# Function name: sys_htonl
#------------------------------------------------------------------------------------------------------------
#-
#- Function performs byteswap of word
#-
#- @param[out]    r6:  u32_t n        word to be swapped
#- @return                            swapped word
#-
#-----------------------------------------------------------------------------------------------------------*/
.public _sys_htonl

_sys_htonl:
	bsw r6, r10
	jmp [lp]
	

#- Function name: sys_htons
#------------------------------------------------------------------------------------------------------------
#-
#- Function performs byteswap of short
#-
#- @param[out]    r6:  u16_t n        short to be swapped
#- @return                            swapped short
#-
#------------------------------------------------------------------------------------------------------------
.public _sys_htons

_sys_htons:
	bsh r6, r10
	jmp [lp]