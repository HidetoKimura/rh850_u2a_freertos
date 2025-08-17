;-----------------------------------------------------------------------------
;	section initialize table
;-----------------------------------------------------------------------------
	.section	".INIT_DSEC.const", const
	.align	4
	.dw	#__s.data.cmn,	#__e.data.cmn,	#__s.data.cmn.R

	.section	".INIT_BSEC.const", const
	.align	4
	.dw	#__s.bss.cmn,	#__e.bss.cmn

;-----------------------------------------------------------------------------
;	startup
;-----------------------------------------------------------------------------
	.section ".text.cmn", text
	.public	__cstart_shared
	.align	2
__cstart_shared:
	mov	lp, r20			; save return address
	
	mov	#__s.INIT_DSEC.const, r6
	mov	#__e.INIT_DSEC.const, r7
	mov	#__s.INIT_BSEC.const, r8
	mov	#__e.INIT_BSEC.const, r9
	
	jarl32	__INITSCT_RH, lp	;  initialize RAM area
	
	mov	r20, lp
	jmp	[lp]
	
;-----------------------------------------------------------------------------
;	dummy section
;-----------------------------------------------------------------------------
	.section	".data.cmn", data
.L.dummy.data.cmn:
	.section	".bss.cmn", bss
.L.dummy.bss.cmn:
	.section	".const.cmn", const
.L.dummy.const.cmn:
	.section	".text.cmn", text
.L.dummy.text.cmn:
	.section	".text", text
.L.dummy.text:
	.section	"RETENTION_RAM.bss.cmn", bss
.L.dummy.RETENTION_RAM.bss.cmn:
;-------------------- end of start up module -------------------;
