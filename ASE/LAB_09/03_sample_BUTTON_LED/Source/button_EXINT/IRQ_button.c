#include "button.h"
#include "lpc17xx.h"

#include "../led/led.h"

extern unsigned char next_state(unsigned char ,unsigned char ,int*);

extern unsigned char taps;
extern unsigned char curr_state;
int output;

void EINT0_IRQHandler (void)	  
{
		int count =0;
		unsigned char nt_state = next_state(curr_state,taps,&output);
		count++;
		// check if current state is equal to the old state we cycled 
		// until the new state
		while(nt_state != curr_state){
				nt_state = next_state(nt_state,taps,&output);
				count++;
		}
		LED_Out(count);
		LPC_SC->EXTINT &= (1 << 0);
}

void EINT1_IRQHandler (void)	  
{
	
		unsigned char nt_state = next_state(curr_state,taps,&output);
		LPC_GPIO2->FIOSET = nt_state;
		LPC_SC->EXTINT &= (1 << 1);
}

void EINT2_IRQHandler (void)	  
{
	LED_Off(0);
	LED_Off(1);
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}