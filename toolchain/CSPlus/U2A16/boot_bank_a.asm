;/**********************************************************************************************************************
; * DISCLAIMER
; * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
; * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
; * applicable laws, including copyright laws.
; * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
; * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
; * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
; * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
; * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
; * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
; * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
; * this software. By using this software, you agree to the additional terms and conditions found by accessing the
; * following link:
; * http://www.renesas.com/disclaimer
; *
; * Copyright (C) 2020, 2021 Renesas Electronics Corporation. All rights reserved.
; *********************************************************************************************************************/
;   NOTE       : THIS IS A TYPICAL EXAMPLE.
;   DATE       : Wed, Sep 08, 2021

	; if using eiint as table reference method,
	; enable next line's macro.

	; USE_TABLE_REFERENCE_METHOD .set 1

;-----------------------------------------------------------------------------
;	exception vector table
;-----------------------------------------------------------------------------
	.section "RESET_BANK_A", text
	.public	_zeroclr4
        .extern _g_GRAM_ClearFlag
	.align	512
	jr32	__start ; RESET

	.align	16
	syncp
	jr32	_Dummy ; SYSERR

	.align	16
	jr32	_Dummy

	.align	16
	jr32	_Dummy ; FETRAP

	.align	16
	jr32	_Dummy_EI ; TRAP0

	.align	16
	jr32	_Dummy_EI ; TRAP1

	.align	16
	jr32	_Dummy ; RIE

	.align	16
	syncp
	jr32	_Dummy_EI ; FPE/FXE

	.align	16
	jr32	_Dummy ; UCPOP

	.align	16
	jr32	_Dummy ; MIP/MDP

	.align	16
	jr32	_Dummy ; PIE

	.align	16
	jr32	_Dummy

	.align	16
	jr32	_Dummy ; MAE

	.align	16
	jr32	_Dummy

	.align	16
	syncp
	jr32	_Dummy ; FENMI

	.align	16
	syncp
	jr32	_Dummy ; FEINT

	.align	16
	syncp
	jr32	_Dummy_EI ; INTn(priority0)

	.align	16
	syncp
	jr32	_Dummy_EI ; INTn(priority1)

	.align	16
	syncp
	jr32	_Dummy_EI ; INTn(priority2)

	.align	16
	syncp
	jr32	_Dummy_EI ; INTn(priority3)

	.align	16
	syncp
	jr32	_Dummy_EI ; INTn(priority4)

	.align	16
	syncp
	jr32	_Dummy_EI ; INTn(priority5)

	.align	16
	syncp
	jr32	_Dummy_EI ; INTn(priority6)

	.align	16
	syncp
	jr32	_Dummy_EI ; INTn(priority7)

	.align	16
	syncp
	jr32	_Dummy_EI ; INTn(priority8)

	.align	16
	syncp
	jr32	_Dummy_EI ; INTn(priority9)

	.align	16
	syncp
	jr32	_Dummy_EI ; INTn(priority10)

	.align	16
	syncp
	jr32	_Dummy_EI ; INTn(priority11)

	.align	16
	syncp
	jr32	_Dummy_EI ; INTn(priority12)

	.align	16
	syncp
	jr32	_Dummy_EI ; INTn(priority13)

	.align	16
	syncp
	jr32	_Dummy_EI ; INTn(priority14)

	.align	16
	syncp
	jr32	_Dummy_EI ; INTn(priority15)


	.section ".text", text
	.align	2
_Dummy:
	SNOOZE
	br	_Dummy

_Dummy_EI:
	SNOOZE
	br	_Dummy_EI

;-----------------------------------------------------------------------------
;	startup
;-----------------------------------------------------------------------------
	.section	".text", text
	.align	2
__start:
    ;- General purpose register
    $nowarning
    mov     r0, r1          ; r1  Assembler reserved register
    $warning
    mov     r0, r2          ; r2  Register for address and data variables
    mov     r0, r3          ; r3  Stack pointer(SP)
    mov     r0, r4          ; r4  Global pointer(GP)
    mov     r0, r5          ; r5  Text pointer(TP)
    mov     r0, r6          ; r6  Register for addresses and data variables
    mov     r0, r7          ; r7  Register for addresses and data variables
    mov     r0, r8          ; r8  Register for addresses and data variables
    mov     r0, r9          ; r9  Register for addresses and data variables
    mov     r0, r10         ; r10 Register for addresses and data variables
    mov     r0, r11         ; r11 Register for addresses and data variables
    mov     r0, r12         ; r12 Register for addresses and data variables
    mov     r0, r13         ; r13 Register for addresses and data variables
    mov     r0, r14         ; r14 Register for addresses and data variables
    mov     r0, r15         ; r15 Register for addresses and data variables
    mov     r0, r16         ; r16 Register for addresses and data variables
    mov     r0, r17         ; r17 Register for addresses and data variables
    mov     r0, r18         ; r18 Register for addresses and data variables
    mov     r0, r19         ; r19 Register for addresses and data variables
    mov     r0, r20         ; r20 Register for addresses and data variables
    mov     r0, r21         ; r21 Register for addresses and data variables
    mov     r0, r22         ; r22 Register for addresses and data variables
    mov     r0, r23         ; r23 Register for addresses and data variables
    mov     r0, r24         ; r24 Register for addresses and data variables
    mov     r0, r25         ; r25 Register for addresses and data variables
    mov     r0, r26         ; r26 Register for addresses and data variables
    mov     r0, r27         ; r27 Register for addresses and data variables
    mov     r0, r28         ; r28 Register for addresses and data variables
    mov     r0, r29         ; r29 Register for addresses and data variables
    mov     r0, r30         ; r30 Element pointer(EP)
    mov     r0, r31         ; r31 Link pointer(LP)

    ;- Basic system register
    ldsr    r0,  0, 0       ; SR0,0  EIPC
    ldsr    r0,  2, 0       ; SR2,0  FEPC
    ldsr    r0, 16, 0       ; SR16,0 CTPC
    ldsr    r0, 28, 0       ; SR28,0 EIWR
    ldsr    r0, 29, 0       ; SR29,0 FEWR
    ldsr    r0,  3, 1       ; SR3,1  EBASE
    ldsr    r0,  4, 1       ; SR4,1  INTBP
    ldsr    r0,  6, 2       ; SR6,2  MEA
    ldsr    r0,  8, 2       ; SR8,2  MEI
    ldsr    r0, 18, 2       ; SR18,2 RBIP

    ;- FPU system register
    mov     0x00010020, r10 ; set 1 in PSW.CU0 for writing FPU Function Register
                            ; set 1 in PSW.ID for prohibiting EI-level interrupt
    ldsr    r10, 5, 0       ; SR5,0  PSW 

    mov     0x00220000, r10 ; set 1 in FPSR.FS
    ldsr    r10, 6, 0       ; SR6,0  FPSR
    ldsr    r0,  7, 0       ; SR7,0  FPEPC
    ldsr    r0,  8, 0       ; SR8,0  FPST
    ldsr    r0,  9, 0       ; SR9,0  FPCC

    ;- MPU function register
    ldsr    r0,  8, 5       ; SR8,5  MCA
    ldsr    r0,  9, 5       ; SR9,5  MCS
    ldsr    r0, 11, 5       ; SR11,5 MCR
     
    mov     r0,r2	    
    _loop:		    ; Initialize MPU 32 Areas
    ldsr    r2, 16, 5       ; SR16,5 MPIDX
    ldsr    r0, 20, 5       ; SR20,5 MPLA
    ldsr    r0, 21, 5       ; SR21,5 MPUA
    ldsr    r0, 22, 5       ; SR22,5 MPAT
    add     0x1, r2         ;
    cmp     0x20, r2        ;
    bne     _loop
    
    ldsr    r0, 24, 5       ; SR24,5 MPID0
    ldsr    r0, 25, 5       ; SR25,5 MPID1
    ldsr    r0, 26, 5       ; SR26,5 MPID2
    ldsr    r0, 27, 5       ; SR27,5 MPID3
    ldsr    r0, 28, 5       ; SR28,5 MPID4
    ldsr    r0, 29, 5       ; SR29,5 MPID5
    ldsr    r0, 30, 5       ; SR30,5 MPID6
    ldsr    r0, 31, 5       ; SR31,5 MPID7
    ldsr    r0, 12, 5       ; SR12,5 MCI

    ;- Cache Operation Function Registers
    ldsr    r0, 16, 4       ; SR16,4 ICTAGL
    ldsr    r0, 17, 4       ; SR17,4 ICTAGH
    ldsr    r0, 18, 4       ; SR18,4 ICDATL
    ldsr    r0, 19, 4       ; SR19,4 ICDATH
    ldsr    r0, 28, 4       ; SR28,4 ICERR

    ;- Virtualization support function system register
    ldsr    r0, 20, 1       ; SR20,1 HVSB

    ;- Guest Context Register
    ldsr    r0,  0, 9       ; SR0,9  GMEIPC
    ldsr    r0,  2, 9       ; SR2,9  GMFEPC
    ldsr    r0, 19, 9       ; SR19,9 GMEBASE
    ldsr    r0, 20, 9       ; SR20,9 GMINTBP
    ldsr    r0, 28, 9       ; SR28,9 GMEIWR
    ldsr    r0, 29, 9       ; SR29,9 GMFEWR
    ldsr    r0,  6, 9       ; SR6,9  GMMEA
    ldsr    r0, 8, 9        ; SR8,9 GMMEI

$if 1
	; jump to entry point of each PE
	stsr	0, r10, 2		; get PEID or HTCFG0
	stsr	6, r11, 1		; get PID
	shr	24, r11
	cmp	6, r11
	bnl	.L1
	shr	16, r10			; get PEID (for G3)
.L1:
	cmp	0, r10
	bz	.L.entry_PE0
	cmp	1, r10
	bz	.L.entry_PE1
	cmp	2, r10
	bz	.L.entry_PE2
	cmp	3, r10
	bz	.L.entry_PE3
	cmp	4, r10
	bz	.L.entry_PE4
	cmp	5, r10
	bz	.L.entry_PE5
	cmp	6, r10
	bz	.L.entry_PE6
	cmp	7, r10
	bz	.L.entry_PE7
	cmp	8, r10
	bz	.L.entry_PE8
	cmp	9, r10
	bz	.L.entry_PE9
	cmp	10, r10
	bz	.L.entry_PE10
	cmp	11, r10
	bz	.L.entry_PE11
	cmp	12, r10
	bz	.L.entry_PE12
	cmp	13, r10
	bz	.L.entry_PE13
	cmp	14, r10
	bz	.L.entry_PE14
	cmp	15, r10
	bz	.L.entry_PE15
	addi	-16, r10, r0
	bz	.L.entry_PE16
	addi	-17, r10, r0
	bz	.L.entry_PE17
	addi	-18, r10, r0
	bz	.L.entry_PE18
	addi	-19, r10, r0
	bz	.L.entry_PE19
	addi	-20, r10, r0
	bz	.L.entry_PE20
	addi	-21, r10, r0
	bz	.L.entry_PE21
	addi	-22, r10, r0
	bz	.L.entry_PE22
	addi	-23, r10, r0
	bz	.L.entry_PE23
	addi	-24, r10, r0
	bz	.L.entry_PE24
	addi	-25, r10, r0
	bz	.L.entry_PE25
	addi	-26, r10, r0
	bz	.L.entry_PE26
	addi	-27, r10, r0
	bz	.L.entry_PE27
	addi	-28, r10, r0
	bz	.L.entry_PE28
	addi	-29, r10, r0
	bz	.L.entry_PE29
	addi	-30, r10, r0
	bz	.L.entry_PE30
	addi	-31, r10, r0
	bz	.L.entry_PE31
__exit:
	br	__exit

.L.entry_PE0:
	jarl    __preinit_pm0, lp
	jarl	_hdwinit_PE0, lp	; initialize hardware
	jr32	__cstart_pm0

.L.entry_PE1:
	jarl	_hdwinit_PE1, lp	; initialize hardware
    ;    jarl    _wait_gram_clear, lp
	jr32	__cstart_pm1

.L.entry_PE2:
	br	__exit
.L.entry_PE3:
	br	__exit
.L.entry_PE4:
	br	__exit
.L.entry_PE5:
	br	__exit
.L.entry_PE6:
	br	__exit
.L.entry_PE7:
	br	__exit
.L.entry_PE8:
	br	__exit
.L.entry_PE9:
	br	__exit
.L.entry_PE10:
	br	__exit
.L.entry_PE11:
	br	__exit
.L.entry_PE12:
	br	__exit
.L.entry_PE13:
	br	__exit
.L.entry_PE14:
	br	__exit
.L.entry_PE15:
	br	__exit
.L.entry_PE16:
	br	__exit
.L.entry_PE17:
	br	__exit
.L.entry_PE18:
	br	__exit
.L.entry_PE19:
	br	__exit
.L.entry_PE20:
	br	__exit
.L.entry_PE21:
	br	__exit
.L.entry_PE22:
	br	__exit
.L.entry_PE23:
	br	__exit
.L.entry_PE24:
	br	__exit
.L.entry_PE25:
	br	__exit
.L.entry_PE26:
	br	__exit
.L.entry_PE27:
	br	__exit
.L.entry_PE28:
	br	__exit
.L.entry_PE29:
	br	__exit
.L.entry_PE30:
	br	__exit
.L.entry_PE31:
	br	__exit
$endif

;-----------------------------------------------------------------------------
;	hdwinit_PE0
; Specify RAM addresses suitable to your system if needed.
;-----------------------------------------------------------------------------
	CLUSTER_0_RAM_ADDR	.set	0xFE000000
	CLUSTER_0_RAM_END	.set	0xFE07FFFF
	
	CLUSTER_2_RAM_ADDR	.set	0xFE400000
	CLUSTER_2_RAM_END	.set	0xFE5FFFFF
	
	CLUSTER_3_RAM_ADDR	.set	0xFE800000	; Retention RAM
	CLUSTER_3_RAM_END	.set	0xFE83FFFF
	
	LOCAL_RAM_SELF_ADDR	.set	0xFDE00000
	LOCAL_RAM_SELF_END	.set	0xFDE0FFFF
	
	RESF				.set	0xFF988500

	.align	2
_hdwinit_PE0:
	mov	lp, r14			; save return address
	
	; Clear RAM Areas
.CLUSTER_0:
	mov	CLUSTER_0_RAM_ADDR, r6
	mov	CLUSTER_0_RAM_END, r7
	jarl	_zeroclr8, lp
.CLUSTER_2:
	mov	CLUSTER_2_RAM_ADDR, r6
	mov	CLUSTER_2_RAM_END, r7
	jarl	_zeroclr8, lp
.CLUSTER_3: 
	; only clear Retention RAM (Cluster 3) when Power On Reset flag is set 
	ld.w RESF, r8
	andi 4, r8, r8
	bz  .RAM_SELF

	mov	CLUSTER_3_RAM_ADDR, r6
	mov	CLUSTER_3_RAM_END, r7
	jarl	_zeroclr8, lp
.RAM_SELF:
    ; Set GRAM clear flag
    mov  _g_GRAM_ClearFlag, r6
    mov  1, r7
    st.w r7, 0[r6]

	mov	LOCAL_RAM_SELF_ADDR, r6
	mov	LOCAL_RAM_SELF_END, r7
	jarl	_zeroclr8, lp

	mov	r14, lp
	jmp	[lp]

;-----------------------------------------------------------------------------
;	hdwinit_PE1
; Specify RAM addresses suitable to your system if needed.
;-----------------------------------------------------------------------------
	.align	2
_hdwinit_PE1:
	mov	lp, r14			; save return address

	; Clear RAM Areas
	mov	LOCAL_RAM_SELF_ADDR, r6
	mov	LOCAL_RAM_SELF_END, r7
	jarl	_zeroclr8, lp

	mov	r14, lp
	jmp	[lp]

;-----------------------------------------------------------------------------
;	_wait_gram_clear
; Wait until corrensponding flag is set by PE0
;-----------------------------------------------------------------------------
_wait_gram_clear:
    mov _g_GRAM_ClearFlag, r6
    mov 1, r7 
   ld.w 0[r6], r8
    cmp  r7, r8
    bz   _wait_gram_clear.2
_wait_gram_clear.1:
    snooze
    ld.w 0[r6], r8
    cmp  r7, r8
    bnz  _wait_gram_clear.1
_wait_gram_clear.2:
    jmp [lp]
    
;-----------------------------------------------------------------------------
;	zeroclr4
;-----------------------------------------------------------------------------

	.align	2
_zeroclr4:
	br	.L.zeroclr4.2
.L.zeroclr4.1:
	st.w	r0, [r6]
	add	4, r6
.L.zeroclr4.2:
	cmp	r6, r7
	bh	.L.zeroclr4.1
	jmp	[lp]

;-----------------------------------------------------------------------------
;	zeroclr8
;-----------------------------------------------------------------------------

	.align	2
_zeroclr8:
        mov r0, r8
        mov r0, r9
	br	.L.zeroclr8.2
.L.zeroclr8.1:
	st.dw	r8, [r6]
	add	8, r6
.L.zeroclr8.2:
	cmp	r6, r7
	bh	.L.zeroclr8.1
	jmp	[lp]

$ifdef USE_TABLE_REFERENCE_METHOD
;-----------------------------------------------------------------------------
;	set table reference method
;-----------------------------------------------------------------------------

	jmp	[lp]
$endif
;-------------------- end of start up module -------------------;
