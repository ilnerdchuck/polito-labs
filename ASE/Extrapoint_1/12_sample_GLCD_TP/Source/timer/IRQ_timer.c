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
	int _res = CheckNextPos(pacmanState.pmNextDir);
	if(_res == -1){
		//in this case is a wall so i exit and leave the state as is 
		// but draw a filled pacman as the main game
		if(pacmanState.pmCurrDir != pmStuck){
			DrawFilledPacman(pacmanState.pmYpos*CELL_DIM,pacmanState.pmXpos*CELL_DIM+TEXT_OFFSET, Yellow, Black);
			pacmanState.pmCurrDir = pmStuck;
		}
		LPC_TIM1->IR = 1;	
		return;
	}else if(_res == 0){
			//small dot;
			playerPoints += 10;
			DrawScore(playerPoints);
	}else if(_res == 1){
			//large dot;
			playerPoints += 50;
			DrawScore(playerPoints);
	}
	//otherwise update the neext position
	updatePacmanPos(pacmanState.pmNextDir);
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
	DrawTime(--gameTime);	//otherwise update the neext position
	if(!gameTime){
		//TODO: interrupt everthing and game over
		//for now disables the joystick and this timer
		LPC_TIM2->IR = 1;
		disable_RIT();
		disable_timer(2);
	}
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}
/******************************************************************************
**                            End Of File
******************************************************************************/
