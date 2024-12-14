/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "LPC17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "pacman/pacman_lib.h"
#include "RIT/RIT.h"
#include <stdio.h> 

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER0_IRQHandler (void){
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void){
	if(gameStatus != 0 || pacmanState.pmNextDir == pmStuck){
		//the game is not running i dont have to update (error handling)
		LPC_TIM1->IR = 1;	
		return;
	}
	//ok to solve all issues you check nextpos: if valid u update it
	//othewise you check next currPos if valid you move
	//otherwise you are at a wall you draw filled pacman
	cellType _res = GetNextCellType(pacmanState.pmNextDir); //if wall i dont do anything i go check currNext dir call
	//If wall uses pmCurDir as next direction
	if(CheckIfWall(_res)){
		//non é un muro mi sposto quindi di nuova posizione
		updatePacmanPos(pacmanState.pmNextDir); //if no error update pacmanState
		UpdateScore(_res);
	}else if(pacmanState.pmCurrDir != pmStuck){
		//é un muro continuo con currdir
		_res = GetNextCellType(pacmanState.pmCurrDir);
		if(CheckIfWall(_res)){
			//Pacman is not at a wall
			updatePacmanPos(pacmanState.pmCurrDir);
		}else{
			//pacman is at a wall for the ffirst time u draw filled pacman
			updatePacmanPos(pmStuck);
		}
	}
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 2 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER2_IRQHandler (void){
	//handles game time
	DrawTime(--gameTime, White, Black);	//otherwise update the neext position
	if(!gameTime){
		SetGameOver();
	}
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}
/******************************************************************************
**                            End Of File
******************************************************************************/
