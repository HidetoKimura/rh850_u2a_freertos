
$include "contextop.h"


;------------------------------------------------------------------------------
	.public _Intfunc_INTTAUD2I0_pre
	.align	2
_Intfunc_INTTAUD2I0_pre:
	
	portSAVE_CONTEXT
	
	jarl	_Intfunc_INTTAUD2I0, lp
	
	portRESTORE_CONTEXT
	
	eiret
