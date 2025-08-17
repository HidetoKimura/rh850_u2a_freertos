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
* File Name        : display.h
* Component Version: 1.0.0
* Description      : 
***********************************************************************************************************************/
#ifndef R_DISPLAY_H
#define R_DISPLAY_H


/*===========================================================================*/
/* Defines */
/*===========================================================================*/




#define R_NO_FILL                                     0x00
#define R_FILL                                        0xff

#define R_BLACK                                       0x00
#define R_WHITE                                       0xff

#define DISPLAY_WIDTH                                 128
#define DISPLAY_HEIGHT                                64

#define DISPLAY_SETCONTRAST                           0x81
#define DISPLAY_DISPLAYALLON_RESUME                   0xA4
#define DISPLAY_DISPLAYALLON                          0xAF
#define DISPLAY_NORMALDISPLAY                         0xA6
#define DISPLAY_INVERTDISPLAY                         0xA7
#define DISPLAY_DISPLAYOFF                            0xAE


#define DISPLAY_SETDISPLAYOFFSET                      0xD3
#define DISPLAY_SETCOMPINS                            0xDA

#define DISPLAY_SETVCOMDETECT                         0xDB

#define DISPLAY_SETDISPLAYCLOCKDIV                    0xD5
#define DISPLAY_SETPRECHARGE                          0xD9

#define DISPLAY_SETMULTIPLEX                          0xA8

#define DISPLAY_SETLOWCOLUMN                          0x00
#define DISPLAY_SETHIGHCOLUMN                         0x10

#define DISPLAY_SETSTARTLINE                          0x40

#define DISPLAY_MEMORYMODE                            0x20
#define DISPLAY_COLUMNADDR                            0x21
#define DISPLAY_PAGEADDR                              0x22

#define DISPLAY_COMSCANINC                            0xC0
#define DISPLAY_COMSCANDEC                            0xC8

#define DISPLAY_SEGREMAP                              0xA0

#define DISPLAY_CHARGEPUMP                            0x8D

#define DISPLAY_EXTERNALVCC                           0x1
#define DISPLAY_SWITCHCAPVCC                          0x2


// Scrolling #defines
#define DISPLAY_ACTIVATE_SCROLL                       0x2F
#define DISPLAY_DEACTIVATE_SCROLL                     0x2E
#define DISPLAY_SET_VERTICAL_SCROLL_AREA              0xA3
#define DISPLAY_RIGHT_HORIZONTAL_SCROLL               0x26
#define DISPLAY_LEFT_HORIZONTAL_SCROLL                0x27
#define DISPLAY_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL  0x29
#define DISPLAY_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL   0x2A



typedef struct 
{
  uint32_t  num_rows;
  uint32_t  width;
  const uint8_t   *data;
}r_display_image;


typedef enum {
  R_DISPLAY_OK = 0u,
  R_DISPLAY_ERROR,
  R_DISPLAY_TIMEOUT,
  R_DISPLAY_BUSY
} r_DisplayError_t;  

typedef enum {
  R_DISPLAY_OK_STATE = 0x00,
  R_DISPLAY_TIMEOUT_STATE = 0x01,
  R_DISPLAY_ERROR_STATE = 0x02
} r_displayState_t;
typedef struct r_display
{
  r_displayState_t state;
}r_displayStatus_t;

extern r_displayStatus_t g_DisplayStatus;


/*===========================================================================*/
/* Function defines */
/*===========================================================================*/
void R_DISPLAY_start_display( void );
void R_DISPLAY_fc_upd_display( uint32_t fc_data);
void R_DISPLAY_sc_upd_display( uint16_t errorCode );
void R_Display_delay(uint32_t countms);
r_DisplayError_t R_DISPLAY_waitForIdle(uint32_t timeoutms);
void R_DISPLAY_Deinit(void);
void R_DISPLAY_StartScreen(void);
r_DisplayError_t R_DISPLAY_Init(void);
void R_DISPLAY_ResetRelease(void);
void R_DISPLAY_DrawText(uint8_t row, uint8_t  pos, char* c,  uint8_t color, uint8_t fill);
void R_DISPLAY_clearBuffer(void);
void R_DISPLAY_DrawImg(uint8_t row, uint8_t pos, r_display_image *image);
void R_DISPLAY_DrawTextBig(uint8_t row, uint8_t  pos, char* c,  uint8_t color, uint8_t fill);
r_DisplayError_t R_DISPLAY_writeBuffer_ifIDLE(void);
r_DisplayError_t R_DISPLAY_writeBuffer(void);
void R_DISPLAY_rowFill(uint16_t row, uint16_t pos, uint16_t length ,uint8_t color);
void R_DISPLAY_testpattern();
void R_DISPLAY_clear(void);
void R_DISPLAY_clearBuffer(void);
void R_DISPLAY_StartScreenStop(void);
#endif /* R_DISPLAY_H */
