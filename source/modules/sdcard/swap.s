;-- Function name: sys_htonl
;-------------------------------------------------------------------------------------------------------------
;--
;-- Function performs byteswap of word
;--
;-- @param[out]    r6:  u32_t n        word to be swapped
;-- @return                            swapped word
;--
;-------------------------------------------------------------------------------------------------------------

  PUBLIC _sys_htonl
  SECTION     .text:CODE:ROOT
_sys_htonl:
	BSW r6, r10
        JMP [lp]         ; Jump to label lp
	

;-- Function name: sys_htons
;-------------------------------------------------------------------------------------------------------------
;--
;-- Function performs byteswap of short
;--
;-- @param[out]    r6:  u16_t n        short to be swapped
;-- @return                            swapped short
;--
;-------------------------------------------------------------------------------------------------------------
  PUBLIC _sys_htons
  SECTION     .text:CODE:ROOT

_sys_htons:
	BSH r6, r10
	JMP [lp]

	

