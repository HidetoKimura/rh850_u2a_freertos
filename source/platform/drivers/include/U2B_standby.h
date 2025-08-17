/******************************************************************************* 
* DISCLAIMER 
* This software is supplied by Renesas Electronics Corporation and is only  
* intended for use with Renesas products. No other uses are authorized. This  
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE  
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. 
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS  
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE  
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. 
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software. By using this software, 
* you agree to the additional terms and conditions found by accessing the  
* following link: 
* http://www.renesas.com/disclaimer 
* 
* Copyright (C) 2023 Renesas Electronics Corporation. All rights reserved.     
*******************************************************************************/
/******************************************************************************* 
* File Name    : U2B_standby.h
* Version      : 1.00
* Device(s)    : RH850/U2B
* Description  : This is header file for stand-by controller configuration.
*******************************************************************************/

#ifndef	__U2B_standby_H__
#define	__U2B_standby_H__

#include "U2x_typedef.h"

//////////////////////////////////////////////////////////////////////
// Const Value Definition
//////////////////////////////////////////////////////////////////////
		

//////////////////////////////////////////////////////////////////////
// Register Definition
//////////////////////////////////////////////////////////////////////	
// module standby (ISO area)
#define	rMSR_RSCFD     	(*(volatile unsigned long  *)(0xFF981000U))	// Module Standby Register for RS-CANFD [PBG20 #2/rMSRKCPROT] 
#define	rMSR_FLXA      	(*(volatile unsigned long  *)(0xFF981010U))	// Module Standby Register for FLXA [PBG20 #2/rMSRKCPROT] 
#define	rMSR_GTM       	(*(volatile unsigned long  *)(0xFF981020U))	// Module Standby Register for GTM [PBG20 #2/rMSRKCPROT] 
#define	rMSR_ETN       	(*(volatile unsigned long  *)(0xFF981030U))	// Module Standby Register for ETN [PBG20 #2/rMSRKCPROT] 
#define	rMSR_RSENT     	(*(volatile unsigned long  *)(0xFF981040U))	// Module Standby Register for RSENT [PBG20 #2/rMSRKCPROT] 
#define	rMSR_MSPI      	(*(volatile unsigned long  *)(0xFF981050U))	// Module Standby Register for MSPI [PBG20 #2/rMSRKCPROT] 
#define	rMSR_RLIN3     	(*(volatile unsigned long  *)(0xFF981060U))	// Module Standby Register for RLIN3 [PBG20 #2/rMSRKCPROT] 
#define	rMSR_DSADC_CADC	(*(volatile unsigned long  *)(0xFF981070U))	// Module Standby Register for DS-ADC and Cyclic-ADC [PBG20 #2/rMSRKCPROT] 
#define	rMSR_ADCK_ISO  	(*(volatile unsigned long  *)(0xFF981078U))	// Module Standby Register for SAR- ADC [PBG20 #2/rMSRKCPROT] 
#define	rMSR_MMCA      	(*(volatile unsigned long  *)(0xFF981090U))	// Module Standby Register for MMCA [PBG20 #2/rMSRKCPROT] 
#define	rMSR_ENCA      	(*(volatile unsigned long  *)(0xFF9810A0U))	// Module Standby Register for ENCA [PBG20 #2/rMSRKCPROT] 
#define	rMSR_PSI5      	(*(volatile unsigned long  *)(0xFF9810B0U))	// Module Standby Register for PSI5 [PBG20 #2/rMSRKCPROT] 
#define	rMSR_PSI5S     	(*(volatile unsigned long  *)(0xFF9810C0U))	// Module Standby Register for PSI5-S [PBG20 #2/rMSRKCPROT] 
#define	rMSR_RHSIF     	(*(volatile unsigned long  *)(0xFF9810E0U))	// Module Standby Register for RHSIF [PBG20 #2/rMSRKCPROT] 
#define	rMSR_RHSB      	(*(volatile unsigned long  *)(0xFF9810E4U))	// Module Standby Register for RHSB [PBG20 #2/rMSRKCPROT] 
#define	rMSR_RIIC      	(*(volatile unsigned long  *)(0xFF9810F0U))	// Module Standby Register for RIIC [PBG20 #2/rMSRKCPROT] 
#define	rMSR_SFMA      	(*(volatile unsigned long  *)(0xFF981110U))	// Module Standby Register for SFMA [PBG20 #2/rMSRKCPROT] 
#define	rMSR_TAPA      	(*(volatile unsigned long  *)(0xFF981120U))	// Module Standby Register for TAPA [PBG20 #2/rMSRKCPROT] 
#define	rMSR_TAUD      	(*(volatile unsigned long  *)(0xFF981130U))	// Module Standby Register for TAUD [PBG20 #2/rMSRKCPROT] 
#define	rMSR_TPBA      	(*(volatile unsigned long  *)(0xFF981150U))	// Module Standby Register for TPBA [PBG20 #2/rMSRKCPROT] 
#define	rMSR_TSG3      	(*(volatile unsigned long  *)(0xFF981160U))	// Module Standby Register for TSG3 [PBG20 #2/rMSRKCPROT] 
#define	rMSR_OSTM      	(*(volatile unsigned long  *)(0xFF981180U))	// Module Standby Register for OSTM [PBG20 #2/rMSRKCPROT] 
#define	rMSR_ATU       	(*(volatile unsigned long  *)(0xFF9811B0U))	// Module Standby Register for ATU6 [PBG20 #2/rMSRKCPROT] 
#define	rMSR_DFE       	(*(volatile unsigned long  *)(0xFF9811C0U))	// Module Standby Register for DFE [PBG20 #2/rMSRKCPROT] 
#define	rMSR_DFP       	(*(volatile unsigned long  *)(0xFF9811D0U))	// Module Standby Register for DFP [PBG20 #2/rMSRKCPROT] 
#define	rMSR_RDC       	(*(volatile unsigned long  *)(0xFF9811E0U))	// Module Standby Register for RDC3 [PBG20 #2/rMSRKCPROT] 
#define	rMSR_FCOMP     	(*(volatile unsigned long  *)(0xFF9811F0U))	// Module Standby Register for Fast Comparator [PBG20 #2/rMSRKCPROT] 
#define	rMSR_EMU       	(*(volatile unsigned long  *)(0xFF981200U))	// Module Standby Register for Enhanced Motor Control Unit. [PBG20 #2/rMSRKCPROT] 
#define	rMSR_HRPWM     	(*(volatile unsigned long  *)(0xFF981220U))	// Module Standby Register for HRPWM [PBG20 #2/rMSRKCPROT] 
#define	rMSR_DSMIF     	(*(volatile unsigned long  *)(0xFF981270U))	// Module Standby Register for DSMIF [PBG20 #2/rMSRKCPROT] 

// write protection
#define	rSTBCKCPROT    	(*(volatile unsigned long  *)(0xFF981700U))	// Standby controller Register Key Code Protection Register [PBG20 #2] 
#define	rMSRKCPROT     	(*(volatile unsigned long  *)(0xFF981710U))	// Module Standby Register Key Code Protection Register [PBG20 #2] 

// module standby (AWO area)
#define	rMSR_ADCK_AWO  	(*(volatile unsigned long  *)(0xFF988E00U))	// Module Standby Register for SAR- ADC(AWO area) [PBG20 #2/rMSRKCPROT] 
#define	rMSR_RTCA      	(*(volatile unsigned long  *)(0xFF988E10U))	// Module Standby Register for RTCA [PBG20 #2/rMSRKCPROT] 
#define	rMSR_TAUJ_AWO  	(*(volatile unsigned long  *)(0xFF988E20U))	// Module Standby Register for TAUJ2/ TAUJ3(AWO area) [PBG20 #2/rMSRKCPROT] 
#define	rMSR_WDTB_AWO  	(*(volatile unsigned long  *)(0xFF988E30U))	// Module Standby Register for WDTB(AWO area) [PBG20 #2/rMSRKCPROT] 
	
	
//////////////////////////////////////////////////////////////////////
// Function Prototype Declaration
//////////////////////////////////////////////////////////////////////
// releases write protection for rMSR_xxx register
#define	STB_ReleaseWriteProtect_MSR()	rMSRKCPROT = 0xA5A5A501

// set write protection for rMSR_xxx register
#define	STB_SetWriteProtect_MSR()    	rMSRKCPROT = 0xA5A5A500

//////////////////////////////////////////////////////////////////////
// Function Name: STB_ReleaseModuleStandby_Units
// Description  : This function releases module standby specified module.
// target device: [U2B]
// Arguments    : 
//	u32 *msr_reg
//		address of rMSR_xxx register.
//	u32 bit_word
// 		specify unit released module standby by value in which 
// 		the bit number is linked to the unit number 
// Return Value : (none)
// Exapmpe      :
//	STB_ReleaseModuleStandby_Units( &rMSR_RSCFD,      0x00000003 );	// all bit clear MSR_RSCFD
//	STB_ReleaseModuleStandby_Units( &rMSR_FLXA,       0x00000003 );	// all bit clear MSR_FLXA
//	STB_ReleaseModuleStandby_Units( &rMSR_GTM,        0x00000001 );	// all bit clear MSR_GTM
//	STB_ReleaseModuleStandby_Units( &rMSR_ETN,        0x00000017 );	// all bit clear MSR_ETN
//	STB_ReleaseModuleStandby_Units( &rMSR_RSENT,      0x3FFFFFFF );	// all bit clear MSR_RSENT
//	STB_ReleaseModuleStandby_Units( &rMSR_MSPI,       0x000003FF );	// all bit clear MSR_MSPI
//	STB_ReleaseModuleStandby_Units( &rMSR_RLIN3,      0x00FFFFFF );	// all bit clear MSR_RLIN3
//	STB_ReleaseModuleStandby_Units( &rMSR_DSADC_CADC, 0x0000007F );	// all bit clear MSR_DSADC_CADC
//	STB_ReleaseModuleStandby_Units( &rMSR_ADCK_ISO,   0x000000FF );	// all bit clear MSR_ADCK_ISO
//	STB_ReleaseModuleStandby_Units( &rMSR_MMCA,       0x00000001 );	// all bit clear MSR_MMCA
//	STB_ReleaseModuleStandby_Units( &rMSR_ENCA,       0x00000003 );	// all bit clear MSR_ENCA
//	STB_ReleaseModuleStandby_Units( &rMSR_PSI5,       0x0000003F );	// all bit clear MSR_PSI5
//	STB_ReleaseModuleStandby_Units( &rMSR_PSI5S,      0x00000003 );	// all bit clear MSR_PSI5S
//	STB_ReleaseModuleStandby_Units( &rMSR_RHSIF,      0x00000003 );	// all bit clear MSR_RHSIF
//	STB_ReleaseModuleStandby_Units( &rMSR_RHSB,       0x0000000F );	// all bit clear MSR_RHSB
//	STB_ReleaseModuleStandby_Units( &rMSR_RIIC,       0x00000003 );	// all bit clear MSR_RIIC
//	STB_ReleaseModuleStandby_Units( &rMSR_SFMA,       0x00000001 );	// all bit clear MSR_SFMA
//	STB_ReleaseModuleStandby_Units( &rMSR_TAPA,       0x0000003F );	// all bit clear MSR_TAPA
//	STB_ReleaseModuleStandby_Units( &rMSR_TAUD,       0x0000000F );	// all bit clear MSR_TAUD
//	STB_ReleaseModuleStandby_Units( &rMSR_TPBA,       0x00000003 );	// all bit clear MSR_TPBA
//	STB_ReleaseModuleStandby_Units( &rMSR_TSG3,       0x00000007 );	// all bit clear MSR_TSG3
//	STB_ReleaseModuleStandby_Units( &rMSR_OSTM,       0x0000003F );	// all bit clear MSR_OSTM
//	STB_ReleaseModuleStandby_Units( &rMSR_ATU,        0x00000001 );	// all bit clear MSR_ATU
//	STB_ReleaseModuleStandby_Units( &rMSR_DFE,        0x00000001 );	// all bit clear MSR_DFE
//	STB_ReleaseModuleStandby_Units( &rMSR_DFP,        0x00000001 );	// all bit clear MSR_DFP
//	STB_ReleaseModuleStandby_Units( &rMSR_RDC,        0x0000000F );	// all bit clear MSR_RDC
//	STB_ReleaseModuleStandby_Units( &rMSR_FCOMP,      0x000007FF );	// all bit clear MSR_FCOMP
//	STB_ReleaseModuleStandby_Units( &rMSR_EMU,        0x00000003 );	// all bit clear MSR_EMU
//	STB_ReleaseModuleStandby_Units( &rMSR_HRPWM,      0x00000001 );	// all bit clear MSR_HRPWM
//	STB_ReleaseModuleStandby_Units( &rMSR_ADCK_AWO,   0x00000001 );	// all bit clear MSR_ADCK_AWO
//	STB_ReleaseModuleStandby_Units( &rMSR_RTCA,       0x00000001 );	// all bit clear MSR_RTCA
//	STB_ReleaseModuleStandby_Units( &rMSR_TAUJ_AWO,   0x00000003 );	// all bit clear MSR_TAUJ_AWO
//	STB_ReleaseModuleStandby_Units( &rMSR_WDTB_AWO,   0x00000001 );	// all bit clear MSR_WDTB_AWO
//////////////////////////////////////////////////////////////////////
void STB_ReleaseModuleStandby_Units( volatile u32 *msr_reg, u32 bit_word );

	
#endif
