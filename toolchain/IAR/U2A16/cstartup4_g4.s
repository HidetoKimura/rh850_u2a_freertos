;-----------------------------------------------------------------------------
;       This file contains the startup code
;       used by the RH850 C/C++ compiler.
;
;       Copyright 2012-2020 IAR Systems AB.
;
;-----------------------------------------------------------------------------

;---------------------------------------------------------------;
; Naming convention of labels in this file:                     ;
;                                                               ;
;  ?xxx  - External labels only accessed from assembler.        ;
;  __xxx - External labels accessed from or defined in C.       ;
;  xxx   - Labels local to one module (note: this file contains ;
;          several modules).                                    ;
;  main  - The starting point of the user program.              ;
;---------------------------------------------------------------;

;---------------------------------------------------------------;
; Defines for RAM initialization.                               ;
;                                                               ;
; To SKIP initialization of used RAM memory with 32-bit         ;
; write accesses, define the macro:                             ;
; __NORAMINIT__                                                 ;
;                                                               ;
; example: #define __NORAMINIT__                                ;
;---------------------------------------------------------------;
;#define __NORAMINIT__

;---------------------------------------------------------------;
; Includes.                                                     ;
;---------------------------------------------------------------;
#include "lxx.h"
#include "cfi.h"

            CASEON

;---------------------------------------------------------------;
; Call Frame Information                                        ;
;---------------------------------------------------------------;

            CFNAMES
            CFCOMMON

            MODULE      CSTARTUP

;---------------------------------------------------------------;
; Module start.                                                 ;
;---------------------------------------------------------------;

            EXTERN      _exception_vector_table
            EXTERN      __iar_static_base$$GP
            EXTERN      __iar_static_base$$TP
            EXTERN      __iar_static_base$$EP
            PUBLIC      __iar_program_start4_g4
            PUBLIC      ??reset_vector

;---------------------------------------------------------------;
; C startup Control Registers                                   ;
; Used as semaphores in multicore systems.                       ;
;---------------------------------------------------------------;

#define SEMAPHORE_A 0x34567890
#define SEMAPHORE_B 0x87654321
            
            SECTION     .bss.noinit:DATA:NOROOT(2)
__IAR_STARTUP_SEMAPHORE_COUNTER:
            DATA
            DS8         4
            
            SECTION     .bss.noinit:DATA:NOROOT(2)
__IAR_STARTUP_SEMAPHORE_LOCK2:
            DATA
            DS8         4

            SECTION     .bss.noinit:DATA:NOROOT(2)
__IAR_STARTUP_SEMAPHORE_LOCK1:
            DATA
            DS8         4

;---------------------------------------------------------------;
; Forward declarations of segments used in this module.         ;
;---------------------------------------------------------------;

            SECTION     CSTACK0:DATA:NOROOT(2)
            SECTION     CSTACK1:DATA:NOROOT(2)
            SECTION     CSTACK2:DATA:NOROOT(2)
            SECTION     CSTACK3:DATA:NOROOT(2)
            SECTION     `Region$$Table`:DATA:REORDER:NOROOT(0)
            SECTION     `Region$$TableS`:DATA:REORDER:NOROOT(0)
            SECTION     `Region$$Table0`:DATA:REORDER:NOROOT(0)
            SECTION     `Region$$Table1`:DATA:REORDER:NOROOT(0)
            SECTION     `Region$$Table2`:DATA:REORDER:NOROOT(0)
            SECTION     `Region$$Table3`:DATA:REORDER:NOROOT(0)

            SECTION     HEAP:DATA:NOROOT(2)
            SECTION     `Region$$RamTable`:DATA
            SECTION     .sbss:DATA
            SECTION     .sconst:CONST

;---------------------------------------------------------------;
; The startup code.                                             ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(2)
            CODE

            CFSTART     cstartup
            CFI Function __iar_program_start4_g4
            CALL_GRAPH_ROOT __iar_program_start4_g4, "reset"            

;---------------------------------------------------------------;
; The startup sequence contained in the final linked            ;
; application will consist of a mosaic containing               ;
; modules and segment parts defined in this file.               ;
;                                                               ;
; The only part which is required is the call to                ;
; the function "main".                                          ;
;---------------------------------------------------------------;

?BTT_cstart_begin:
__iar_program_start4_g4:
??reset_vector:
            REQUIRE     _exception_vector_table
            REQUIRE     ?cstart_call_main
            REQUIRE     ?INIT_PSW
            REQUIRE     ?INIT_STACKS
            REQUIRE     ?GLOBAL_INIT

;---------------------------------------------------------------;
; Get running PE.                                               ;
;---------------------------------------------------------------;

            STSR        0, R6, 2                        ; get PEID.PEID
            ANDI        0x7, R6, R20                    ; set core id (PE number)

;---------------------------------------------------------------;
; Set up the global pointers.                                   ;
;---------------------------------------------------------------;

#if __ROPI__
; Calculate adjusted PC offset for ROPI
     
            JARL        ?PC_LABEL, LP
?PC_LABEL:
            MOV         ?PC_LABEL, GP
            SUBR        LP, GP
            MOV         __iar_static_base$$TP, TP
            ADD         GP, TP
#else
            MOV         __iar_static_base$$TP, TP
#endif
            MOV         __iar_static_base$$GP, GP

            CFEND       cstartup

;---------------------------------------------------------------;
; Initialize the saddr base pointers.                           ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(1)
            
            PUBLIC      ?INIT_SADDR_BASE
            CFSTART     cstartup0
            CFI Function __iar_program_start4_g4

?INIT_SADDR_BASE:
            ;RTMODEL     "__reg_ep", "saddr"
            MOV         __iar_static_base$$EP, EP
            CFEND       cstartup0

;---------------------------------------------------------------;
; Initialize co-processors                                      ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(1)
            
            CFSTART     cstartup1
            CFI Function __iar_program_start4_g4

?INIT_PSW:
            STSR        5, R6, 0           ; get PSW
            MOV         0x00070000, R7
            OR          R7, R6             ; PSW.CU0 = 1, PSW.CU1 = 1, PSW.CU2 = 1

            ; Attempt to enable coprocessors. If they don't exist,
            ; this should not causes any problems. 
            ; The apropriate bits in PSW will simply remain fixed to zero.
            
            LDSR        R6, 5, 0           ; set PSW
            CFEND       cstartup1

;---------------------------------------------------------------;
; Stack initializations.                                        ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(1)
            
            CFSTART     cstartup2
            CFI Function __iar_program_start4_g4

?INIT_STACKS:

;---------------------------------------------------------------;
; Set the stacks for all PEs.                                   ;
;---------------------------------------------------------------;

            MOV         0xCDCDCDCD, R8
            CMP         0, R20
            BZ          ?stack_PE0
            CMP         1, R20
            BZ          ?stack_PE1
            CMP         2, R20
            BZ          ?stack_PE2
            CMP         3, R20
            BZ          ?stack_PE3
?not_used_PE:
            SNOOZE
            BR          ?not_used_PE
?stack_PE0:
            ; Clear counter
            MOV         __IAR_STARTUP_SEMAPHORE_COUNTER, R7
            MOV         0, R6
            ST.W        R6, 0[R7]
            ; Make sure the semaphore lock is locked by PE0
            MOV         __IAR_STARTUP_SEMAPHORE_LOCK1, R7
            MOV         SEMAPHORE_A, R6
            ST.W        R6, 0[R7]
            MOV         __IAR_STARTUP_SEMAPHORE_LOCK2, R7
            MOV         SEMAPHORE_B, R6
            ST.W        R6, 0[R7]
            MOV         SFE CSTACK0, SP
            MOV         SP, R7
            MOV         SFB CSTACK0, R6
?stack_PE_loop0:                          ;Clear stack for PE0
#if __CORE__ == __CORE_G4MH__
            ST.W        R8, [R6]+
#else
            ST.W        R8, 0[R6]
            ADD         4, R6
#endif
            CMP         R7, R6
            BC          ?stack_PE_loop0
            BR          __cstart_low_level_init
?stack_PE1:
            MOV         SFE CSTACK1, SP
            MOV         SP, R7
            MOV         SFB CSTACK1, R6
?stack_PE_loop1:                          ;Clear stack for PE1
#if __CORE__ == __CORE_G4MH__
            ST.W        R8, [R6]+
#else
            ST.W        R8, 0[R6]
            ADD         4, R6
#endif
            CMP         R7, R6
            BC          ?stack_PE_loop1
            BR          __cstart_low_level_init
?stack_PE2:
            MOV         SFE CSTACK2, SP
            MOV         SP, R7
            MOV         SFB CSTACK2, R6
?stack_PE_loop2:                          ;Clear stack for PE2
#if __CORE__ == __CORE_G4MH__
            ST.W        R8, [R6]+
#else
            ST.W        R8, 0[R6]
            ADD         4, R6
#endif
            CMP         R7, R6
            BC          ?stack_PE_loop2
            BR          __cstart_low_level_init
?stack_PE3:
            MOV         SFE CSTACK3, SP
            MOV         SP, R7
            MOV         SFB CSTACK3, R6
?stack_PE_loop3:                          ;Clear stack for PE3
#if __CORE__ == __CORE_G4MH__
            ST.W        R8, [R6]+
#else
            ST.W        R8, 0[R6]
            ADD         4, R6
#endif
            CMP         R7, R6
            BC          ?stack_PE_loop3


            CFEND     cstartup2

;---------------------------------------------------------------;
; If hardware must be initialized from C or if watch dog timer  ;
; must be handled or if the segment init should not be          ;
; performed it can now be done in `__low_level_init'.           ;
;---------------------------------------------------------------;
; Call the user function __low_level_init, if defined.          ;
; It is the responsibility of __low_level_init to require       ;
; __cstart_low_level_init in order to be called by cstartup.    ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(1)

            PUBLIC      __cstart_low_level_init
            EXTERN      ___low_level_init
            EXTERN      _low_level_init_pe0
            CFSTART     cstartup3
            CFI Function __iar_program_start4_g4

__cstart_low_level_init:
            ; We jump to our own low level init for pe0 first
            CMP         0, R20
            BNZ         __cstart_data_init
            JARL        _low_level_init_pe0, LP

            MOV         R20, R6
            CFI FunCall ___low_level_init
            CALL_FUNC   ___low_level_init, LP, R1
            ANDI        0xFF, R10, R10
            BZ          ?no_seg_init



;---------------------------------------------------------------;
; Segment initialization code. Copy initialized ROMmed code to  ;
; RAM and ?seg_clear uninitialized variables.                   ;
;---------------------------------------------------------------;
  EXTERN _g_GRAM_ClearFlag

#define CLUSTER_0_RAM_ADDR      0xFE000000
#define CLUSTER_0_RAM_END       0xFE07FFFF

#define CLUSTER_1_RAM_ADDR      0xFE100000
#define CLUSTER_1_RAM_END       0xFE17FFFF
	
#define CLUSTER_2_RAM_ADDR      0xFE400000
#define CLUSTER_2_RAM_END       0xFE5FFFFF
	
#define CLUSTER_3_RAM_ADDR      0xFE800000
#define CLUSTER_3_RAM_END       0xFE83FFFF
	
#define LOCAL_RAM_SELF_ADDR     0xFDE00000
#define LOCAL_RAM_SELF_END      0xFDE0FFFF

#define RESF                    0xFF988500

            EXTERN      ___iar_data_init2
__cstart_data_init:
            MOV         LOCAL_RAM_SELF_ADDR, R6
            MOV         LOCAL_RAM_SELF_END,  R7
            MOV         R0, R12
            MOV         R0, R13
?clear_self:
            ST.DW       R12, 0[R6]
            ADD         8, R6
            CMP         R7, R6
            BLE          ?clear_self
            
            CMP         0, R20
            BZ          ?data_init_PE0
            
;-----------------------------------------------------------------------------
;	_wait_gram_clear
; Wait until corrensponding flag is set by PE0
;-----------------------------------------------------------------------------
_wait_gram_clear:
            MOV  _g_GRAM_ClearFlag, R6
            MOV  1, R7 
            LD.W 0[R6], R8
            CMP  R7, R8
            BZ   _wait_gram_clear2
_wait_gram_clear1:
            SNOOZE
            LD.W 0[R6], R8
            CMP  R7, R8
            BNZ  _wait_gram_clear1
_wait_gram_clear2:

            CMP         1, R20
            BZ          ?data_init_PE1
            CMP         2, R20
            BZ          ?data_init_PE2
            CMP         3, R20
            BZ          ?data_init_PE3
?data_init_PE0:
            MOV         CLUSTER_0_RAM_ADDR, R6
            MOV         CLUSTER_0_RAM_END,  R7
?clear_cluster0:
            ST.DW       R12, 0[R6]
            ADD         8, R6
            CMP         R7, R6
            BLE          ?clear_cluster0
            
            MOV         CLUSTER_2_RAM_ADDR, R6
            MOV         CLUSTER_2_RAM_END,  R7
?clear_cluster2:
            ST.DW       R12, 0[R6]
            ADD         8, R6
            CMP         R7, R6
            BLE          ?clear_cluster2
            
            ; only clear Retention RAM (Cluster 3) when Power On Reset flag is set 
            MOV RESF, r9
            LD.W 0[r9], r8
            ANDI 4, r8, r8
            BZ  ?init_end

            MOV         CLUSTER_3_RAM_ADDR, R6
            MOV         CLUSTER_3_RAM_END,  R7
?clear_cluster3:
            ST.DW       R12, 0[R6]
            ADD         8, R6
            CMP         R7, R6
            BLE          ?clear_cluster3

?init_end:
            MOV  _g_GRAM_ClearFlag, R6
            MOV  1, R7
            ST.W R7, 0[R6]

            ; Initialize self area
#if __ROPI__
            MOV         __iar_static_base$$TP, R8
            MOV         SFE(`Region$$TableS`), R7
            MOV         SFB(`Region$$TableS`), R6
            SUB         R8, R7
            SUB         R8, R6
            ADD         TP, R7
            ADD         TP, R6
#else
            MOV         SFE(`Region$$TableS`), R7
            MOV         SFB(`Region$$TableS`), R6
#endif
            CFI FunCall ___iar_data_init2
            CALL_FUNC   ___iar_data_init2, LP, R1

            ; Initialize global data
#if __ROPI__
            MOV         __iar_static_base$$TP, R8
            MOV         SFE(`Region$$Table`), R7
            MOV         SFB(`Region$$Table`), R6
            SUB         R8, R7
            SUB         R8, R6
            ADD         TP, R7
            ADD         TP, R6
#else
            MOV         SFE(`Region$$Table`), R7
            MOV         SFB(`Region$$Table`), R6
#endif
            CFI FunCall ___iar_data_init2
            CALL_FUNC   ___iar_data_init2, LP, R1

            ; Initialize core data
#if __ROPI__
            MOV         __iar_static_base$$TP, R8
            MOV         SFE(`Region$$Table0`), R7
            MOV         SFB(`Region$$Table0`), R6
            SUB         R8, R7
            SUB         R8, R6
            ADD         TP, R7
            ADD         TP, R6
#else
            MOV         SFE(`Region$$Table0`), R7
            MOV         SFB(`Region$$Table0`), R6
#endif
            CFI FunCall ___iar_data_init2
            CALL_FUNC   ___iar_data_init2, LP, R1
            BR ?no_seg_init

?data_init_PE1:
            ; Initialize self area
#if __ROPI__
            MOV         __iar_static_base$$TP, R8
            MOV         SFE(`Region$$TableS`), R7
            MOV         SFB(`Region$$TableS`), R6
            SUB         R8, R7
            SUB         R8, R6
            ADD         TP, R7
            ADD         TP, R6
#else
            MOV         SFE(`Region$$TableS`), R7
            MOV         SFB(`Region$$TableS`), R6
#endif
            CFI FunCall ___iar_data_init2
            CALL_FUNC   ___iar_data_init2, LP, R1

            ; Initialize core data
#if __ROPI__
            MOV         __iar_static_base$$TP, R8
            MOV         SFE(`Region$$Table1`), R7
            MOV         SFB(`Region$$Table1`), R6
            SUB         R8, R7
            SUB         R8, R6
            ADD         TP, R7
            ADD         TP, R6
#else
            MOV         SFE(`Region$$Table1`), R7
            MOV         SFB(`Region$$Table1`), R6
#endif
            CFI FunCall ___iar_data_init2
            CALL_FUNC   ___iar_data_init2, LP, R1
            BR ?no_seg_init

?data_init_PE2:
            MOV         CLUSTER_1_RAM_ADDR, R6
            MOV         CLUSTER_1_RAM_END,  R7
?clear_cluster1:
            ST.DW       R12, 0[R6]
            ADD         8, R6
            CMP         R7, R6
            BLE          ?clear_cluster1
            ; Initialize self area
#if __ROPI__
            MOV         __iar_static_base$$TP, R8
            MOV         SFE(`Region$$TableS`), R7
            MOV         SFB(`Region$$TableS`), R6
            SUB         R8, R7
            SUB         R8, R6
            ADD         TP, R7
            ADD         TP, R6
#else
            MOV         SFE(`Region$$TableS`), R7
            MOV         SFB(`Region$$TableS`), R6
#endif
            CFI FunCall ___iar_data_init2
            CALL_FUNC   ___iar_data_init2, LP, R1

            ; Initialize core data
#if __ROPI__
            MOV         __iar_static_base$$TP, R8
            MOV         SFE(`Region$$Table2`), R7
            MOV         SFB(`Region$$Table2`), R6
            SUB         R8, R7
            SUB         R8, R6
            ADD         TP, R7
            ADD         TP, R6
#else
            MOV         SFE(`Region$$Table2`), R7
            MOV         SFB(`Region$$Table2`), R6
#endif
            CFI FunCall ___iar_data_init2
            CALL_FUNC   ___iar_data_init2, LP, R1
            BR ?no_seg_init

?data_init_PE3:
            ; Initialize self area
#if __ROPI__
            MOV         __iar_static_base$$TP, R8
            MOV         SFE(`Region$$TableS`), R7
            MOV         SFB(`Region$$TableS`), R6
            SUB         R8, R7
            SUB         R8, R6
            ADD         TP, R7
            ADD         TP, R6
#else
            MOV         SFE(`Region$$TableS`), R7
            MOV         SFB(`Region$$TableS`), R6
#endif
            CFI FunCall ___iar_data_init2
            CALL_FUNC   ___iar_data_init2, LP, R1

            ; Initialize core data
#if __ROPI__
            MOV         __iar_static_base$$TP, R8
            MOV         SFE(`Region$$Table3`), R7
            MOV         SFB(`Region$$Table3`), R6
            SUB         R8, R7
            SUB         R8, R6
            ADD         TP, R7
            ADD         TP, R6
#else
            MOV         SFE(`Region$$Table3`), R7
            MOV         SFB(`Region$$Table3`), R6
#endif
            CFI FunCall ___iar_data_init2
            CALL_FUNC   ___iar_data_init2, LP, R1


;---------------------------------------------------------------;
; Destination label when skipping data initialization.          ;
;---------------------------------------------------------------;

?no_seg_init:
            CFEND     cstartup3


            EXTERN      ?CODE_DISTANCE
            PUBLIC      ___iar_init_callt
            PUBLIC      ___iar_init_syscall
            PUBLIC      ___iar_init_interrupt
            PUBLIC      ?BTT_cstart_end
            PUBLIC      __exit
            PUBLIC      ?BTT_exit_begin
            PUBLIC      ?BTT_exit_end

;---------------------------------------------------------------;
; Initialize the CALLT base pointers.                           ;
;---------------------------------------------------------------;

            SECTION     .table.callt:CONST
            SECTION     .text:CODE:NOROOT(1)
            CFSTART     cstartup4
            CFI Function __iar_program_start4_g4


            ;; The CALLT table base pointer
___iar_init_callt:
            EXTERN      _callt_vector_table
            REQUIRE     _callt_vector_table

#if __ROPI__
            MOVHI       hi1(reltp(SFB .table.callt)),TP,R8
            MOVEA       lw1(reltp(SFB .table.callt)),R8,R8
#else
            MOV         SFB .table.callt, R8
#endif
            LDSR        R8, 20          ; CTBP

            CFEND     cstartup4

;---------------------------------------------------------------;
; Initialize the SYSCALL base pointers.                         ;
;---------------------------------------------------------------;

            SECTION     `.table.syscall`:CONST
            SECTION     .text:CODE:NOROOT(1)
            CFSTART     cstartup5
            CFI Function __iar_program_start4_g4

            ;; The SYSCALL table base pointer
___iar_init_syscall:
            EXTERN      _syscall_vector_table
            REQUIRE     _syscall_vector_table
            
#if __ROPI__
            MOVHI       hi1(reltp(SFB .table.syscall)),TP,R8
            MOVEA       lw1(reltp(SFB .table.syscall)),R8,R8
#else
            MOV         SFB .table.syscall, R8
#endif
            LDSR        R8, 12, 1        ; SCBP

            MOV         (SIZEOF .table.syscall) - 4, R8
            SHR         2, R8
            LDSR        R8, 11, 1        ; SCCFG
            CFEND     cstartup5

;---------------------------------------------------------------;
; Initialize the INTBP base pointer.                            ;
;---------------------------------------------------------------;

            SECTION     `.table.interrupt_core_0`:CONST
            SECTION     `.table.interrupt_core_1`:CONST
            SECTION     `.table.interrupt_core_2`:CONST
            SECTION     `.table.interrupt_core_3`:CONST
            SECTION     .text:CODE:ROOT(1)

            ;; The INTBP table base pointer
            CFSTART     cstartup5b
            CFI Function __iar_program_start4_g4
___iar_init_interrupt:
            EXTERN      _INT_Vectors_PE0
            REQUIRE     _INT_Vectors_PE0

            CMP         0, R20
            BNZ         ?int_PE0
#if __ROPI__
            MOV         _INT_Vectors_PE0, R8
            MOVHI       hi1(reltp(SFB `.table.interrupt_core_0`)), TP, R6
            MOVEA       lw1(reltp(SFB `.table.interrupt_core_0`)), R6, R6
            MOVHI       hi1(reltp(SFE `.table.interrupt_core_0`)), TP, R7
            MOVEA       lw1(reltp(SFE `.table.interrupt_core_0`)), R7, R7
?interrupt_loop0:
            LD.W        0[R6], LP
            ADD         TP, LP
            ADD         4, R6
            ST.W        LP, 0[R8]
            ADD         4, R8
            CMP         R7, R6
            BC          ?interrupt_loop0
#endif
            MOV         _INT_Vectors_PE0, R8
?int_PE0:
            EXTERN      _INT_Vectors_PE1
            REQUIRE     _INT_Vectors_PE1

            CMP         1, R20
            BNZ         ?int_PE1
#if __ROPI__
            MOV         _INT_Vectors_PE1, R8
            MOVHI       hi1(reltp(SFB `.table.interrupt_core_1`)), TP, R6
            MOVEA       lw1(reltp(SFB `.table.interrupt_core_1`)), R6, R6
            MOVHI       hi1(reltp(SFE `.table.interrupt_core_1`)), TP, R7
            MOVEA       lw1(reltp(SFE `.table.interrupt_core_1`)), R7, R7
?interrupt_loop1:
            LD.W        0[R6], LP
            ADD         TP, LP
            ADD         4, R6
            ST.W        LP, 0[R8]
            ADD         4, R8
            CMP         R7, R6
            BC          ?interrupt_loop1
#endif
            MOV         _INT_Vectors_PE1, R8
?int_PE1:
            EXTERN      _INT_Vectors_PE2
            REQUIRE     _INT_Vectors_PE2

            CMP         2, R20
            BNZ         ?int_PE2
#if __ROPI__
            MOV         _INT_Vectors_PE2, R8
            MOVHI       hi1(reltp(SFB `.table.interrupt_core_2`)), TP, R6
            MOVEA       lw1(reltp(SFB `.table.interrupt_core_2`)), R6, R6
            MOVHI       hi1(reltp(SFE `.table.interrupt_core_2`)), TP, R7
            MOVEA       lw1(reltp(SFE `.table.interrupt_core_2`)), R7, R7
?interrupt_loop2:
            LD.W        0[R6], LP
            ADD         TP, LP
            ADD         4, R6
            ST.W        LP, 0[R8]
            ADD         4, R8
            CMP         R7, R6
            BC          ?interrupt_loop2
#endif
            MOV         _INT_Vectors_PE2, R8
?int_PE2:
            EXTERN      _INT_Vectors_PE3
            REQUIRE     _INT_Vectors_PE3

            CMP         3, R20
            BNZ         ?int_PE3
#if __ROPI__
            MOV         _INT_Vectors_PE3, R8
            MOVHI       hi1(reltp(SFB `.table.interrupt_core_3`)), TP, R6
            MOVEA       lw1(reltp(SFB `.table.interrupt_core_3`)), R6, R6
            MOVHI       hi1(reltp(SFE `.table.interrupt_core_3`)), TP, R7
            MOVEA       lw1(reltp(SFE `.table.interrupt_core_3`)), R7, R7
?interrupt_loop3:
            LD.W        0[R6], LP
            ADD         TP, LP
            ADD         4, R6
            ST.W        LP, 0[R8]
            ADD         4, R8
            CMP         R7, R6
            BC          ?interrupt_loop3
#endif
            MOV         _INT_Vectors_PE3, R8
?int_PE3:

            
            LDSR        R8, 4, 1         ; INTBP
            CFEND     cstartup5b

;---------------------------------------------------------------;
; Initialization done by one core only.                         ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(1)
            CFSTART     cstartup6
            CFI Function __iar_program_start4_g4

?GLOBAL_INIT:


;---------------------------------------------------------------;
; Check if wait (PE1+) or continue (PE0).                       ;
;---------------------------------------------------------------;

            CMP         0, R20
            BZ          ?continue_init

;---------------------------------------------------------------;
; All, but PE0, waits here for PE0 to finalize init.            ;
;---------------------------------------------------------------;
            CFI FunCall __wait_for_init
            CALL_FUNC   __wait_for_init, LP, R1
            BR          ?init_done_PE0

?continue_init:

;---------------------------------------------------------------;
; Only PE0 do all the rest.                                     ;
;---------------------------------------------------------------;

;---------------------------------------------------------------;
; TLS initialization code. Copy initialized ROMmed code to      ;
; RAM and uninitialized variables.                              ;
;---------------------------------------------------------------;

            EXTWEAK     ___iar_cstart_tls_init
            CFI FunCall ___iar_cstart_tls_init
            CALL_FUNC   ___iar_cstart_tls_init, LP, R1

;---------------------------------------------------------------;
; Init heap memory.                                             ;
;---------------------------------------------------------------;

            PUBLIC      ?heap_init

?heap_init:
            MOV         SFB HEAP, R6
            MOV         SFE HEAP, R7
            BR          ?heap_init_loop_test
?heap_init_loop:                          
#if __CORE__ == __CORE_G4MH__
            ST.W        R0, [R6]+
#else
            ST.W        R0, 0[R6]
            ADD         4, R6
#endif
?heap_init_loop_test:                          
            CMP         R6, R7
            BNZ         ?heap_init_loop

            CFEND     cstartup6

;---------------------------------------------------------------;
; This segment part is required by the compiler when it is      ;
; necessary to call constructors of global objects.             ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(1)

            PUBLIC      __iar_cstart_call_ctors2
            EXTWEAK     ___iar_dynamic_initialization
            CFSTART     cstartup7
            CFI Function __iar_program_start4_g4

__iar_cstart_call_ctors2:
            CFI FunCall ___iar_dynamic_initialization
            CALL_FUNC   ___iar_dynamic_initialization, LP, R8
            CFEND       cstartup7


            SECTION     .text:CODE:NOROOT(1)
            CFSTART     cstartup7b
            CFI Function __iar_program_start4_g4

;---------------------------------------------------------------;
; PE0 init has finished.                                        ;
;---------------------------------------------------------------;

            ; Flag that PE0 init is finished
            MOV         __IAR_STARTUP_SEMAPHORE_LOCK1, R7
            MOV         SEMAPHORE_B, R6
            ST.W        R6, 0[R7]
            MOV         __IAR_STARTUP_SEMAPHORE_LOCK2, R7
            MOV         SEMAPHORE_A, R6
            ST.W        R6, 0[R7]
            MOV         0, R6                                       ; Set current core
?init_done_PE0:

;---------------------------------------------------------------;
; Wait for all cores to finish with initializing before calling ;
; main                                                          ;
;---------------------------------------------------------------;

            PUBLIC      ?wait_for_others

            MOV         __IAR_STARTUP_SEMAPHORE_COUNTER, R7         ; Increase core counter
?wait_for_my_turn:
            LD.W        0[R7], R8
            CMP         R6,R8
            BNZ         ?wait_for_my_turn
            ADD         1, R8
            ST.W        R8, 0[R7]

?wait_for_others:
            LD.W        0[R7], R8
            CMP         4, R8
            BZ          ?waitfinished
            SNOOZE
            BR          ?wait_for_others
            
?waitfinished:
            CFEND     cstartup7b




;---------------------------------------------------------------;
; Call C main() with no parameters.                             ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(1)

            EXTERN      _main_pe0
            EXTERN      _main_pe1
            EXTERN      _main_pe2
            EXTERN      _main_pe3
            EXTERN      _exit
            REQUIRE     __cstart_data_init
            CFSTART     cstartup8
            CFI Function __iar_program_start4_g4

?cstart_call_main:
            CMP         0, R20
            BZ          ?call_main_pe0
            CMP         1, R20
            BZ          ?call_main_pe1
            CMP         2, R20
            BZ          ?call_main_pe2
            CMP         3, R20
            BZ          ?call_main_pe3
            
            JARL        ?not_used_PE, LP
            
?call_main_pe0:
            CFI FunCall _main_pe0
            CALL_FUNC   _main_pe0, LP, R6
            BR          ?main_call_exit
?call_main_pe1:
            CFI FunCall _main_pe1
            CALL_FUNC   _main_pe1, LP, R6
            BR          ?main_call_exit
?call_main_pe2:
            CFI FunCall _main_pe2
            CALL_FUNC   _main_pe2, LP, R6
            BR          ?main_call_exit
?call_main_pe3:
            CFI FunCall _main_pe3
            CALL_FUNC   _main_pe3, LP, R6

;---------------------------------------------------------------;
; If we come here we have returned from main with a 'return'    ;
; statement, not with a call to exit() or abort().              ;
; In this case we must call exit() here for a nice ending.      ;
; Note: The return value of main() is the argument to exit().   ;
;---------------------------------------------------------------;
?main_call_exit:
            MOV         R10, R6
            CFI FunCall _exit
            CALL_FUNC   _exit, LP, R7

;---------------------------------------------------------------;
; We should never come here, but just in case.                  ;
;---------------------------------------------------------------;

            MOV         ___exit, LP
            CFI TailCall ___exit
            JMP         [LP]

__wait_for_init:
            ; Check if main core is initializing
            MOV         __IAR_STARTUP_SEMAPHORE_LOCK1, R7
            MOV         SEMAPHORE_A, R6
            LD.W        0[R7],R7
            CMP         R6,R7
            BZ          waitloop1
            MOV         __IAR_STARTUP_SEMAPHORE_LOCK2, R7
            MOV         SEMAPHORE_B, R6
            LD.W        0[R7],R7
            CMP         R6,R7
            BNZ         waitphase2
waitloop1:
            SNOOZE
            BR          __wait_for_init
waitphase2:
            ; Wait for main core to finish initializing
            MOV         __IAR_STARTUP_SEMAPHORE_LOCK1, R7
            MOV         SEMAPHORE_B, R6
            LD.W        0[R7],R7
            CMP         R6,R7
            BNZ         waitloop2
            MOV         __IAR_STARTUP_SEMAPHORE_LOCK2, R7
            MOV         SEMAPHORE_A, R6
            LD.W        0[R7],R7
            CMP         R6,R7
            BZ          waitphase3
waitloop2:
            SNOOZE
            BR          waitphase2
waitphase3:
            CMP         0,R20
            BNZ         ?wait_exit0
            MOV         0,R6
            JMP         [LP]
?wait_exit0:
            CMP         1,R20
            BNZ         ?wait_exit1
            MOV         1,R6
            JMP         [LP]
?wait_exit1:
            CMP         2,R20
            BNZ         ?wait_exit2
            MOV         2,R6
            JMP         [LP]
?wait_exit2:
            CMP         3,R20
            BNZ         ?wait_exit3
            MOV         3,R6
            JMP         [LP]
?wait_exit3:
            JMP         [LP]

?BTT_cstart_end:
            CFEND       cstartup8

;---------------------------------------------------------------;
; _exit code                                                    ;
;                                                               ;
; Call destructors (if required), then fall through to __exit.  ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(1)
            CFSTART     cstartup9
            CFI Function __exit

?BTT_exit_begin:
__exit:
            REQUIRE     ?exit_restore2
            NOP
            CFEND     cstartup9
            
;---------------------------------------------------------------;
; If any of the two pieces of code "__cexit_call_dtors" or      ;
; "___cstart_closeall" is called we need to save the argument   ;
; to "_exit". However, since we never will return from this     ;
; function we can use a permanent register rather than storing  ;
; the value on the stack.                                       ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(1)
            CFSTART     cstartup10
            CFI Function __exit

?exit_save:
            REQUIRE     ?exit_restore

            MOV         R6, R29
            CFEND       cstartup10

            SECTION     .text:CODE:NOROOT(1)

            PUBLIC      __cexit_call_dtors
            EXTWEAK     ___call_dtors

            REQUIRE     ?exit_save
            CFSTART     cstartup11
            CFI Function __exit

__cexit_call_dtors:
            CFI FunCall ___call_dtors
            CALL_FUNC   ___call_dtors, LP, R1

            CFEND       cstartup11

            ;; A new module is needed so that a program without
            ;; terminal I/O doesn't include this.

            SECTION     .text:CODE:NOROOT(1)

            PUBLIC      __cexit_closeall
            EXTWEAK     __Close_all

            REQUIRE     ?exit_save
            CFSTART     cstartup12
            CFI Function __exit

__cexit_closeall:
            CFI FunCall __Close_all
            CALL_FUNC   __Close_all, LP, R1

            CFEND       cstartup12

            ;; A new module is needed so that a program without
            ;; DLib threads doesn't include this.

            SECTION     .text:CODE:NOROOT(1)

            PUBLIC      __cexit_clearlocks
            EXTWEAK     ___iar_clearlocks

            REQUIRE     ?exit_save
            CFSTART     cstartup13
            CFI Function __exit

__cexit_clearlocks:
            CFI FunCall ___iar_clearlocks
            CALL_FUNC   ___iar_clearlocks, LP, R1

            CFEND       cstartup13

            ;; Restore the argument previously stored by the "save" section
            ;; above.

            SECTION     .text:CODE:NOROOT(1)
            CFSTART     cstartup14
            CFI Function __exit

?exit_restore:
            REQUIRE     ?exit_restore2
            MOV         R29, R6

            CFEND       cstartup14

            SECTION     .text:CODE:NOROOT(1)

            EXTERN      ___exit
            CFSTART     cstartup15
            CFI Function __exit

?exit_restore2:
 #if __ROPI__
            MOV         __iar_static_base$$TP, R8
            MOV         ___exit, LP
            SUB         R8, LP
            ADD         TP, LP
#else
            MOV         ___exit, LP
#endif
            CFI TailCall ___exit
            JMP         [LP]

?BTT_exit_end:
            CFEND       cstartup15

            END

;-----------------------------------------------------------------------------
