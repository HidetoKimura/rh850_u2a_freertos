/*===========================================================================*/
/* Project:  F1x StarterKit Sample Software                                  */
/* Module :  ssi.c                                                           */
/* Version:  V1.00                                                           */
/*===========================================================================*/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2017 by Renesas Electronics Europe GmbH,                    */
/*               a company of the Renesas Electronics Corporation            */
/*===========================================================================*/
/* In case of any question please do not hesitate to contact:                */
/*                                                                           */
/*        ABG Software Tool Support                                          */
/*                                                                           */
/*        Renesas Electronics Europe GmbH                                    */
/*        Arcadiastrasse 10                                                  */
/*        D-40472 Duesseldorf, Germany                                       */
/*                                                                           */
/*        e-mail: software_support-eu@lm.renesas.com                         */
/*        FAX:   +49 - (0)211 / 65 03 - 11 31                                */
/*                                                                           */
/*===========================================================================*/
/* Warranty Disclaimer                                                       */
/*                                                                           */
/* Because the Product(s) is licensed free of charge, there is no warranty   */
/* of any kind whatsoever and expressly disclaimed and excluded by Renesas,  */
/* either expressed or implied, including but not limited to those for       */
/* non-infringement of intellectual property, merchantability and/or         */
/* fitness for the particular purpose.                                       */
/* Renesas shall not have any obligation to maintain, service or provide bug */
/* fixes for the supplied Product(s) and/or the Application.                 */
/*                                                                           */
/* Each User is solely responsible for determining the appropriateness of    */
/* using the Product(s) and assumes all risks associated with its exercise   */
/* of rights under this Agreement, including, but not limited to the risks   */
/* and costs of program errors, compliance with applicable laws, damage to   */
/* or loss of data, programs or equipment, and unavailability or             */
/* interruption of operations.                                               */
/*                                                                           */
/* Limitation of Liability                                                   */
/*                                                                           */
/* In no event shall Renesas be liable to the User for any incidental,       */
/* consequential, indirect, or punitive damage (including but not limited    */
/* to lost profits) regardless of whether such liability is based on breach  */
/* of contract, tort, strict liability, breach of warranties, failure of     */
/* essential purpose or otherwise and even if advised of the possibility of  */
/* such damages. Renesas shall not be liable for any services or products    */
/* provided by third party vendors, developers or consultants identified or  */
/* referred to the User by Renesas in connection with the Product(s) and/or  */
/* the Application.                                                          */
/*                                                                           */
/*===========================================================================*/
/* History:                                                                  */
/*              V1.00: Initial version                                       */
/*                                                                           */
/*===========================================================================*/
/*                                                                           */
/* Source code to support server side include.                               */
/*                                                                           */
/*===========================================================================*/

/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "inc\common.h"
#include "httpd.h"
#include "r_ssi.h"
#include "modules\eth\r_eth.h"
#include "shared.h"

/*===========================================================================*/
/* Variables */
/*===========================================================================*/
 
const char *SSITags[]={
	"pe0Load",	// 0
	"pe1Load",	// 1
	"pe2Load",	// 2
	"runtime",	// 3
	"poti",	    // 4
	"enc",	    // 5
	"ledr",	    // 6
	"ledg",	    // 7
	"ledb",	    // 8
	"led4",	    // 9
	"led5",	    // 10
	"led6",	    // 11
	"led7",	    // 12
	"ledring",	// 13
    "ftx",		// 14
	"frx",		// 15
	"mode",	    // 16
	};


// extern u32_T g_Pot1Value;
extern uint32_t g_CpuLoad;
extern ethernet_t eth_config[];

/*===========================================================================*/
/* Functions */
/*===========================================================================*/
/*****************************************************************************
** Function:    httpd_SSIHandler
** Description: SSI handler implemented as defined by http daemon.
**              This function is called automatically by httpd with the 
**              corresponding parameters if SSI is enabled. Refer to httpd.h
**              for further information.
** Parameter:   iIndex - SSI index
**              pcInsert - Pointer to location in ssi-file where string has 
**                         to be inserted
**              iInsertLen - size of the buffer pointed to by pcInsert
** Return:      Number of chars to be inserted
******************************************************************************/
uint16_t httpd_SSIHandler(int iIndex, char *pcInsert, int iInsertLen)
{
    // u16_T r=0, g=0, b=0; /* Local RGB values */
    
	switch(iIndex)
	{   
		case 0: /* pe0Load */
			sprintf(pcInsert,"%16u", 0);
			return 5;
		case 1: /* pe1Load */
			sprintf(pcInsert,"%16u", 0);
			return 5;
			
		case 2: /* pe2load */
			sprintf(pcInsert,"%16u", 0);
			return 16;
			
		case 3: /* runtime */
			sprintf(pcInsert,"%16u", g_SystemStatus.RunTimeMs);
			return 16;
			
		case 4: /* poti */
			sprintf(pcInsert,"%16u",  g_SystemStatus.UiStatus->poti);
			return 16;
			
		case 5: /*enc */
			sprintf(pcInsert,"%16u", g_SystemStatus.UiStatus->enc);
			return 16;
			
		case 6: /* ledr */
			sprintf(pcInsert,"%16u", g_SystemStatus.LedStatus->Leds[LEDR]);
			return 16;
			
		case 7: /* ledg */
			sprintf( pcInsert,"%3i", g_SystemStatus.LedStatus->Leds[LEDG]);   // g_cpuLoad);
			return 3;
			
        case 8: /* ledb */
			sprintf(pcInsert,"%16u", g_SystemStatus.LedStatus->Leds[LEDB]);
            return 16;
        
        case 9: /* led4 */
			sprintf(pcInsert,"%16u", g_SystemStatus.LedStatus->Leds[LED4]);
            return 16;
        
        case 10: /* led5 */
			sprintf(pcInsert,"%16u", g_SystemStatus.LedStatus->Leds[LED5]);
            return 16;
            
        case 11: /* led6 */
			sprintf(pcInsert,"%16u", g_SystemStatus.LedStatus->Leds[LED6]);
            return 16;

		case 12: /* led7 */
			sprintf(pcInsert,"%16u", g_SystemStatus.LedStatus->Leds[LED7]);
			return 16;
			
		case 13: /* ledring */
			sprintf(pcInsert,"%16u", g_SystemStatus.LedStatus->LEDRing);
			return 16;
			
		case 14: /* ftx */
			sprintf(pcInsert,"%16u", eth_config[0].sent_frames);
	
			return 16;
			
		case 15: /* frx */
			sprintf(pcInsert,"%16u", eth_config[0].received_frames);

			return 16;
			
		case 16: /* mode */
			sprintf(pcInsert,"%16u", g_SystemStatus.UiStatus->CurrentMode);
			return 16;	

		default:
			return 0;
	}
}

/*****************************************************************************
** Function:    httpd_ssi_init
** Description: SSI initialization as defined by http daemon.
** Parameter:   None
** Return:      None
******************************************************************************/
void httpd_ssi_init(void)
{
  http_set_ssi_handler(httpd_SSIHandler, SSITags, sizeof(SSITags)/sizeof(SSITags[0]));
}


