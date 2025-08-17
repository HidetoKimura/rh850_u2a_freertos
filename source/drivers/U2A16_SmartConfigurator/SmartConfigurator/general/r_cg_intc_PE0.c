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
* Copyright (C) 2018, 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : r_cg_intc_PE0.c
* Version          : 1.0.140
* Device(s)        : R7F702300BFABA
* Description      : None
***********************************************************************************************************************/
/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
#define R_Interrupt_Initialize_ForPE R_Interrupt_Initialize_ForPE0
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
void R_Interrupt_Initialize_ForPE(void)
{
    /* Set INTADCJ1ERR setting */
    INTC2.EIC232.BIT.EIMK232 = _INT_PROCESSING_DISABLED;
    INTC2.EIC232.BIT.EIRF232 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC232.BIT.EITB232 = _INT_TABLE_VECTOR;
    INTC2.EIC232.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD232.BIT.PEID = _INT_CPU_PE0;
    /* Set INTADCJ1I4 setting */
    INTC2.EIC237.BIT.EIMK237 = _INT_PROCESSING_DISABLED;
    INTC2.EIC237.BIT.EIRF237 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC237.BIT.EITB237 = _INT_TABLE_VECTOR;
    INTC2.EIC237.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD237.BIT.PEID = _INT_CPU_PE0;
    /* Set INTMSPI3ERR setting */
    INTC2.EIC271.BIT.EIMK271 = _INT_PROCESSING_DISABLED;
    INTC2.EIC271.BIT.EIRF271 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC271.BIT.EITB271 = _INT_TABLE_VECTOR;
    INTC2.EIC271.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD271.BIT.PEID = _INT_CPU_PE0;
    /* Set INTMSPI3FE setting */
    INTC2.EIC270.BIT.EIMK270 = _INT_PROCESSING_DISABLED;
    INTC2.EIC270.BIT.EIRF270 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC270.BIT.EITB270 = _INT_TABLE_VECTOR;
    INTC2.EIC270.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD270.BIT.PEID = _INT_CPU_PE0;
    /* Set INTMSPI3RX setting */
    INTC2.EIC269.BIT.EIMK269 = _INT_PROCESSING_DISABLED;
    INTC2.EIC269.BIT.EIRF269 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC269.BIT.EITB269 = _INT_TABLE_VECTOR;
    INTC2.EIC269.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD269.BIT.PEID = _INT_CPU_PE0;
    /* Set INTMSPI3TX setting */
    INTC2.EIC268.BIT.EIMK268 = _INT_PROCESSING_DISABLED;
    INTC2.EIC268.BIT.EIRF268 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC268.BIT.EITB268 = _INT_TABLE_VECTOR;
    INTC2.EIC268.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD268.BIT.PEID = _INT_CPU_PE0;
    /* Set INTOSTM0TINT setting */
    INTC2.EIC199.BIT.EIMK199 = _INT_PROCESSING_DISABLED;
    INTC2.EIC199.BIT.EIRF199 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC199.BIT.EITB199 = _INT_TABLE_VECTOR;
    INTC2.EIC199.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD199.BIT.PEID = _INT_CPU_PE0;
    /* Set INTP4 setting */
    INTC2.EIC548.BIT.EIMK548 = _INT_PROCESSING_DISABLED;
    INTC2.EIC548.BIT.EIRF548 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC548.BIT.EITB548 = _INT_TABLE_VECTOR;
    INTC2.EIC548.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD548.BIT.PEID = _INT_CPU_PE0;
    /* Set INTP5 setting */
    INTC2.EIC549.BIT.EIMK549 = _INT_PROCESSING_DISABLED;
    INTC2.EIC549.BIT.EIRF549 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC549.BIT.EITB549 = _INT_TABLE_VECTOR;
    INTC2.EIC549.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD549.BIT.PEID = _INT_CPU_PE0;
    /* Set INTP21 setting */
    INTC2.EIC565.BIT.EIMK565 = _INT_PROCESSING_DISABLED;
    INTC2.EIC565.BIT.EIRF565 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC565.BIT.EITB565 = _INT_TABLE_VECTOR;
    INTC2.EIC565.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD565.BIT.PEID = _INT_CPU_PE0;
    /* Set INTRIIC0EE setting */
    INTC2.EIC685.BIT.EIMK685 = _INT_PROCESSING_DISABLED;
    INTC2.EIC685.BIT.EIRF685 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC685.BIT.EITB685 = _INT_TABLE_VECTOR;
    INTC2.EIC685.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD685.BIT.PEID = _INT_CPU_PE0;
    /* Set INTRIIC0RI setting */
    INTC2.EIC686.BIT.EIMK686 = _INT_PROCESSING_DISABLED;
    INTC2.EIC686.BIT.EIRF686 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC686.BIT.EITB686 = _INT_TABLE_VECTOR;
    INTC2.EIC686.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD686.BIT.PEID = _INT_CPU_PE0;
    /* Set INTRIIC0TEI setting */
    INTC2.EIC688.BIT.EIMK688 = _INT_PROCESSING_DISABLED;
    INTC2.EIC688.BIT.EIRF688 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC688.BIT.EITB688 = _INT_TABLE_VECTOR;
    INTC2.EIC688.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD688.BIT.PEID = _INT_CPU_PE0;
    /* Set INTRIIC0TI setting */
    INTC2.EIC687.BIT.EIMK687 = _INT_PROCESSING_DISABLED;
    INTC2.EIC687.BIT.EIRF687 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC687.BIT.EITB687 = _INT_TABLE_VECTOR;
    INTC2.EIC687.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD687.BIT.PEID = _INT_CPU_PE0;
    /* Set INTRLIN39UR0 setting */
    INTC2.EIC453.BIT.EIMK453 = _INT_PROCESSING_DISABLED;
    INTC2.EIC453.BIT.EIRF453 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC453.BIT.EITB453 = _INT_TABLE_VECTOR;
    INTC2.EIC453.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD453.BIT.PEID = _INT_CPU_PE0;
    /* Set INTRLIN39UR1 setting */
    INTC2.EIC454.BIT.EIMK454 = _INT_PROCESSING_DISABLED;
    INTC2.EIC454.BIT.EIRF454 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC454.BIT.EITB454 = _INT_TABLE_VECTOR;
    INTC2.EIC454.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD454.BIT.PEID = _INT_CPU_PE0;
    /* Set INTRLIN39UR2 setting */
    INTC2.EIC455.BIT.EIMK455 = _INT_PROCESSING_DISABLED;
    INTC2.EIC455.BIT.EIRF455 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC455.BIT.EITB455 = _INT_TABLE_VECTOR;
    INTC2.EIC455.UINT16 &= _INT_PRIORITY_LOWEST;
    INTC2.EIBD455.BIT.PEID = _INT_CPU_PE0;
}
