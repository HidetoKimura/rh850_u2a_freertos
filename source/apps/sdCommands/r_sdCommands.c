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
* File Name        : r_sdCommands.c
* Component Version: 1.0.0
* Description      : SD Card Commands.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "thirdparty\shell\shell.h"
#include "shared.h"
#include "thirdparty\fatfs\diskio.h"
#include <stdbool.h>
#include "string.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
FATFS FatFs;    /* Work area (filesystem object) for logical drive */
FIL fil;        /* File object */
FRESULT fr;     /* FatFs return code */
UINT bw;        /* Bytes written */
char line[100]; /* Line buffer */
char write_open_file[50];

/***********************************************************************************************************************
* Function Name: sd_cmd
* Description  : Provide SD card functionalities from shell.
* Arguments    : Command arguments
* Return Value : Result
***********************************************************************************************************************/
int sd_cmd(int argc, char **argv) {
  uint8_t sd_return_value=0;
  /* Default to Verbose */
  bool verbose = true;
  /* First argument as command -- mkdir */
  if (argc > 1 && (((strcmp(argv[1], "-mkdir")) ==0) || \
                  ((strcmp(argv[1], "-f_open")) ==0) || \
                  ((strcmp(argv[1], "-f_write")) ==0)|| \
                  ((strcmp(argv[1], "-f_unlink")) ==0)|| \
                  (strcmp(argv[1], "-f_gets")) ==0)) {
    verbose = false;
  } else {
    printf_esh("use: -mkdir <name_of_directory> for creating a directory in sd card (disk IO) device.\n\n");
    printf_esh("use: -f_open </address of the file/><name_of_file>.txt for creating a file in sd card (disk IO) device.\n\n");
    printf_esh("use: -f_write </address of the file/><name_of_file>.txt <file_content> for writing to a file in sd card (disk IO) device without spaces.\n\n");
    printf_esh("use: -f_gets <file path> for writing to the created file in sd card (disk IO) device.\n\n");
  }

    if (verbose) {
      printf_esh("\n\t");
      printf_esh("Wrong command!");
      printf_esh("\n");
      return 0x11; /* break and hand over control to shell. */
    }

    /* First argument as command -- -mkdir */

    if (strcmp(argv[1], "-mkdir")==0)
    {

      /* Give a work area to the default drive */
      fr = f_mount(&FatFs, "", 1);
      if(fr != FR_OK)
      {
          printf_esh("Mounting failed: Error Code %d\n", fr);
      }
      else if(fr == FR_OK)
      {
          printf_esh("Mounting passed.\n");
      }
      printf_esh("\n");

      fr = f_mkdir(argv[2]);
      if(fr != FR_OK)
      {
          printf_esh("Directory creation failed: Error Code %d\n", fr);
      }
      else if(fr == FR_OK)
      {
          printf_esh("Directory creation passed.\n");
      }
      printf_esh("\n");

      /* Close the file */
      f_close(&fil);
      f_mount(NULL, "", 0);

      sd_return_value = 0;

    } /* End first command. */


  /* Second argument as command -- -f_open */
  if (strcmp(argv[1], "-f_open")==0)
  {
    /* Give a work area to the default drive */
    fr = f_mount(&FatFs, "", 1);
    if(fr != FR_OK)
    {
        printf_esh("Mounting failed: Error Code %d\n", fr);
    }
    else if(fr == FR_OK)
    {
        printf_esh("Mounting passed.\n", fr);
    }
    printf_esh("\n");

    fr = f_open(&fil, argv[2], FA_CREATE_NEW | FA_WRITE | FA_READ);
    if(fr != FR_OK)
    {
        printf_esh("File creation failed: Error Code %d\n", fr);
    }
    else if(fr == FR_OK)
    {
        printf_esh("File creation passed.\n");
    }
    printf_esh("\n");

    /* Close the file */
    f_close(&fil);
    f_mount(NULL, "", 0);
    sd_return_value = 0;

  } /* End second command. */

  /* Third argument as command -- -f_write */
  if (strcmp(argv[1], "-f_write")==0)
  {
    /* Give a work area to the default drive */
    fr = f_mount(&FatFs, "", 1);
    if(fr != FR_OK)
    {
        printf_esh("Mounting failed: Error Code %d\n", fr);
    }
    else if(fr == FR_OK)
    {
        printf_esh("Mounting passed.\n");
    }
    printf_esh("\n");

    fr = f_open(&fil, argv[2], FA_WRITE | FA_READ);
    if(fr != FR_OK)
    {
        printf_esh("File open failed: Error Code %d\n", fr);
    }
    else if(fr == FR_OK)
    {
        printf_esh("File open passed.\n");
    }
    printf_esh("\n");

    fr = f_write(&fil, argv[3], strlen(argv[3]), &bw);
    if(fr != FR_OK)
    {
        printf_esh("Writing failed: Error Code %d\n", fr);
    }
    else if(fr == FR_OK)
    {
        printf_esh("Writing successful.\n");
    }

    printf_esh("\n");

    /* Close the file */
    f_close(&fil);
    f_mount(NULL, "", 0);
    printf_esh("\n");

    sd_return_value = 0;

  } /* End third command. */

  /* Fourth argument as command -- --f_gets */
  if (strcmp(argv[1], "-f_gets")==0)
  {
    /* Give a work area to the default drive */
    fr = f_mount(&FatFs, "", 1);
    if(fr != FR_OK)
    {
        printf_esh("Mounting failed: Error Code %d\n", fr);
    }
    else if(fr == FR_OK)
    {
        printf_esh("Mounting passed.\n");
    }
    printf_esh("\n");

    fr = f_open(&fil, argv[2], FA_READ);
    if(fr != FR_OK)
    {
        printf_esh("READ ONLY mode file open failed: Error Code %d\n", fr);
    }
    else if(fr == FR_OK)
    {
        printf_esh("READ ONLY mode file open passed.\n");
    }
    printf_esh("\n");

    /* Read every line and display it */
    while (f_gets(line, sizeof line, &fil)) {
        printf_esh(line);
    }
    printf_esh("\n");
    if(fr != FR_OK)
    {
        sd_return_value = 1;
        printf_esh("\nReading failed: Error Code %d\n", fr);
    }

    else if(fr == FR_OK)
    {
        sd_return_value = 0;
        printf_esh("\nReading passed.\n");
    }

    /* Close the file */
    f_close(&fil);
    f_mount(NULL, "", 0);
    printf_esh("\n");

  sd_return_value = 0;

  } /* End fourth command. */

  /* Fifth argument as command -- -f_unlink */
  if (strcmp(argv[1], "-f_unlink")==0)
  {
    /* Give a work area to the default drive */
    fr = f_mount(&FatFs, "", 1);
    if(fr != FR_OK)
    {
        printf_esh("Mounting failed: Error Code %d\n", fr);
    }
    else if(fr == FR_OK)
    {
        printf_esh("Mounting passed.\n");
    }

    printf_esh("\n");

    /* Close the file */
    f_close(&fil);
    if(fr != FR_OK)
    {
        printf_esh("File closing failed: Error Code %d\n", fr);
    }
    else if(fr == FR_OK)
    {
        printf_esh("File closed successfully.\n");
    }
   
    printf_esh("\n");

    /* Delete the file */
    fr = f_unlink(argv[2]);
    if(fr != FR_OK)
    {
        printf_esh("Deleting file failed: Error Code %d\n", fr);
    }
    else if(fr == FR_OK)
    {
        printf_esh("Deleting file passed.\n");
    }
    printf_esh("\n");    

    f_mount(NULL, "", 0);
    printf_esh("\n");

  sd_return_value = 0;

  } /* End fifth command. */

  return sd_return_value; /* Return function value. */
}

ADD_CMD(sd_diskio_cmd, "SD Card (DISK-I/O) Commands", sd_cmd);
