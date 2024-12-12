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

volatile int down=0;

void RIT_IRQHandler (void)
{					
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
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
