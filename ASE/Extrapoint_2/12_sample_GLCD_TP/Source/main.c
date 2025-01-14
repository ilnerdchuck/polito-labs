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
//#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "pacman/pacman_lib.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


//So i know i made a type but to fill out the matrix it's easier with numbers
/*
	smallDot, //0
	largeDot, //1
	vWall, 		//2
	hWall, 		//3
	tlAngle, 	//4
	trAngle, 	//5
	blAngle, 	//6
	brAngle, 	//7
	pacman, 	//8
	teleport, //9
	blank 		//10
	blinky 		//11
	intersection 		//12
	emptyinter 		//13
*/
//GAME VARIABLES - for info see the pacman.h file
uint8_t powerUPspeed = 95;
uint16_t playerPoints = 0;	//Handles player pointsl
uint8_t playerLives = 1;		//Handles 
uint8_t playEat = 0;				//Handle sound 
uint8_t powerUP = 0;
uint16_t gamePoints = 0; 		//Handles how many white points are in the game 
pmState pacmanState;				//Handles pacman state 
pmState blinkyState;
uint8_t gameTime = 60;			//Handles game time
uint8_t gameStatus = 1; 		//0 game running 1 game paused 2 game won 3 game lost
uint8_t  largeDotRemaining = N_LARGE_DOT;
cellType GameState[GAME_ROWS][GAME_COLUMNS]={
 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5,10, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5,
 2,12, 0, 0, 0, 0, 0,12, 0, 0, 0, 0,12, 2,10, 2,12, 0, 0, 0, 0,12, 0, 0, 0, 0, 0, 0,12, 2,
 2, 0, 4, 3, 3, 3, 5, 0, 4, 3, 3, 5, 0, 2,10, 2, 0, 4, 3, 3, 5, 0, 4, 3, 3, 3, 3, 5, 0, 2,
 2, 0, 2,10,10,10, 2, 0, 2,10,10, 2, 0, 2,10, 2, 0, 2,10,10, 2, 0, 2,10,10,10,10, 2, 0, 2,
 2, 0, 6, 3, 3, 3, 7, 0, 6, 3, 3, 7, 0, 6, 3, 7, 0, 6, 3, 3, 7, 0, 6, 3, 3, 3, 3, 7, 0, 2,
 2,12, 0, 0, 0, 0, 0,12, 0, 0, 0, 0,12, 0, 0, 0,12, 0, 0, 0, 0,12, 0, 0, 0, 0, 0, 0,12, 2,
 2, 0, 4, 3, 3, 3, 5, 0, 4, 3, 3, 5, 0, 4, 3, 5, 0, 4, 3, 3, 5, 0, 4, 3, 3, 3, 3, 5, 0, 2,
 2, 0, 6, 3, 3, 5, 2, 0, 2,10,10, 2, 0, 2,10, 2, 0, 2,10,10, 2, 0, 2,10, 4, 3, 3, 7, 0, 2,
 2,12, 0, 0,12, 6, 7, 0, 6, 3, 3, 7, 0, 6, 3, 7, 0, 6, 3, 3, 7, 0, 6, 3, 7,12, 0, 0,12, 2,
 6, 3, 3, 5,12, 0, 0,12, 0,12, 0, 0,12, 0,11, 0,12, 0, 0,12, 0,12, 0, 0, 0,12, 4, 3, 3, 7,
 3, 3, 3, 7, 0, 4, 3, 3, 5, 0, 4, 3, 3, 3, 3, 3, 3, 3, 5, 0, 4, 3, 3, 3, 5, 0, 6, 3, 3, 3,
 9,10,10,10, 0, 2,10,10, 2, 0, 2,10,10,10,10,10,10,10, 2, 0, 2,10,10,10, 2, 0,10,10,10, 9,
 3, 3, 3, 5, 0, 2,10,10, 2, 0, 2,10,10,10,10,10,10,10, 2, 0, 2,10,10,10, 2, 0, 4, 3, 3, 3,
 4, 3, 3, 7, 0, 6, 3, 3, 7, 0, 6, 3, 3, 3, 3, 3, 3, 3, 7, 0, 6, 3, 3, 3, 7, 0, 6, 3, 3, 5,
 2,12, 0, 0,12, 0,12, 0, 0,12, 0,12, 0, 0, 8, 0,12, 0, 0,12, 0,12, 0, 0, 0,12, 0, 0,12, 2,
 2, 0, 4, 3, 3, 5, 0, 4, 3, 3, 5, 0, 4, 3, 3, 5, 0, 4, 3, 3, 5, 0, 4, 3, 3, 3, 3, 5, 0, 2,
 2, 0, 2,10,10, 2, 0, 2,10,10, 2, 0, 2,10,10, 2, 0, 2,10,10, 2, 0, 2,10,10,10,10, 2, 0, 2,
 2, 0, 2,10,10, 2, 0, 2,10,10, 2, 0, 2,10,10, 2, 0, 2,10,10, 2, 0, 2,10,10,10,10, 2, 0, 2,
 2, 0, 6, 3, 3, 7, 0, 2,10,10, 2, 0, 2,10,10, 2, 0, 2,10,10, 2, 0, 6, 3, 3, 3, 3, 7, 0, 2,
 2,12, 0, 0, 0, 0,12, 2,10,10, 2, 0, 2,10,10, 2, 0, 2,10,10, 2,12, 0, 0, 0, 0, 0, 0,12, 2,
 2, 0, 4, 3, 3, 5, 0, 2,10,10, 2, 0, 2,10,10, 2, 0, 2,10,10, 2, 0, 4, 3, 3, 3, 3, 5, 0, 2,
 2, 0, 2,10,10, 2, 0, 2,10,10, 2, 0, 2,10,10, 2, 0, 2,10,10, 2, 0, 2,10,10,10,10, 2, 0, 2,
 2, 0, 2,10,10, 2, 0, 2,10,10, 2, 0, 2,10,10, 2, 0, 2,10,10, 2, 0, 2,10,10,10,10, 2, 0, 2,
 2, 0, 6, 3, 3, 7, 0, 6, 3, 3, 7, 0, 6, 3, 3, 7, 0, 6, 3, 3, 7, 0, 6, 3, 3, 3, 3, 7, 0, 2,
 2,12, 0, 0, 0, 0,12, 0, 0, 0, 0,12, 0, 0, 0, 0,12, 0, 0, 0, 0,12, 0, 0, 0, 0, 0, 0,12, 2,
 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7
};

int main(void)
{
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  LCD_Initialization();
	
	CAN_Init();
	
	//ADC_init();
	int _err = initGame();
	_err = init_hardware();
	
	//ADC things
	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);
  
	while (1){
		__ASM("wfi");
  }
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/




