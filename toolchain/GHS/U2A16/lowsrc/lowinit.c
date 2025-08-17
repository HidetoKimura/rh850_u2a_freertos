/*===============================================================================================

    Copyright (c) 2013 by Renesas Electronics Europe GmbH, a company of the Renesas Electronics 
    Corporation. All rights reserved.

  ===============================================================================================

    Warranty Disclaimer                                                       
                                                                             
    Because the Product(s) is licensed free of charge, there is no warranty of any kind
    whatsoever and expressly disclaimed and excluded by Renesas, either expressed or implied, 
    including but not limited to those for non-infringement of intellectual property, 
    merchantability and/or fitness for the particular purpose.
    Renesas shall not have any obligation to maintain, service or provide bug fixes for the
    supplied Product(s) and/or the Application.

    Each User is solely responsible for determining the appropriateness of using the Product(s)
    and assumes all risks associated with its exercise of rights under this Agreement, including,
    but not limited to the risks and costs of program errors, compliance with applicable laws,
    damage to or loss of data, programs or equipment, and unavailability or interruption of
    operations.

    Limitation of Liability

    In no event shall Renesas be liable to the User for any incidental, consequential, indirect,
    or punitive damage (including but not limited to lost profits) regardless of whether such
    liability is based on breach of contract, tort, strict liability, breach of warranties, 
    failure of essential purpose or otherwise and even if advised of the possibility of such
    damages. Renesas shall not be liable for any services or products provided by third party
    vendors, developers or consultants identified or referred to the User by Renesas in 
    connection with the Product(s) and/or the Application.

  ===============================================================================================*/

#define CHECK_BOARD 1
#include <device.h>

#ifndef SNZWAIT
 #define SNZWAIT 32 
#endif
#ifndef MAXWAIT
 #define MAXWAIT (1+(140/SNZWAIT)) 
#endif


//--------------------------------------------------------------------------
// variables
//--------------------------------------------------------------------------

extern u32_T __ghsbegin_bss[];
extern u32_T __ghsend_bss[];
extern u32_T __ghsbegin_data[];
extern u32_T __ghsend_data[];
extern u32_T __ghsbegin_slbss[];
extern u32_T __ghsend_slbss[];
extern u32_T __ghsbegin_sldata[];
extern u32_T __ghsend_sldata[];
extern u32_T __ghsbegin_slsync[];
extern u32_T __ghsend_slsync[];
extern u32_T __ghsbegin_stack[];
extern u32_T __ghsend_stack[];


#pragma ghs startdata			// locate to GRAM
#pragma ghs section bss=".slsync"	// to section ".slsync"
volatile int __ghs_multicore_init_flag;
extern volatile unsigned int	ThreadLocked;		// for mutual exclusion
extern volatile unsigned int	PE_Started;		// for mutual exclusion
#pragma ghs section			//
#pragma ghs enddata			// locate default	

#if defined( __E2XFCC1__) | defined( __E2XFCC2__ )
void R_OSTM0_CreateUser(void);
void R_OSTM0_Create(void);
void R_OSTM0_Start(void);
void R_OSTM0_Stop(void);
void R_OSTM0_Set_CompareValue(u32_T value);
void R_PIC1_Create(void);
void R_PIC1_Timer_SyncStart(void);
void R_PORT_Create(void);
#endif

void __spinLockRW( PVOID pMEVREG);
void __spinUnlockRW( PVOID pMEVREG);

const char id[]="__lowinit";
#pragma weak RESET
extern void RESET( void);
#pragma weak RESET_PE0
extern void RESET_PE0( void);
#pragma weak RESET_PE1
extern void RESET_PE1( void);
#pragma weak RESET_PE2
extern void RESET_PE2( void);
#pragma weak RESET_PE3
extern void RESET_PE3( void);
#pragma weak RESET_PE4
extern void RESET_PE4( void);
#pragma weak RESET_PE5
extern void RESET_PE5( void);
#pragma weak RESET_PE6
extern void RESET_PE6( void);
#pragma weak RESET_PE7
extern void RESET_PE7( void);

#ifdef __RH850G4MH__
extern void RESET_PE0( void);
const PFUNC __reset_hd[8] = { RESET, RESET_PE0, RESET_PE1, RESET_PE2, RESET_PE3, RESET_PE4, RESET_PE5, RESET_PE6};
#else
extern void RESET_PE2( void);
const PFUNC __reset_hd[8] = { RESET, RESET_PE1, RESET_PE2, RESET_PE3, RESET_PE4, RESET_PE5, RESET_PE6, RESET_PE7};
#endif

void SectionInitShared( void);

#ifdef __GNU_ASM_SUPPORT__ 
static inline void MC_INIT( void)
{
#pragma asm
    stsr      PEID, r2, 2
    andi      0x7, r2, r1
    mov       ___ghs_multicore_init_flag, ep
    set1      r1, [ep]
#pragma endasm
}
#else
#error "Please enable GNU ASM support!"
#endif

int swreset0( int try)
{
	if( GetPEID() == PE0) 
    {
        do
        {
            __SNOOZE();
        } while( try--);
    }

    return -1;
}

/*
 * Called first, directly after RESET and before _start() is called
 * Be aware of following restrictions:
 *   1. Use ONLY variables of 32-bit size (int, long)
 *   2. Do not read from any memory, before it has been written to by 32-bit 
 *   3. minimize usage of local variables
 *   4. Initialized memory is NOT available at this point
 */
extern void  low_level_init_pe0(void);  
void __lowinit( void)
{
    /* PE1 stops from continuation, if PE0 did not finish the
     * initialization of shared memory area.
     */
    if( GetPEID() == PE0) 
    {
        #ifdef HAS_CLKINIT  /* From device.h */
                low_level_init_pe0();
        #endif
    }
    else 
    {
        while( __ghs_multicore_init_flag == 0)  __SNOOZE();
    }
}


/* 
 * Once PE0 finished its initialization part, PE1 may continue to
 * initialize the workspeace.
 */
#pragma alignfunc (4)
void __ghs_board_devices_init(void)
{
	/* 
	 * If both cores are finished with the runtime initialization,
     * the MEV32 register contains PE0 ... PE7
	 */
    MC_INIT();      /* __ghs_multicore_init_flag |=  1<<GetPEID(); */
    if( GetPEID() == PE0) 
    {
        BARRIER_0_INIT();
    }
}

#pragma asm
#ifndef ENTER
#define ENTER( f) \
	.global	 f; \
	.section .text; \
	.align   4; \
	.type    f, @function; \
f:;
#endif

#ifndef LEAVE
#define LEAVE( f) \
	.type  f, @function; \
	.size	f, .-f;
#endif

ENTER( _JumpToReset)
     stsr      PEID, r6, 2     -- load PE identifier
     andi      0x7, r6, r6     -- mask out pe0...pe7
     movhi     hi(___reset_hd+4), r0, r7
     shl       2, r6           -- adjust index to jump table
     add       r7, r6
     ld.w      lo(___reset_hd+4)[r6], r8   -- load the target address into r29
     jmp       [r8]            -- start local reset

     jmp       [lp]
LEAVE( _JumpToReset)
#pragma endasm

