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

#include <device.h>

#include <../src/libsys/indos.h>
#include <../src/libsys/ind_io.h>

//--------------------------------------------------------------------------
// variables
//--------------------------------------------------------------------------
#pragma ghs startdata			// locate to GRAM
#pragma ghs section bss=".slsync"	// to section ".slsync"
__EXPORTED( unsigned int, ThreadUnlocked);	// for mutual exclusion
__EXPORTED( unsigned int, ThreadLocked);	// for mutual exclusion
__EXPORTED( unsigned int, PE_Started);		// for mutual exclusion
#pragma ghs section			//
#pragma ghs enddata			// locate default	



void __spinLockRW( PVOID pMEVREG);
void __spinUnlockRW( PVOID pMEVREG);

void __spinLockRW( PVOID pMEVREG)
{
	unsigned long __pe= GetPEID();

	/* return without lock, if PE already owner */
	if( __pe == *(unsigned long *)pMEVREG)
		return;

	while( *(unsigned long *) pMEVREG !=0 )	/* Active lock exists */
	{
		__SNOOZE();	/* Indicate by LED on P8 */
	}
	__INTERLOCKED_OR( (unsigned long *)pMEVREG, __pe);	/* get the resource and lock it */
}

/* Release global lock */
void __spinUnlockRW( PVOID pMEVREG)
{
	*(unsigned long *)pMEVREG = 0L;	/* clear the PE */
}


#if !defined(MINIMAL_STARTUP)
/* Acquire global lock.  Blocks until the lock becomes available. */


#endif /* !defined(MINIMAL_STARTUP) */
