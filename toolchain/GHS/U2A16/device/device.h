//============================================================================
// PROJECT  :  Example project
//============================================================================
//                           C O P Y R I G H T
//============================================================================
// Copyright (c) 2011 by Renesas Electronics  GmbH. All rights reserved.
// Arcadiastr.10
// D-40472 Duesseldorf
// Germany
//============================================================================
//
// Warranty Disclaimer :
// Because the Product(s) is licensed free of charge, there is no warranty of
// any kind whatsoever and expressly disclaimed and excluded by NEC, either
// expressed or implied, including but not limited to those for non-
// infringement of intellectual property, merchantability and/or fitness for
// the particular purpose. NEC shall not have any obligation to maintain,
// service or provide bug fixes for the supplied Product(s) and/or the
// Application.
//
// Each User is solely responsible for determining the appropriateness of
// using the Product(s) and assumes all risks associated with its exercise
// of rights under this Agreement, including, but not limited to the risks
// and costs of program errors, compliance with applicable laws, damage to
// or loss of data, programs or equipment, and unavailability or
// interruption of operations.
//
// Limitation of Liability :
// In no event shall NEC be liable to the User for any incidental,
// consequential, indirect, or punitive damage (including but not limited to
// lost profits) regardless of whether such liability is based on breach of
// contract, tort, strict liability, breach of warranties, failure of
// essential purpose or otherwise and even if advised of the possibility of
// such damages. NEC shall not be liable for any services or products provided
// by third party vendors, developers or consultants identified or referred
// to the User by NEC in connection with the Product(s) and/or the
// Application.
//
//============================================================================
//
// Device specific main header file to be included in all source files.
//
//============================================================================

#ifndef   DEVICE_H
#define   DEVICE_H


#if 0
#ifdef __ghs
 #if (__GHS_VERSION_NUMBER > 201517)
 /* Suppress warnings about C99 specific unneccessary ";" at end of macro line */
 #pragma ghs nowarning 381
 #endif
/* Suppress warnings about double typedefs (same type only!) */
#pragma ghs nowarning 301
#endif
#endif /* 0 */

//============================================================================
// Includes
//============================================================================
#include <../include/v800/v800_ghs.h>
#include <ghs_barrier.h>
#include "io_macros_v2.h"

#include "dr7f702300b.dvf.h" 

#define U2A 

#include "cpu.h"


#ifndef __r_Error_t__
#define __r_Error_t__
typedef enum
{
  R_OK = 0u,
  R_ERROR,
  R_ERROR_NOTIFY,
  R_PARAMETER_MISSING,
  R_PARAMETER_RANGE,
  R_PARAMETER_INCORRECT,
  R_DATA_MISMATCH
} r_Error_t;   
#endif

#define DELAYBOUND_400  (11550)
#define DELAYBOUND_200  (DELAYBOUND_400/2)
#define DELAYBOUND_080  (DELAYBOUND_400/5)
#define DELAYBOUND_160  (DELAYBOUND_080*2)
#define DELAYBOUND_240  (DELAYBOUND_080*3)
#define DELAYBOUND_320  (DELAYBOUND_080*4)

#if (__GHS_VERSION_NUMBER <201713)
#error "Wrong compiler version! Please consider to update GHS compiler!
#endif

#ifndef protected_write
 #define protected_write(preg,reg,value)   preg=0xa5;\
                                          reg=value;\
                                          reg=~value;\
                                          reg=value
#endif


#define SNZWAIT 32 
#define CYCWAIT_200  (20000)
#define CYCWAIT_400  (40000)
#define CYCWAIT CYCWAIT_400
#define MAXWAIT (CYCWAIT/SNZWAIT) 

static inline void bWait( void) 
{ 
    int i; 
    for( i=0; i< MAXWAIT; i++) __SNOOZE(); 
} 

#define BARRIER_0_INIT()  { \
  __memory_changed(); \
  BARRBR0EN=0; \
  BARRBR0INIT=1; \
  BARRBR0EN=0xff; \
  }

#define BARRIER() { \
    __memory_changed(); \
    BARRBR0CHKS=1; \
    while( BARRBR0SYNCS == 0) __SNOOZE(); \
    }

#define BARRIER_0() { \
    __memory_changed(); \
    BARRBR0CHKS=1; \
    while( BARRBR0SYNCS == 0) __SNOOZE(); \
    }

#define BARRIER_1() { \
    __memory_changed(); \
    BARRBR1CHKS=1; \
    while( BARRBR1CHKS == 1) __SNOOZE(); \
    }


#define BARRIER_2() { \
    __memory_changed(); \
    BARRBR2CHKS=1; \
    while( BARRBR2CHKS == 1) __SNOOZE(); \
    }


#define BARRIER_3() { \
    __memory_changed(); \
    BARRBR3CHKS=1; \
    while( BARRBR3CHKS == 1) __SNOOZE(); \
    }


#define BARRIER_4() { \
    __memory_changed(); \
    BARRBR4CHKS=1; \
    while( BARRBR4CHKS == 1) __SNOOZE(); \
    }


#define BARRIER_5() { \
    __memory_changed(); \
    BARRBR5CHKS=1; \
    while( BARRBR5CHKS == 1) __SNOOZE(); \
    }


#define BARRIER_6() { \
    __memory_changed(); \
    BARRBR6CHKS=1; \
    while( BARRBR6CHKS == 1) __SNOOZE(); \
    }


#define BARRIER_7() { \
    __memory_changed(); \
    BARRBR7CHKS=1; \
    while( BARRBR7CHKS == 1) __SNOOZE()


#define DELAYBOUND  (DELAYBOUND_400)

#define KCE_EN  0xA5A5A501
#define KCE_DIS 0xA5A5A500


#define HAS_CLKINIT 1
extern void CLKINIT(void);

#define PE0   0
#define PE1   1
#define PE2   2
#define PE3   3
#define PE3   3 
#define PEMAX 4


/*=========================================================================== */
/* Defines                                                                    */
/*=========================================================================== */

#define PRAGMA(x)         _Pragma(#x)
#define __SHARED(type, x)	\
	PRAGMA( ghs startdata)	\
	PRAGMA( ghs section bss=".slbss")	\
	PRAGMA( ghs exported)	\
	type    x;             	\
	PRAGMA( ghs section) 	\
	PRAGMA( ghs enddata)

#if defined( PE0)
#define __PE0_SHARED(type, x)	\
	PRAGMA( ghs startdata)	\
	PRAGMA( ghs section bss=".pe0.slbss")	\
	PRAGMA( ghs exported)	\
	type    x;             	\
	PRAGMA( ghs section) 	\
	PRAGMA( ghs enddata)
#endif

#if defined( PE1)
#define __PE1_SHARED(type, x)	\
	PRAGMA( ghs startdata)	\
	PRAGMA( ghs section bss=".pe1.slbss")	\
	PRAGMA( ghs exported)	\
	type    x;             	\
	PRAGMA( ghs section) 	\
	PRAGMA( ghs enddata)
#endif

#if defined( PE2)
#define __PE2_SHARED(type, x)	\
	PRAGMA( ghs startdata)	\
	PRAGMA( ghs section bss=".pe2.slbss")	\
	PRAGMA( ghs exported)	\
	type    x;             	\
	PRAGMA( ghs section) 	\
	PRAGMA( ghs enddata)
#endif

#if defined( PE3)
#define __PE3_SHARED(type, x)	\
	PRAGMA( ghs startdata)	\
	PRAGMA( ghs section bss=".pe3.slbss")	\
	PRAGMA( ghs exported)	\
	type    x;             	\
	PRAGMA( ghs section) 	\
	PRAGMA( ghs enddata)
#endif

#if defined( PE4)
#define __PE4_SHARED(type, x)	\
	PRAGMA( ghs startdata)	\
	PRAGMA( ghs section bss=".pe4.slbss")	\
	PRAGMA( ghs exported)	\
	type    x;             	\
	PRAGMA( ghs section) 	\
	PRAGMA( ghs enddata)
#endif

#if defined( PE5)
#define __PE5_SHARED(type, x)	\
	PRAGMA( ghs startdata)	\
	PRAGMA( ghs section bss=".pe5.slbss")	\
	PRAGMA( ghs exported)	\
	type    x;             	\
	PRAGMA( ghs section) 	\
	PRAGMA( ghs enddata)
#endif

#define __EXPORTED(type, x)	\
	PRAGMA( ghs exported)  	\
	type    x


#define protected_write(preg,reg,value)   preg=0xa5;\
                                          reg=value;\
                                          reg=~value;\
                                          reg=value

/*=========================================================================== */
/* Useful type definitions                                                    */
/*=========================================================================== */
typedef void 	VOID;
typedef void *	PVOID;
typedef	void (*PFUNC)(void);
typedef	void (*PISR)(void);

/*=========================================================================== */
/* Declaration of external unused exception and interrupt handler             */
/*=========================================================================== */
extern void __unused_isr( void);
extern void __unused_eisr( void);
extern void __unused_ex( void);


#pragma ghs io __itbl 0x200
volatile const PFUNC __itbl[256];

#ifndef __CPU_H__
__inline unsigned long GetPEID( void)
{
	unsigned long	__t;

#if defined( __RH850G4MH__) || defined( __RH850G4KH__)
	/* unsigned int __STSR(__ghs_c_int__ regID, __ghs_c_int__ selID); */ 
	__t= (__STSR( 0, 2) & 0x7U);
#else
	__t= (__STSR( 0, 2) >>16) & 0x7U;
#endif

	return __t;
}
#endif


#endif  /* DEVICE_H */
