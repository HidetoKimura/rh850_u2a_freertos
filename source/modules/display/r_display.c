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
* File Name        : r_display.h
* Component Version: 1.0.0
* Description      : 
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "inc\common.h"
#include "r_display.h"
#include "r_image.h"
#include "font5x7.h"
#include "font12x16.h"
#include <stdio.h>
#include <stdio.h>
#include "drivers\gpio\r_gpio_helper.h"
#include "SmartConfigurator\RIIC0\RIIC0.h"
#include "shared.h"

/*===========================================================================*/
/* Variables */
/*===========================================================================*/
int32_t  displayed_ESDM_ID = 0x3;

uint8_t display_timeout;
uint8_t display_flag_interrupt_error;

/*===========================================================================*/
/* Function prototypes */
/*===========================================================================*/
r_DisplayError_t writeCommand(uint8_t Command) ;
void writeBufferInit(void);
void delay(uint16_t count);
void startscrollright(uint8_t start, uint8_t stop);
void drawChar(uint8_t row, uint8_t  pos , uint8_t c, uint8_t  color);
void drawCharBig(uint8_t row, uint8_t  pos , uint8_t c, uint8_t  color);
void stopscroll(void);
void startscrolldiagright(uint8_t start, uint8_t stop);
void R_DISPLAY_rowFill(uint16_t row, uint16_t pos, uint16_t length ,uint8_t color);

static uint8_t displayBuffer[DISPLAY_HEIGHT/8][DISPLAY_WIDTH];
static uint8_t send_buffer[((DISPLAY_WIDTH*DISPLAY_HEIGHT)/8)+1];
static uint8_t cmd_send_buffer[2];

/* Display status */
r_displayStatus_t g_DisplayStatus;
/*===========================================================================*/
/* General Display Functions */
/*===========================================================================*/
    
/*****************************************************************************
** Function:    R_DISPLAY_Deinit
** Description: Configures used pins back to default.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_DISPLAY_Deinit(void)
{

}

/*****************************************************************************
** Function:    R_DISPLAY_ResetRelease
** Description: Set display reset pin to high->operation mode.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_DISPLAY_ResetRelease(void)
{
    PORT0.PKCPROT = KCE_EN;                  /* Enable writes to PWE register */
    PORT0.PWE |= 1<<3;                /* PWEP2:Enable Write Access for Port 2 */

    PORT0.P2.UINT16 &= ~(1u<<15);/* Port 2 Pin 15: Port pin drives lowlevel. Pn_15=0 */
    PORT0.PM2.UINT16 &= ~(1u<<15);   /* Port 2 Pin 15: Set as Output Mode. PMn_15= 0 */
    PORT0.PMC2.UINT16 &= ~(1u<<15);    /* Port 2 Pin 15: Set as Port Mode. PMCn_2= 0 */
    
    PORT0.PWE &= ~(1<<3);            /* PWEP2:Disable Write Access for Port 2 */
    SYSCTRL.MSRKCPROT.UINT32 = KCE_DIS;           /* Disables writes to PWE register */
}

/*****************************************************************************
** Function:    R_DISPLAY_StartScreen
** Description: Displays the initial startup screen with logo and scrolling text
** Parameter:   None
** Return:      None
******************************************************************************/
void R_DISPLAY_StartScreen(void)
{
  R_DISPLAY_DrawImg(0,0,&rh850Logo);                                  /* Draw the RH850 logo at top of screen */
  R_DISPLAY_DrawText(4,0,"    U2A Starterkit  ",R_WHITE,R_FILL);     /* Display starterkit text in white */
  R_DISPLAY_DrawText(6,0,"Press Enc to start ",R_WHITE,R_FILL);      /* Display prompt text in white */
  R_DISPLAY_writeBuffer();                                            /* Update the display with new content */
  startscrollright(6,7);                                             /* Start scrolling the prompt text */
}

/*****************************************************************************
** Function:    R_DISPLAY_StartScreenStop
** Description: Stops the scrolling effect and reinitializes the display buffer
** Parameter:   None
** Return:      None
******************************************************************************/
void R_DISPLAY_StartScreenStop(void)
{
  stopscroll();         /* Stop any active scrolling effects */
  writeBufferInit();    /* Reinitialize the display buffer */
}

/***********************************************************************************************************************
* Function Name: R_DISPLAY_clearBuffer
* Description: Clears the entire display buffer by setting all bytes to 0 (black)
* Arguments: None
* Return Value: None
***********************************************************************************************************************/
void R_DISPLAY_clearBuffer(void)
{
  uint32_t i; 
  for (i=0;i<((DISPLAY_WIDTH*DISPLAY_HEIGHT)/8);i++)
  {
      displayBuffer[i/DISPLAY_WIDTH][i%DISPLAY_WIDTH]=0;
  }
}

/***********************************************************************************************************************
* Function Name: R_DISPLAY_clear 
* Description: Clears both the display buffer and updates the physical display
* Arguments: None
* Return Value: None
* Note: This combines R_DISPLAY_clearBuffer() with R_DISPLAY_writeBuffer() to clear screen
***********************************************************************************************************************/
void R_DISPLAY_clear(void)
{
  uint32_t i; 
  for (i=0;i<((DISPLAY_WIDTH*DISPLAY_HEIGHT)/8);i++)
  {
      displayBuffer[i/DISPLAY_WIDTH][i%DISPLAY_WIDTH]=0;
  }
  R_DISPLAY_writeBuffer();	
}

/***********************************************************************************************************************
* Function Name: startscrolldiagright
* Description: Initiates diagonal right scrolling animation on the display
* Arguments:
*   start - Starting row/page for scroll effect (0-7)
*   stop - Ending row/page for scroll effect (0-7)
* Return Value: None
***********************************************************************************************************************/
void startscrolldiagright(uint8_t start, uint8_t stop)
{
  writeCommand(DISPLAY_SET_VERTICAL_SCROLL_AREA);
  writeCommand(0X00);
  writeCommand(DISPLAY_HEIGHT);
  writeCommand(DISPLAY_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);
  writeCommand(0X00);
  writeCommand(start);
  writeCommand(0X00);
  writeCommand(stop);
  writeCommand(0X01);
  writeCommand(DISPLAY_ACTIVATE_SCROLL);
}

/***********************************************************************************************************************
* Function Name: startscrollright
* Description: Initiates horizontal right scrolling animation on the display
* Arguments:
*   start - Starting row/page for scroll effect (0-7)
*   stop - Ending row/page for scroll effect (0-7)
* Return Value: None
***********************************************************************************************************************/
void startscrollright(uint8_t start, uint8_t stop)
{
  writeCommand(DISPLAY_RIGHT_HORIZONTAL_SCROLL);
  writeCommand(0X00);
  writeCommand(start);
  writeCommand(0X00);
  writeCommand(stop);
  writeCommand(0X00);
  writeCommand(0XFF);
  writeCommand(DISPLAY_ACTIVATE_SCROLL);
}

/***********************************************************************************************************************
* Function Name: stopscroll
* Description: Stops any active scrolling animation on the display
* Arguments: None
* Return Value: None
***********************************************************************************************************************/
void stopscroll(void)
{
  writeCommand(DISPLAY_DEACTIVATE_SCROLL);
}

/*****************************************************************************
** Function:    R_DISPLAY_Init
** Description: Configures pins, RIIC and the display if connected.
** Parameter:   None
** Return:      R_OK - Configuration complete
**              R_ERROR - No display connected.
******************************************************************************/
r_DisplayError_t R_DISPLAY_Init(void)
{
    
    
    g_DisplayStatus.state = R_DISPLAY_OK_STATE;

    R_Display_delay(100);       
    
    setGpioHigh(2,14);
    setGpioHigh(2,15);

    R_RIIC0_Create();
    R_RIIC0_Start();
    
    R_Display_delay(200);
        
    writeCommand(DISPLAY_DISPLAYOFF);   
    
    writeCommand(DISPLAY_SETDISPLAYCLOCKDIV);            
    writeCommand(0x80);                                  
    
    writeCommand(DISPLAY_SETMULTIPLEX);                  
    writeCommand(DISPLAY_HEIGHT - 1);
    
    writeCommand(DISPLAY_SETDISPLAYOFFSET);              
    writeCommand(0x0);                                   
    writeCommand(DISPLAY_SETSTARTLINE | 0x0);            
    writeCommand(DISPLAY_CHARGEPUMP);                    
    writeCommand(0x14);

    writeCommand(DISPLAY_MEMORYMODE);                    
    writeCommand(0x00);          

    writeCommand(DISPLAY_SEGREMAP | 0x1);
    writeCommand(DISPLAY_COMSCANDEC);
    
  
    writeCommand(DISPLAY_SETCOMPINS);                    
    writeCommand(0x12);

    writeCommand(DISPLAY_SETCONTRAST);                   
    writeCommand(0xCF);
    
    writeCommand(DISPLAY_SETPRECHARGE);                  // 0xd9
    writeCommand(0xF1);

    writeCommand(DISPLAY_SETVCOMDETECT);                 // 0xDB
    writeCommand(0x40);

    writeCommand(DISPLAY_DISPLAYALLON_RESUME);           // 0xA4

    writeCommand(DISPLAY_NORMALDISPLAY);                 // 0xA6
    
    writeCommand(DISPLAY_DEACTIVATE_SCROLL);
    writeBufferInit();                        //Display dimension setting
    writeCommand(DISPLAY_DISPLAYALLON);		/*--turn on oled panel */   
    R_Display_delay(200);

    if (g_DisplayStatus.state!=R_DISPLAY_OK_STATE)
    {
        return R_DISPLAY_ERROR;
    }

    return R_DISPLAY_OK;

}

/*****************************************************************************
** Function:    R_DISPLAY_DrawImg
** Description: Draws rectangular image data to RAM buffer
** Parameter:   row - Start coordinate 
**              pos - Start coordimate vertical
**              *image - Pointer to image 
** Return:      None
******************************************************************************/
void R_DISPLAY_DrawImg(uint8_t row, uint8_t pos, r_display_image *image)
{
    uint32_t i,j,k;
  k=0; 

  if(((image->num_rows*8+row*8)<=DISPLAY_HEIGHT)&&((image->width+pos)<=DISPLAY_WIDTH))
  {
      for(i=0;i<(image->num_rows);i++)
      {
           for(j=0;j<image->width;j++)
           {
                   displayBuffer[row+i][pos+j]=image->data[k++];
           }
      }
    }
}


/*****************************************************************************
** Function:    drawChar
** Description: Draw single character.
** Parameter:   row - Start coordinate x row
**              y - Start coordimate y (pixels)
**              c - character
**              color - Color of character

** Return:      None
******************************************************************************/
void drawChar(uint8_t row, uint8_t  pos , uint8_t c, uint8_t  color)
{
  uint8_t i;
  if(color == R_WHITE)
  {
      if((DISPLAY_HEIGHT/8) > row)
         {  
          for (i=0; i<5; i++ ) 
          {
                if((pos+i)<(DISPLAY_WIDTH))
                {
                    displayBuffer[row][pos+i]=font57[c*5+i];
                }
          }
          if((pos+5)<(DISPLAY_WIDTH))
            {
                    displayBuffer[row][pos+5]=0x00;
            }
        }
    }
    if(color == R_BLACK)
  {
      if((DISPLAY_HEIGHT/8) > row)
         {  
          for (i=0; i<5; i++ ) 
          {
                if((pos+i)<(DISPLAY_WIDTH))
                {
                    displayBuffer[row][pos+i]=~font57[c*5+i];
                }
          }
          if((pos+5)<(DISPLAY_WIDTH))
            {
                    displayBuffer[row][pos+5]=0xff;
            }
        }
    }
    
}


/*****************************************************************************
** Function:    drawCharBig
** Description: Draw single character.
** Parameter:   row - Start coordinate x row
**              pos - Start coordinate y (pixels)
**              c - character
**              color - Color of character

** Return:      None
******************************************************************************/
void drawCharBig(uint8_t row, uint8_t  pos , uint8_t c, uint8_t  color)
{
  uint8_t i;
  if(color == R_WHITE)
  {
      if((DISPLAY_HEIGHT/8) > row)
         {  
          for (i=0; i<12; i++ ) 
          {
                if((pos+i)<(DISPLAY_WIDTH))
                {
                    displayBuffer[row+1][pos+i]=font1216[c][i*2];
                    displayBuffer[row][pos+i]=font1216[c][i*2+1];
                }
          }
    
        }
  }
  if(color == R_BLACK)
  {
      if((DISPLAY_HEIGHT/8) > row)
         {  
          for (i=0; i<12; i++ ) 
          {
                if((pos+i)<(DISPLAY_WIDTH))
                {
                    displayBuffer[row+1][pos+i]=~font1216[c][i*2];
                    displayBuffer[row][pos+i]=~font1216[c][i*2+1];
                }
          }
    
        }
  }
}


/*****************************************************************************
** Function:    drawPixel
** Description: Draw a rectangle on the display.
** Parameter:   x - Start coordinate x (pixels)
**              y - Start coordimate y (pixels)
**              color - Color of pixel
** Return:      None
******************************************************************************/
void R_DISPLAY_rowFill(uint16_t row, uint16_t pos, uint16_t length ,uint8_t color)
{
    uint16_t i;
  for (i=pos; i<pos+length; i++ ) 
    {
        displayBuffer[row][i]=color;
    }
}




/*****************************************************************************
** Function:    drawText
** Description: Draw a rectangle on the display.
** Parameter:   x - Start coordinate x (pixels)
**              y - Start coordimate y (pixels)
**              *c - Pointer to text
**              color - Color of text
**              bg - Color of background
**              size - Font size 
** Return:      None
******************************************************************************/
void R_DISPLAY_DrawText(uint8_t row, uint8_t  pos, char* c,  uint8_t color, uint8_t fill) 
{
  uint8_t i=0;
  
  
  if((fill==R_FILL) && (pos>0))
    {
          R_DISPLAY_rowFill(row, 0, pos ,~color);
    }

 
  while(*c != 0)
  {  
    drawChar(row,pos+i*6,*c,color);
    c++;
    i++;
  }
  
  if((fill==R_FILL) && ((pos+i*6)<DISPLAY_WIDTH))
    {
          R_DISPLAY_rowFill(row, pos+i*6, DISPLAY_WIDTH-(pos+(i*6)) ,~color);
    } 
    
}



/*****************************************************************************
** Function:    drawTextBig
** Description: Draw a rectangle on the display.
** Parameter:   x - Start coordinate x (pixels)
**              y - Start coordimate y (pixels)
**              *c - Pointer to text
**              color - Color of text
**              bg - Color of background
**              size - Font size 
** Return:      None
******************************************************************************/
void R_DISPLAY_DrawTextBig(uint8_t row, uint8_t  pos, char* c,  uint8_t color, uint8_t fill) 
{
  uint8_t i=0;
    if((fill==R_FILL) && (pos>0))
    {
          R_DISPLAY_rowFill(row, 0, pos ,~color);
          R_DISPLAY_rowFill(row+1, 0, pos ,~color);
    }
  
  while(*c != 0)
    {  
      drawCharBig(row,pos+i*12,*c,color);
      c++;
      i++;
    }
      if((fill==R_FILL) && ((pos+i*12)<DISPLAY_WIDTH))
    {
          R_DISPLAY_rowFill(row, pos+i*12, DISPLAY_WIDTH-(pos+(i*6)) ,~color);
          R_DISPLAY_rowFill(row+1, pos+i*12, DISPLAY_WIDTH-(pos+(i*6)) ,~color);
    } 
    
}
uint64_t display_time;
/*****************************************************************************
** Function:    writeCommand
** Description: Set D/C to command and transmit command. 
** Parameter:   Command - Display controller command. 
** Return:      None
******************************************************************************/
r_DisplayError_t writeCommand(uint8_t Command) 
{
    if( R_DISPLAY_waitForIdle(100)==R_DISPLAY_OK)
    {
        cmd_send_buffer[0]=0;
        cmd_send_buffer[1]=Command;
        R_RIIC0_set_busy();
        R_RIIC0_Master_Send(0x3Du,cmd_send_buffer,2);
    }
    else
    {
        return R_DISPLAY_TIMEOUT;
    }

  return R_DISPLAY_OK;
}



/*****************************************************************************
** Function:    writeBufferInit
** Description: write RAM buffer to display
** Parameter:   
**              
** Return:      None
******************************************************************************/
void writeBufferInit(void)
{
    uint32_t i;

  // set display dimensions
  writeCommand(DISPLAY_COLUMNADDR);
  writeCommand(0);   // Column start address (0 = reset)
  writeCommand(DISPLAY_WIDTH-1); // Column end address (127 = reset)

  writeCommand(DISPLAY_PAGEADDR);
  writeCommand(0); // Page start address (0 = reset)
  #if DISPLAY_HEIGHT == 64
    writeCommand(7); // Page end address
  #endif
  #if DISPLAY_HEIGHT == 32
    writeCommand(3); // Page end address
  #endif
  #if DISPLAY_HEIGHT == 16
    writeCommand(1); // Page end address
  #endif
  
  //fill GDDRAM
  R_DISPLAY_waitForIdle(100);
  
  send_buffer[0]=0x40;
  for (i=0;i<((DISPLAY_WIDTH*DISPLAY_HEIGHT)/8);i++)
  {
      send_buffer[i+1]=displayBuffer[i/DISPLAY_WIDTH][i%DISPLAY_WIDTH];
  }
    R_RIIC0_set_busy();
    R_RIIC0_Master_Send(0x3Du,send_buffer,((DISPLAY_WIDTH*DISPLAY_HEIGHT)/8)+1);

}
/*****************************************************************************
** Function:    R_DISPLAY_writeBuffer_ifIDLE
** Description: Attempts to write display buffer to OLED if RIIC bus is not busy
** Parameter:   None
** Return:      R_DISPLAY_OK if write initiated successfully
**              R_DISPLAY_BUSY if RIIC bus is busy
******************************************************************************/
r_DisplayError_t R_DISPLAY_writeBuffer_ifIDLE(void) 
{
  uint32_t i;
  if(R_RIIC0_busy_state()==R_RIIC_NOT_BUSY )
  {  
    send_buffer[0]=0x40;  // Data command
    // Copy display buffer to send buffer
    for (i=0;i<((DISPLAY_WIDTH*DISPLAY_HEIGHT)/8);i++)
    {
      send_buffer[i+1]=displayBuffer[i/DISPLAY_WIDTH][i%DISPLAY_WIDTH];
    }
     R_RIIC0_set_busy();
     R_RIIC0_Master_Send(0x3Du,send_buffer,((DISPLAY_WIDTH*DISPLAY_HEIGHT)/8)+1);
     return R_DISPLAY_OK;
  }
  return R_DISPLAY_BUSY;
}

/*****************************************************************************
** Function:    R_DISPLAY_writeBuffer
** Description: Writes display buffer to OLED display, waiting for RIIC bus if needed
** Parameter:   None  
** Return:      R_DISPLAY_OK if write completed successfully
**              R_DISPLAY_TIMEOUT if RIIC bus timeout occurred
******************************************************************************/
r_DisplayError_t R_DISPLAY_writeBuffer(void)
{
  uint32_t i;
    
  if (R_DISPLAY_waitForIdle(100)==R_DISPLAY_OK)
  {
  send_buffer[0]=0x40;  // Data command
  // Copy display buffer to send buffer
  for (i=0;i<((DISPLAY_WIDTH*DISPLAY_HEIGHT)/8);i++)
  {
    send_buffer[i+1]=displayBuffer[i/DISPLAY_WIDTH][i%DISPLAY_WIDTH];
  }
    R_RIIC0_set_busy();
    R_RIIC0_Master_Send(0x3Du,send_buffer,((DISPLAY_WIDTH*DISPLAY_HEIGHT)/8)+1);
  }
  else
  {
  return R_DISPLAY_TIMEOUT;
  }
  return R_DISPLAY_OK;
}

/*****************************************************************************
** Function:    R_DISPLAY_waitForIdle
** Description: Waits for RIIC bus to become idle with timeout
** Parameter:   timeoutms - Maximum time to wait in milliseconds
** Return:      R_DISPLAY_OK if bus became idle
**              R_DISPLAY_TIMEOUT if timeout occurred
******************************************************************************/
r_DisplayError_t R_DISPLAY_waitForIdle(uint32_t timeoutms)
{
  uint32_t time = g_SystemStatus.RunTimeMs;
  while(R_RIIC0_busy_state()==R_RIIC_BUSY)
  {
    if(g_SystemStatus.RunTimeMs > (time+timeoutms))
    {
    g_DisplayStatus.state = R_DISPLAY_TIMEOUT_STATE;
    return R_DISPLAY_TIMEOUT;
    }
  }
  return R_DISPLAY_OK;
}

/*****************************************************************************
** Function:    delay
** Description: Simple local delay function.
** Parameter:   count
** Return:      None
******************************************************************************/
void R_Display_delay(uint32_t countms)
{
  uint32_t time = g_SystemStatus.RunTimeMs;
  while(g_SystemStatus.RunTimeMs < (time+countms))
  {
  }
}




