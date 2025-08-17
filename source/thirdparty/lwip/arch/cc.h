/*
 * Copyright (c) 2001, Swedish Institute of Computer Science.
 * All rights reserved. 
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 3. Neither the name of the Institute nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE. 
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: cc.h,v 1.1 2007/06/14 12:34:09 kieranm Exp $
 */
#ifndef __CC_H__
#define __CC_H__
#include "inc\common.h"

#define U16_F "hu"
#define S16_F "hd"
#define X16_F "hx"
#define U32_F "u"
#define S32_F "d"
#define X32_F "x"

#define BYTE_ORDER   LITTLE_ENDIAN  

#define PACK_STRUCT_FIELD(x) x//; #pragma STRUCT_ALIGN(x,1)
#define PACK_STRUCT_STRUCT
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_END

#include <stdio.h>

#define LWIP_NO_INTTYPES_H 1

//#define LWIP_NO_STDINT_H 0
//typedef uint8_t   u8_t;
//typedef int8_t    s8_t;
//typedef uint16_t  u16_t;
//typedef int16_t   s16_t;
//typedef uint32_t  u32_t;
//typedef int32_t   s32_t;
////typedef uint64_t  u64_t;
////typedef int64_t   s64_t;
//typedef unsigned int * uintptr_t;
//typedef uintptr_t mem_ptr_t;


#ifndef LWIP_PLATFORM_DIAG
#define LWIP_PLATFORM_DIAG(x)	do {printf x;} while(0)
#endif

#ifndef LWIP_PLATFORM_ASSERT
#define LWIP_PLATFORM_ASSERT(x) do {} while(0)
#endif

/* Use system specific Byteswap function */
#define LWIP_PLATFORM_BYTESWAP 1
#define LWIP_PLATFORM_HTONS(x) sys_htons(x)
#define LWIP_PLATFORM_HTONL(x) sys_htonl(x)
//u16_t sys_htons(u16_t n);
//u32_t sys_htonl(u32_t n);
#define  sys_arch_protect(lev) DI();
#define  sys_arch_unprotect(lev) EI(); 
typedef unsigned int sys_prot_t;
#endif /* __CC_H__ */
