/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "RIT.h"
#include "pacman/pacman_lib.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
int down = 0;
void RIT_IRQHandler (void)
{		
	//Joystick handler
	if(!(LPC_GPIO1->FIOPIN & (1<<26))){
		//Down
		pacmanState.pmNextDir = pmDown;
	}else if(!(LPC_GPIO1->FIOPIN & (1<<27))){
		//Left
		pacmanState.pmNextDir = pmLeft;  
	}else if(!(LPC_GPIO1->FIOPIN & (1<<28))){
		//Right
		pacmanState.pmNextDir = pmRight;
	}else if (!(LPC_GPIO1->FIOPIN & (1<<29))){
		//Up
		pacmanState.pmNextDir = pmUp;  
	}else{
		pacmanState.pmNextDir = pacmanState.pmCurrDir;  
	}
	
	
	//button debounced
	if(down != 0){
		if(!(LPC_GPIO2->FIOPIN & (1<<10))){
			if(down==1){
				PauseToggle();
			}
		}else{
			down = 0;
			NVIC_EnableIRQ(EINT0_IRQn);
			LPC_PINCON->PINSEL4 |= (1<<20);
		}
		++down;
	}
	//i can reset the rit bot i configured in the RIT interrupt init to reset and count
	reset_RIT();
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
