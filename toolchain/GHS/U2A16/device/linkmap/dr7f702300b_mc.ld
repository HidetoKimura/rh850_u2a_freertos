/*===========================================================================*/
/* Module       = dr7f702300b_mc.ld                                          */
/* Version      = E1.00a                                                     */
/*                extracted from device file dr7f702300b.dvf                 */
/*                by DeFiXRH850 1.1.1.9                                      */
/*===========================================================================*/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2021 by Renesas Electronics Europe GmbH,                    */
/*               a company of the Renesas Electronics Corporation            */
/*===========================================================================*/
/* Purpose:     Template of linker directive file                            */
/*                                                                           */
/*===========================================================================*/
/*                                                                           */
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
/* Environment:                                                              */
/*              Device:         R7F702300B                                   */
/*              IDE:            GHS Multi for V800  V6.xx or later           */
/*===========================================================================*/

CONSTANTS
{
  /* User area start */
     USR_STACK_RESERVED_PE0    = 0x2200
     USR_STACK_RESERVED_PE1    = 0x2200
     USR_STACK_RESERVED_PE2    = 0x2200
     USR_STACK_RESERVED_PE3    = 0x2200
     USR_STACK_RESERVED_SHARED = 256
     USR_STACK_RESERVED_GLOBAL = 2k
     USR_HEAP_RESERVED         = 1k    	       /* always in shared memory */
     USR_GRAM_RESERVED_SHARED  = 128k
     USR_ROM_SHARED_SIZE       = 100k
     USR_ROM_SECT_SHARED       = 10k
     USR_ROM_RESERVED_PE0      = 1M
     USR_ROM_SECT_PE0          = 4k
     USR_ROM_RESERVED_PE1      = 1M
     USR_ROM_SECT_PE1          = 4k
     USR_ROM_RESERVED_PE2      = 1M
     USR_ROM_SECT_PE2          = 4k
     USR_ROM_RESERVED_PE3      = 1M
     USR_ROM_SECT_PE3          = 4k
     USR_RAM_SECT_SHARED       = USR_GRAM_RESERVED_SHARED - USR_HEAP_RESERVED - USR_STACK_RESERVED_SHARED
     USR_CLUSTER1_RSVD         = 1M 
     USR_CLUSTER2_RSVD         = 1M
  /* User area end */

  /* Device file area start*/
     DVF_iROM_BANK_A_START      = 0x00000000
     DVF_iROM_BANK_A_SIZE       = 4096k
     DVF_iROM_BANK_B_START      = 0x00400000
     DVF_iROM_BANK_B_SIZE       = 4096k
     DVF_iROM_BANK_C_START      = 0x00800000
     DVF_iROM_BANK_C_SIZE       = 4096k
     DVF_iROM_BANK_D_START      = 0x00C00000
     DVF_iROM_BANK_D_SIZE       = 4096k
     DVF_iROM_MIRROR_START      = 0x04000000
     DVF_iROM_MIRROR_SIZE       = 4096k
     DVF_iROM_MIRROR_START      = 0x04400000
     DVF_iROM_MIRROR_SIZE       = 4096k
     DVF_iROM_MIRROR_START      = 0x04800000
     DVF_iROM_MIRROR_SIZE       = 4096k
     DVF_iROM_MIRROR_START      = 0x04C00000
     DVF_iROM_MIRROR_SIZE       = 4096k
     DVF_iROM_SHARED0_START    = 0x08000000
     DVF_iROM_SHARED0_SIZE     = 64k
     DVF_iROM_SHARED1_START    = 0x08030000
     DVF_iROM_SHARED1_SIZE     = 32k
     DVF_iROM_SHARED2_START    = 0x08050000
     DVF_iROM_SHARED2_SIZE     = 64k
     DVF_iROM_SHARED3_START    = 0x08400000
     DVF_iROM_SHARED3_SIZE     = 64k
     DVF_iROM_SHARED4_START    = 0x08430000
     DVF_iROM_SHARED4_SIZE     = 32k
     DVF_iROM_SHARED5_START    = 0x08450000
     DVF_iROM_SHARED5_SIZE     = 64k
     DVF_iROM_SHARED6_START    = 0x08850000
     DVF_iROM_SHARED6_SIZE     = 64k
     DVF_iROM_SHARED7_START    = 0x08C50000
     DVF_iROM_SHARED7_SIZE     = 64k
     DVF_iROM_SHARED8_START    = 0x0BFF0000
     DVF_iROM_SHARED8_SIZE     = 64k
     DVF_iRAM_SELF_START       = 0xFDE00000    /* iRAM address, as seen from core */
     DVF_iRAM_SELF_SIZE        = 64k           /* iRAM size, as seen from core    */
     DVF_cRAM0_START          = 0xFE000000
     DVF_cRAM0_SIZE           = 512k
     DVF_cRAM1_START          = 0xFE100000
     DVF_cRAM1_SIZE           = 512k
     DVF_cRAM2_START          = 0xFE400000
     DVF_cRAM2_SIZE           = 1024k
     DVF_cRAM3_START          = 0xFE500000
     DVF_cRAM3_SIZE           = 1024k
     DVF_cRAM4_START          = 0xFE800000
     DVF_cRAM4_SIZE           = 128k
     DVF_cRAM5_START          = 0xFE820000
     DVF_cRAM5_SIZE           = 128k
     DVF_iRAM_3_START          = 0xFD600000
     DVF_iRAM_3_SIZE           = 64k
     DVF_iRAM_2_START          = 0xFD800000
     DVF_iRAM_2_SIZE           = 64k
     DVF_iRAM_1_START          = 0xFDA00000
     DVF_iRAM_1_SIZE           = 64k
     DVF_iRAM_0_START          = 0xFDC00000
     DVF_iRAM_0_SIZE           = 64k
  /* Device file area end*/

  /* Global parameter area start */
  /* Total Code Flash Count: 21 */
     ROM_ALL_START             = DVF_iROM_BANK_A_START
     ROM_ALL_SIZE              = DVF_iROM_BANK_A_SIZE
     ROM_CLUSTER1_START        = DVF_iROM_BANK_A_START
     ROM_SHARED_START          = DVF_iROM_BANK_A_START
     ROM_SHARED_SIZE           = USR_CLUSTER1_RSVD
     ROM_CLUSTER1_START        = DVF_iROM_BANK_A_START
     ROM_PE0_START             = DVF_iROM_BANK_A_START  + USR_CLUSTER1_RSVD
     ROM_PE0_SIZE              = DVF_iROM_BANK_A_SIZE - USR_CLUSTER1_RSVD
     ROM_PE1_START             = DVF_iROM_BANK_B_START
     ROM_PE1_SIZE              = DVF_iROM_BANK_B_SIZE
     ROM_CLUSTER2_START        = DVF_iROM_BANK_C_START
     ROM_PE2_START             = DVF_iROM_BANK_C_START  + USR_CLUSTER2_RSVD
     ROM_PE2_SIZE              = DVF_iROM_BANK_C_SIZE - USR_CLUSTER2_RSVD
     ROM_PE3_START             = DVF_iROM_BANK_D_START
     ROM_PE3_SIZE              = DVF_iROM_BANK_D_SIZE
     RAM_PE0_START             = DVF_iRAM_0_START
     RAM_PE0_SIZE              = DVF_iRAM_0_SIZE
     RAM_PE1_START             = DVF_iRAM_1_START
     RAM_PE1_SIZE              = DVF_iRAM_1_SIZE
     RAM_PE2_START             = DVF_iRAM_2_START
     RAM_PE2_SIZE              = DVF_iRAM_2_SIZE
     RAM_PE3_START             = DVF_iRAM_3_START
     RAM_PE3_SIZE              = DVF_iRAM_3_SIZE
     GRAM_0_START              = DVF_cRAM0_START
     GRAM_0_SIZE               = DVF_cRAM0_SIZE
     GRAM_1_START              = DVF_cRAM1_START
     GRAM_1_SIZE               = DVF_cRAM1_SIZE
     GRAM_2_START              = DVF_cRAM2_START
     GRAM_2_SIZE               = DVF_cRAM2_SIZE
     GRAM_3_START              = DVF_cRAM3_START
     GRAM_3_SIZE               = DVF_cRAM3_SIZE
     GRAM_4_START              = DVF_cRAM4_START
     GRAM_4_SIZE               = DVF_cRAM4_SIZE
     GRAM_5_START              = DVF_cRAM5_START
     GRAM_5_SIZE               = DVF_cRAM5_SIZE
     zero_start                = 0xFFFF8000

  #if defined(__ghs_GC_shared__)
    ROM_START      = ROM_CLUSTER1_START
    ROM_SIZE       = ROM_SHARED_SIZE;
    ROM_START_c2   = ROM_CLUSTER2_START
    ROM_SIZE_c2    = ROM_SHARED_SIZE;
    RAM_START      = GRAM_0_START;
    RAM_SIZE       = GRAM_0_SIZE;
    STACK_RESERVED = USR_STACK_RESERVED_SHARED; /* Dummy value required for shared lib */

  #elif defined(__ghs_GC_core_1__)
    ROM_START      = ROM_PE0_START;             /* start of PE1 area incl EBASE and RESET */
    ROM_SIZE       = ROM_PE0_SIZE;
    RAM_START      = RAM_PE0_START;
    RAM_SIZE       = RAM_PE0_SIZE;
    STACK_RESERVED = USR_STACK_RESERVED_PE0;

  #elif defined(__ghs_GC_core_2__)
    ROM_START      = ROM_PE1_START;             /* start of PE2 area incl EBASE and RESET */
    ROM_SIZE       = ROM_PE1_SIZE;
    RAM_START      = RAM_PE1_START;
    RAM_SIZE       = RAM_PE1_SIZE;
    STACK_RESERVED = USR_STACK_RESERVED_PE1;

  #elif defined(__ghs_GC_core_3__)
    ROM_START      = ROM_PE2_START;             /* start of PE3 area incl EBASE and RESET */
    ROM_SIZE       = ROM_PE2_SIZE;
    RAM_START      = RAM_PE2_START;
    RAM_SIZE       = RAM_PE2_SIZE;
    STACK_RESERVED = USR_STACK_RESERVED_PE2;

  #elif defined(__ghs_GC_core_4__)
    ROM_START      = ROM_PE3_START;             /* start of PE4 area incl EBASE and RESET */
    ROM_SIZE       = ROM_PE3_SIZE;
    RAM_START      = RAM_PE3_START;
    RAM_SIZE       = RAM_PE3_SIZE;
    STACK_RESERVED = USR_STACK_RESERVED_PE3;

  #else
    ROM_START      = ROM_ALL_START;
    ROM_SIZE       = ROM_ALL_SIZE;
    RAM_START      = DVF_iRAM_0_START;
    RAM_SIZE       = DVF_iRAM_0_SIZE;
    STACK_RESERVED = USR_STACK_RESERVED_GLOBAL;

  #endif
}
  /* Global Parameter area end */

MEMORY
{
  iROM           : ORIGIN = ROM_START,               LENGTH = ROM_SIZE
  #if defined(__ghs_GC_shared__)
    iROMc2       : ORIGIN = ROM_START_c2,            LENGTH = ROM_SIZE_c2
    iROMBOOT     : ORIGIN = DVF_iROM_SHARED0_START,  LENGTH = DVF_iROM_SHARED0_SIZE
  #endif
  #if !defined(__ghs_GC_shared__)
    iRAM         : ORIGIN = RAM_START,               LENGTH = RAM_SIZE
  #endif
  gRAM0          : ORIGIN = GRAM_0_START,            LENGTH = GRAM_0_SIZE
  gRAM1          : ORIGIN = GRAM_1_START,            LENGTH = GRAM_1_SIZE
  gRAM2          : ORIGIN = GRAM_2_START,            LENGTH = GRAM_2_SIZE
  gRAM3          : ORIGIN = GRAM_3_START,            LENGTH = GRAM_3_SIZE
  gRAM4          : ORIGIN = GRAM_4_START,            LENGTH = GRAM_4_SIZE
  gRAM5          : ORIGIN = GRAM_5_START,            LENGTH = GRAM_5_SIZE
  }

SECTIONS
 {

/* Start of internal ROM area (iROM) */
 #if defined(__ghs_GC_shared__)
  .cintvect min_size(0x0400) align(512)                    :
            { * (.cintvect) }                               >iROM     /* PE1 start of interrupt vector (global) */
  .coldboot                                                :>.
  .intvect max_size(0x0270) align(512)                     :>iROM     /* start of interrupt vector */
 #else
  #if defined(__ghs_GC_core_1__)
    .intvect_PE0 max_size(0x0EA4) align(512)               :>iROM      /* start of interrupt vector core PE0 */
    EIINTTBL_PE0 align(512)                               :>.
  #endif 
  #if defined(__ghs_GC_core_2__)
    .intvect_PE1 max_size(0x0EA4) align(512)               :>iROM      /* start of interrupt vector core PE0 */
    EIINTTBL_PE1 align(512)                               :>.
  #endif
 #endif

/* Next PE/Cluster entries */
 #if defined(__ghs_GC_shared__)
 .cintvect2 min_size(0x0400) align(512)                  :
           { * (.cintvect2) }                             >iROMc2     /* PE2 start of interrupt vector (global) */
 .coldboot2                                              :>.
 .intvect2 max_size(0x0270) align(512)                   :>iROMc2     /* start of interrupt vector */
 #else
  #if defined(__ghs_GC_core_3__)
   .intvect_PE2 max_size(0x0EA4) align(512)              :>iROM        /* start of interrupt vector core PE2 */
   EIINTTBL_PE2 align(512)                               :>.
  #endif
  #if defined(__ghs_GC_core_4__)
   .intvect_PE3 max_size(0x0EA4) align(512)              :>iROM        /* start of interrupt vector core PE3 */
   EIINTTBL_PE3 align(512)                               :>.
  #endif
 #endif
  .rozdata     align(4)                                    :>iROM      /* constant datas in ZDA area */
  .robase      align(4)                                    :>.         /* initialize textpointer TP for SDA addressing */
  .rosdata     align(4)                                    :>.         /* constant datas in SDA area */
  .rodata      align(4)                                    :>.         /* constant datas in normal area */
  .cmd_list  align(4)                                    :>.         /* used by esh shell */
  .auto_list align(4)                                    :>.         /* used by esh shell */
  .cmd_end  align(4)                                     :>.         /* used by esh shell */
  .text        align(4)                                    :>.         /* program code area */
  #if defined(__ghs_GC_shared__)
    .mytext    min_size( USR_ROM_SECT_SHARED) align(4)     :>.         /* user program code area shared */
  #endif
  #if defined(__ghs_GC_core_1__)
    .pe0.text    min_size( USR_ROM_SECT_PE0) align(4)     :>.         /* user program code area core 1 */
  #endif
  #if defined(__ghs_GC_core_2__)
    .pe1.text    min_size( USR_ROM_SECT_PE1) align(4)     :>.         /* user program code area core 2 */
  #endif
  .fixaddr     align(4)                                    :>.         /* ghs internal (compiler) */
  .fixtype     align(4)                                    :>.         /* ghs internal (compiler) */
  .secinfo     align(4)                                    :>.         /* ghs internal (runtime library) */
  .syscall     align(4)                                    :>.         /* ghs internal (linker) */
  .romdata     ROM(.data)                                  :>.         /* constant data to initialize variables (copied to RAM at startup)*/
  #if defined(__ghs_GC_shared__)
  .romsldata   ROM(.sldata)                                :>.         /* constant data to initialize variables in LSDA area (copied to GRAM at startup)*/
  .userboot    align(4)                                    :>iROMBOOT
  #else
  .romsdata  ROM(.sdata)                                   :>.         /* constant data to initialize variables in SDA area (copied to RAM at startup)*/
  #endif

/* Start of internal RAM area (iRAM) */
  #if !defined(__ghs_GC_shared__)
    .stack align(4) pad(STACK_RESERVED)                    :>iRAM      /* definition of stack size */
    .sda_start align(4)                                    :>.         /* initialize globalpointer GP for SDA addressing */
    .sdata     align(4)                                    :>.         /* initialized data in SDA area*/
    .sbss      align(4)                                    :>.         /* zero initialized data in SDA area*/
    .zbss      align(4)                                    :>.         /* zero initialized data in ZDA area*/
    .sda_end   align(4)                                    :>.         /* end of SDA addressing */
  #endif

  #if defined(__ghs_GC_shared__)
  /* Start of internal global RAM area (gRAM) */
   .slsync     min_size(4)                                 :>gRAM0     /* user defined segment for semaphore data located in global RAM */
   .sldata     align(4)                                    :>.         /* user defined segment for initialized data located in global RAM */
   .slbss      align(4)                                    :>.         /* user defined segment for initialized data located in global RAM */

   .sdabase    align(4)                                    :>.         /* initialize globalpointer GP for SDA addressing */
   .sdata      align(4)                                    :>.         /* initialized data in SDA area*/
   .sbss       align(4)                                    :>.         /* zero initialized data in SDA area*/
   .zbss       align(4)                                    :>.         /* zero initialized data in ZDA area*/
  #endif

  .data        align(8)                                    :>.         /* initialized data */
  .bss         align(4)                                    :>.         /* zero initialized data*/

  .tdata       align(4) SIZE(0x0100)                       :>.         /* initialized and zero-initialized data in TDA area */
  .heap        align(4) pad(USR_HEAP_RESERVED)
               NOCLEAR                                     :>.         /* definition of heap size */

  .rbss        align(4)                                    :>gRAM4     /* Retention RAM bss section */

/*  Symbols for compiler references */
  ___ghs_romstart    = MEMADDR(iROM);
  ___ghs_romend      = MEMENDADDR(iROM);
  #if !defined(__ghs_GC_shared__)
    ___ghs_ramstart  = MEMADDR(iRAM);
    ___ghs_ramend    = MEMENDADDR(iRAM);
  #endif
  ___ghs_gramstart0  = MEMADDR(gRAM0);
  ___ghs_gramend0    = MEMENDADDR(gRAM0);

  ___ghs_gramstart1  = MEMADDR(gRAM1);
  ___ghs_gramend1    = MEMENDADDR(gRAM1);

  ___ghs_gramstart2  = MEMADDR(gRAM2);
  ___ghs_gramend2    = MEMENDADDR(gRAM2);

  ___ghs_gramstart3  = MEMADDR(gRAM3);
  ___ghs_gramend3    = MEMENDADDR(gRAM3);

  ___ghs_gramstart4  = MEMADDR(gRAM4);
  ___ghs_gramend4    = MEMENDADDR(gRAM4);

  ___ghs_gramstart5  = MEMADDR(gRAM5);
  ___ghs_gramend5    = MEMENDADDR(gRAM5);

  /* These special symbols mark the bounds of RAM and ROM images of boot code. */
  /* They are used by the GHS startup code (_start and __ghs_ind_crt0).        */
  // ___ghs_rambootcodestart  = 0;
  // ___ghs_rambootcodeend    = 0;
  // ___ghs_rombootcodestart  = ADDR(.text);
  // ___ghs_rombootcodeend    = ENDADDR(.fixtype);
  ___cmd_list_start = ADDR(.cmd_list);
  ___auto_list_start = ADDR(.auto_list);
  _RESETVECT         = 0x08000000;
}

/*===========================================================================*/
/*      End of File                                                          */
/*===========================================================================*/
