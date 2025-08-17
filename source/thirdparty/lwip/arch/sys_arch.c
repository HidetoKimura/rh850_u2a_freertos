
#include "lwip/opt.h"
#include "arch/sys_arch.h"
#include "shared.h"


u32_t
sys_now(void)
{

        return g_SystemStatus.RunTimeMs;

}

#if 0
u16_t 
sys_htons(u16_t n)
{
	asm("bsh r6, r10");
}

u32_t 
sys_htonl(u32_t n)
{
	asm("bsw r6, r10");
}
#endif

