/*===========================================================================*/
/* Project:  F1x StarterKit Sample Software                                  */
/* Module :  cgi.c                                                           */
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
/* Source code to support commong gateways interface functions.              */
/*                                                                           */
/*===========================================================================*/

/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "inc\common.h"
#include "httpd.h"
#include "r_cgi.h"
#include <string.h>
#include "shared.h"
#include "apps\ui\r_ui.h"

/*===========================================================================*/
/* Prototypes */
/*===========================================================================*/
uint8_t loc_AtoI(uint8_t const *p_charVal);
const char *cgi_handler(int iIndex, int iNumParams, char const *pcParam[], char const *pcValue[]);
void httpd_cgi_init(void);
extern void PrintText(uint8_t* TextArray);

/*===========================================================================*/
/* Variables */
/*===========================================================================*/
#ifdef __GHS__
  #pragma ghs startdata 
  #pragma ghs section bss  = ".rbss"
  extern r_System_t g_SystemStatus;
  #pragma ghs section bss = default
  #pragma ghs enddata
#endif /* __GHS__ */

#ifdef __IAR__
  #pragma location="RETENTION_RAM.noinit"
  extern __no_init __brel23 r_System_t g_SystemStatus;
#endif /* __IAR__ */

#ifdef __CSP__
  #pragma section r0_disp32 "RETENTION_RAM"
  extern r_System_t g_SystemStatus;
  #pragma section default
#endif /* __CSP__ */

#if 1
const tCGI CGI_PAGE={"/commands.cgi", (tCGIHandler)cgi_handler};
tCGI CGI_TAB[1];
#endif
const uint8_t cgiResponse[] = "/commands.cgi";

/*===========================================================================*/
/* Functions */
/*===========================================================================*/
/*****************************************************************************
** Function:    cgi_handler
** Description: CGI handler implemented as defined by http daemon.
**              This function is called automatically by httpd with the 
**              corresponding parameters if CGI is enabled. Refer to httpd.h
**              for further information.
** Parameter:   iIndex - Index of CGI
**              iNumParams - Number of parameters in string
**              pcParam - Pointer to parameter strings
**              pcValue - Pointer to values corresponding to parameter strings
** Return:      Pointer to return path char string 
******************************************************************************/
#if 0
const char *cgi_handler(int iIndex, int iNumParams, char const *pcParam[], char const *pcValue[])
{
	int i;
	
	for(i=0; i<iNumParams; i++)
	{
		if(strcmp(pcParam[i], "mode") == 0)
			{
				if(strcmp(pcValue[i], "mode1")==0)
					{
					    if(g_SystemStatus.CurrentMode != R_MODE1)
						{
						    g_SystemStatus.CurrentMode=R_MODE1;
						    PrintText("\r>>Website-button pressed: switch to mode 1...         \n\r");
						}
					}
				if(strcmp(pcValue[i], "mode2")==0)
					{
						if(g_SystemStatus.CurrentMode != R_MODE2)
						{
						    g_SystemStatus.CurrentMode=R_MODE2;
						    PrintText("\r>>Website-button pressed: switch to mode 2...         \n\r");
						}
					}	
				if(strcmp(pcValue[i], "deepstop")==0)
					{
						g_SystemStatus.CurrentMode=R_DEEPSTOP;
						PrintText("\r>>Website-button pressed: enter DeepSTOP...              \n\r");
					}
				if(strcmp(pcValue[i], "selftest")==0)
					{
						
					}
				else
					{
						
					}
				}
        
        if(strcmp(pcParam[i], "rgb") == 0)
            {
                g_SystemStatus.RGB[0] = (loc_AtoI(pcValue[i]) * 0x10);      /* Set value for red LED */
                g_SystemStatus.RGB[1] = (loc_AtoI(pcValue[i]+2) * 0x10);    /* Set value for green LED */
                g_SystemStatus.RGB[2] = (loc_AtoI(pcValue[i]+4) * 0x10);    /* Set value for blue LED */
                
            }
		}
	return cgiResponse;
}
#else
const char *cgi_handler(int iIndex, int iNumParams, char const *pcParam[], char const *pcValue[])
{
	int i;
	
	for(i=0; i<iNumParams; i++)
	{

		if(strcmp(pcParam[i], "mode") == 0)
		{
			if(strcmp(pcValue[i], "1")==0)
			{
				if(g_SystemStatus.CurrentMode != R_MODE1)
				{
					g_SystemStatus.UiStatus->RequestedMode=R_UiMode1;
					
				}
			}
			if(strcmp(pcValue[i], "2")==0)
			{
				if(g_SystemStatus.CurrentMode != R_MODE2)
				{
					g_SystemStatus.UiStatus->RequestedMode=R_UiMode2;
				}
			}
			if(strcmp(pcValue[i], "reset")==0)
			{
				if(g_SystemStatus.CurrentMode != R_MODE2)
				{
					g_SystemStatus.UiStatus->RequestedMode=R_UiReset;
				}
			}	
		
		}
      
    }
	return (const char *)cgiResponse;
}
#endif

/*****************************************************************************
** Function:    httpd_cgi_init
** Description: CGI initialization functions implemented as defined by httpd.
** Parameter:   None
** Return:      None
******************************************************************************/
void httpd_cgi_init(void)
{
	CGI_TAB[0]=CGI_PAGE;
	http_set_cgi_handlers(CGI_TAB, 1);
}

/*****************************************************************************
** Function:    loc_AtoI
** Description: Convert two consecutive ASCII chars to uint8_T integer.
** Parameter:   p_charVal - Pointer to first ASCII char
** Return:      loc_conversion - Result of integer conversion 
******************************************************************************/
uint8_t loc_AtoI(const uint8_t *p_charVal)
{
    uint8_t loc_conversion, loc_char1, loc_char2;
    
    loc_char1 = *p_charVal;     /* Get first char */
    loc_char2 = *(p_charVal+1); /* Get second char */
    
    if(loc_char1 >= 97)     /* Convert lower case letters */
        loc_char1 -= 87;
    else if(loc_char1 >= 65)/* Convert upper case letters */
        loc_char1 -= 55;
    else if(loc_char1 >= 48)/* Convert numbers */
        loc_char1 -= 48;
        
    if(loc_char2 >= 97)     /* Convert lower case letters */
        loc_char2 -= 87;
    else if(loc_char2 >= 65)/* Convert upper case letters */
        loc_char2 -= 55;
    else if(loc_char2 >=48)/* Convert numbers */
        loc_char2 -= 48;
    
    /* Sum up */
    loc_conversion = loc_char2;
    loc_conversion += loc_char1 * 16;
    
    /* Return result */
    return loc_conversion;
}
