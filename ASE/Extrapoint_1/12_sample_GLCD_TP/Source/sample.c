/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"


#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	
  LCD_Initialization();
	
  //TP_Init();
	//TouchPanel_Calibrate();
	
	LCD_Clear(Black);
		//Game time text
	GUI_Text(20, 0, (uint8_t *) "GAME TIME", White, Black);
	GUI_Text(30, 16, (uint8_t *) "100s", White, Black);
	//Score Text
	GUI_Text(180, 0, (uint8_t *) "SCORE", White, Blue);
	GUI_Text(180, 16, (uint8_t *) "000", Red, Red);
	///
	GUI_Text(180, 32, (uint8_t *) "0", Red, Red);
	GUI_Text(180, 48, (uint8_t *) "0", Blue, Blue);
	GUI_Text(180, 64, (uint8_t *) "0", Green, Green);
	GUI_Text(180, 82, (uint8_t *) "0", Yellow, Yellow);
	
	DrawPoint( 200, 200, 0, White, Black);
	DrawPoint( 200, 220, 1, White, Black);
	
	//LCD_DrawLine(200, 200, 220, 220, White);
	//init_timer(0, 0x1312D0 ); 						/* 50ms * 25MHz = 1.25*10^6 = 0x1312D0 */
	//init_timer(0, 0x6108 ); 						  /* 1ms * 25MHz = 25*10^3 = 0x6108 */
	//init_timer(0, 0x4E2 ); 						    /* 500us * 25MHz = 1.25*10^3 = 0x4E2 */
	init_timer(0, 0xC8 ); 						    /* 8us * 25MHz = 200 ~= 0xC8 */
	
	enable_timer(0);
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
