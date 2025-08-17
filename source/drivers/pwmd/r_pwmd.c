/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : r_pwmd.c
* Component Version: 1.0.0
* Description      : This file implements the PWMD module.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "inc\common.h"
#include "r_pwmd.h"
#include "SmartConfigurator\ADCJ1\ADCJ1.h"

/***********************************************************************************************************************
Macros
***********************************************************************************************************************/
#define PWGCPRDSLq_00   0x0
#define PWGCPRDSLq_01   0x1
#define PWGCPRDSLq_10   0x2
#define PWGCPRDSLq_11   0x3

/***********************************************************************************************************************
Public functions
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: R_PWMD_Channel66Init
* Description  : Initializes the PWM channel 66.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PWMD_Channel66Init(void)
{
    /* PWGC stands for PWM signal generation generator. */
    SLPWG.PWGCPRDSL4.UINT32 |= PWGCPRDSLq_01 << (2*(66-64));
                           /* PWGC Period Selection Register: 01 -> PWGCPRD1 */
                                            /* PWGCPRDSL4: PWGC79 to PWGC64 */ 
    PWGC66.CTL.UINT16   = 0xc000u;          /* Use PWMCLK0 , PWMD Trigger on High*/
    PWGC66.CSDR.UINT16  = 0x0000u;          /* Delay = 0 */
    PWGC66.CTDR.UINT16  = 0x0100u;
    PWGC66.CRDR.UINT32  = 0x00000000u;      /* Duty cycle = 0. This will be updated via duty function */
    PWGC66.TCR.UINT8 	= 0x01; 
}

/***********************************************************************************************************************
* Function Name: R_PWMD_Channel67Init
* Description  : Initializes the PWM channel 67.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PWMD_Channel67Init(void)
{
    /* PWGC stands for PWM signal generation generator. */
    SLPWG.PWGCPRDSL4.UINT32 |= PWGCPRDSLq_01 << (2*(67-64));
                           /* PWGC Period Selection Register: 01 -> PWGCPRD1 */
                                            /* PWGCPRDSL4: PWGC79 to PWGC64 */ 
    PWGC67.CTL.UINT16   = 0xc000u;          /* Use PWMCLK0 , PWMD Trigger on High*/
    PWGC67.CSDR.UINT16  = 0x0U;
    PWGC67.CTDR.UINT16  = 0x0655u;
    PWGC67.CRDR.UINT32  = 0x00000000u;      /* Duty cycle = 0. This will be updated via duty function */
    PWGC67.TCR.UINT8	= 0x01;
}

/***********************************************************************************************************************
* Function Name: R_PWMD_Channel68Init
* Description  : Initializes the PWM channel 68.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PWMD_Channel68Init(void)
{
    /* PWGC stands for PWM signal generation generator. */
    SLPWG.PWGCPRDSL4.UINT32 |= PWGCPRDSLq_01 << (2*(68-64));
                           /* PWGC Period Selection Register: 01 -> PWGCPRD1 */
                                            /* PWGCPRDSL4: PWGC79 to PWGC64 */
    PWGC68.CTL.UINT16   = 0xc000u;          /* Use PWMCLK0 , PWMD Trigger on High*/
    PWGC68.CSDR.UINT16  = 0x0U;
    PWGC68.CTDR.UINT16  = 0x0B00u;
    PWGC68.CRDR.UINT32  = 0x00000000u;      /* Duty cycle = 0. This will be updated via duty function */ 
    PWGC68.TCR.UINT8	= 0x01;
}

/***********************************************************************************************************************
* Function Name: R_PWMD_ClockInit
* Description  : Initializes the PWM clock.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PWMD_ClockInit(void)
{
                                    /* Set ClockCycle of PWMCLK0 = PCLK/(2*(PWBA0BRS0[10:0])) */
    PWBA0.BRS0.UINT16 = 0x05U;      /* PWMCLKm count clock cycle = (PWBAnBRSm value × 2) × PCLK cycle */
    PWBA0.TS.UINT8   = 0x01u;       /* Starts Output of PWMCLK0 */
}

/***********************************************************************************************************************
* Function Name: R_PWMD_StartChannel
* Description  : Starts the PWM output of the chosen channel.
* Arguments    : uint32_t PWGC_Channel - PWM channel number
* Return Value : None
***********************************************************************************************************************/
void R_PWMD_StartChannel(uint32_t PWGC_Channel)
{
    if(PWGC_Channel <= 31)
        {
            SLPWG.C0.UINT32 |= 1u<<PWGC_Channel;
        }
    else if(PWGC_Channel <= 63)
        {
            SLPWG.C1.UINT32 |= 1u<<(PWGC_Channel - 32);
        }
    else{
            SLPWG.C2.UINT32 |= 1u<<(PWGC_Channel - 64);
        }
}

/***********************************************************************************************************************
* Function Name: R_PWMD_StopChannel
* Description  : Stops the PWM output of the chosen channel.
* Arguments    : uint32_t PWGC_Channel - PWM channel number
* Return Value : None
***********************************************************************************************************************/
void R_PWMD_StopChannel(uint32_t PWGC_Channel)
{
    if(PWGC_Channel <= 31)
        {
            
            SLPWG.C0.UINT32 &= ~(1u<<PWGC_Channel);
        }
    else if(PWGC_Channel <= 63)
        {
            SLPWG.C1.UINT32 &= ~(1u<<(PWGC_Channel - 32));
        }
    else{
            SLPWG.C2.UINT32 &= ~(1u<<(PWGC_Channel - 64));
        }
}

/***********************************************************************************************************************
* Function Name: R_PWMD_SetPeriod
* Description  : Sets the period of the PWM channels.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PWMD_SetPeriod(void)
{
      SLPWG.PWGCPRD0.UINT16 = 0x0FFFu;
      SLPWG.PWGCPRD1.UINT16 = 0x0FFFu;
      SLPWG.PWGCPRD2.UINT16 = 0xFFFFu;
      SLPWG.PWGCPRD3.UINT16 = 0xFFFFu;
}

/***********************************************************************************************************************
* Function Name: R_PWMD_Channel66DutyUpdate
* Description  : Updates the duty for the chosen PWM Channel.
* Arguments    : uint32_t duty - Duty cycle
* Return Value : None
***********************************************************************************************************************/
void R_PWMD_Channel66DutyUpdate(uint32_t duty)
{
    duty = duty + (uint16_t) PWGC66.CSDR.UINT16;
    PWGC66.CRDR.UINT32 = duty;
    if (duty < 0x300)
    {
	PWGC66.CTDR.UINT16 = 0x500;
    }
    else
    {
	PWGC66.CTDR.UINT16 = 0x200;
    }
    PWGC66.RDT.UINT8 = 1u;      /* Load the new duty cycle */
}

/***********************************************************************************************************************
* Function Name: R_PWMD_Channel67DutyUpdate
* Description  : Updates the duty for the chosen PWM Channel.
* Arguments    : uint32_t duty - Duty cycle
* Return Value : None
***********************************************************************************************************************/
void R_PWMD_Channel67DutyUpdate(uint32_t duty)
{
    duty = duty + (uint16_t) PWGC67.CSDR.UINT16;
    PWGC67.CRDR.UINT32 = duty;    
    if (duty < 0x300)
    {
	PWGC67.CTDR.UINT16 = 0x500;
    }
    else
    {
	PWGC67.CTDR.UINT16 = 0x200;
    }
    PWGC67.RDT.UINT8 = 1u;      /* Load the new duty cycle */
}

/***********************************************************************************************************************
* Function Name: R_PWMD_Channel67DutyUpdate
* Description  : Starts the PWM output of the chosen channel.
* Arguments    : uint32_t duty - Duty cycle
* Return Value : None
***********************************************************************************************************************/
void R_PWMD_Channel68DutyUpdate(uint32_t duty)
{
    duty = duty + (uint16_t) PWGC68.CSDR.UINT16;
    PWGC68.CRDR.UINT32 = duty;
    if (duty < 0x300)
    {
	PWGC68.CTDR.UINT16 = 0x500;
    }
    else
    {
	PWGC68.CTDR.UINT16 = 0x200;
    }
    
    
    PWGC68.RDT.UINT8 = 1u;      /* Load the new duty cycle */
}

/***********************************************************************************************************************
* Function Name: R_PWMD_DiagInit
* Description  : Initializes the PWM-Diagnostic function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PWMD_DiagInit(void)
{
   /* Configure PWM-Diag Mode A/D Setting Register
    * PVCRxy - PWMD Virtual Channel Register xy
    * b11:b8 CSULLMTBSx - These bits indicate the setting value of ADCJvPWDVCR.VCULLMTBS[3:0] that selects 
                          upper limit/lower limit table.
      b7:b6  SLADx - ADCJ Select Output to 0/1/2.
      b5:b0  GCTRLx - These bits indicate the setting value of the ADCAnPWDVCR.GCTRL[5:0] that selects physical channel
                      in ADCTL.
   */ 
    PWSD0.PVCR66.UINT32 = 0x00000140u;
    PWSD0.PVCR67.UINT32 = 0x00000141u;
    PWSD0.PVCR68.UINT32 = 0x00000142u;    
}

/***********************************************************************************************************************
* Function Name: R_PWMD_DiagStart
* Description  : Starts the PWM-Diagnostic function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PWMD_DiagStart(void)
{
    PWSD0.CTL.UINT8 |= 1u;          /* Start PWSA */
    PWSD0.CTL.UINT8 |= (1<<7);      /* Store data in PWDDIRx reg*/
}

/***********************************************************************************************************************
* Function Name: R_PWMD_DiagStop
* Description  : Stops the PWM-Diagnostic function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PWMD_DiagStop(void)
{
    PWSD0.CTL.UINT8 = 0u;           /* Stop PWSA */
}

/*****************************************************************************
** Function:    R_PWMD_PwdDiag_read
** Description: Configure AP0_0 to high impedant input mode of potentiometer 
**              POT1.
** Parameter:   None
** Return:      None
******************************************************************************/
uint16_t R_PWMD_PwmDiag_read(void)
{ 
  uint16_t PwmDiag_buffer;
  R_ADCJ1_ScanGroup4_GetPWMDiagResult(&PwmDiag_buffer);
  return PwmDiag_buffer;
}

/*****************************************************************************
** Function:    R_PWMD_PwmDiag_status
** Description: Note worthy registers to check for debug statuses. 
** Parameter:   None
** Return:      None
******************************************************************************/
void R_PWMD_PwmDiag_status(void)
{
    uint8_t   pwdDiag_ULL_CSR = ADCJ1.PWVCLMSR.BIT.PWVCLMS;
    uint8_t   pwdDiag_SG_ULL_CSR = ADCJ1.SGULCR4.UINT16;
    uint8_t   pwdDiag_ULL_CIER = ADCJ1.PWVCLMINTER.BIT.PWADULIE;
    uint32_t  pwdDiag_Data_Supplementary_66 = PWSD0.PWDDIR66.UINT32;
    uint32_t  pwdDiag_Data_Supplementary_67 = PWSD0.PWDDIR67.UINT32;
    uint32_t  pwdDiag_Data_Supplementary_68 = PWSD0.PWDDIR68.UINT32;
    uint8_t   pwdDiag_PWGC_OCL_66 = PWGC66.CTL.BIT.OCL;
    uint8_t   pwdDiag_PWGC_OCL_67 = PWGC67.CTL.BIT.OCL;
    uint8_t   pwdDiag_PWGC_OCL_68 = PWGC68.CTL.BIT.OCL;
}
