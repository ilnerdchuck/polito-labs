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
#include "../led/led.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void RIT_IRQHandler (void)
{			
		/* Static as its value persists between calls to the function. It is not reinitialized each time the function is executed.*/
		static int down=0;	
		down++;
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){  	
			extern int buffer[];
			reset_RIT();
			int sum = 0;
			//order and average of the 	buffer[pos++%7000]=LPC_TIM1->IR;
			if(down == 1){
				int i,j;
				for (i = 0; i < 7000 - 1; i++) {
							sum += buffer[i];
							// Last i elements are already in place, so no need to check them
							for (j = 0; j < 7000 - i - 1; j++) {
									// If the element found is greater than the next element, swap them
									if (buffer[j] > buffer[j + 1]) {
											// Swap arr[j] and arr[j+1]
											int temp = buffer[j];
											buffer[j] = buffer[j + 1];
											buffer[j + 1] = temp;
									}
							}
					}
				sum = sum/7000;
				for (i = 0; i < 7000 ; i++) {
					buffer[i] = 0xCAFECAFE; 
				}
				//I turn on a led to see the end of computatation
				LED_On(7);
			}			
		}
		else {	/* button released */
			down=0;			
			disable_RIT();
			reset_RIT();
			LED_Off(7);
			//Clear the timers so i can handle the next interrupt
			LPC_TIM2->IR |= 3;			/* clear interrupt flag */
			LPC_TIM3->IR |= 3;			/* clear interrupt flag */
			NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/ 
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
		}
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
