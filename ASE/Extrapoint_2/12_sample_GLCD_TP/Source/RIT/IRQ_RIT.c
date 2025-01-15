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
#include "../timer/timer.h"
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
// beat 1/4 = 1.65/4 seconds
#define RIT_SEMIMINIMA 8
#define RIT_MINIMA 16
#define RIT_INTERA 32

#define UPTICKS 1

NOTE eat[] = 
{
    {e3, time_semibiscroma/2},  // E4, 1/16
		{a3b, time_semibiscroma/2},
		{c4, time_semibiscroma/2},
		{e4b, time_semibiscroma/2},
		{g4b, time_semibiscroma/2},
		{b4b, time_semibiscroma/2},
		{pause, time_biscroma/2},
		{b4, time_semibiscroma/2},
		{g4, time_semibiscroma/2},
		{e4, time_semibiscroma/2},
		{d4b, time_semibiscroma/2},
		{a3, time_semibiscroma/2},
		{f3, time_semibiscroma/2},
};


NOTE start[] = 
{
	// 1
	{b3,  time_croma},
	{b4,  time_croma},
	{g4b, time_croma},
	{e4b, time_croma},
	{b4,  time_semicroma},
	{g4b, time_croma},
	{e4b, time_croma*3/2},

	{c4, time_croma},
	{c5, time_croma},
	{g4, time_croma},
	{e4, time_croma},
	{c5, time_semicroma},
	{g4, time_croma},
	{e4, time_croma*3/2},
	
	{b3,  time_croma},
	{b4,  time_croma},
	{g4b, time_croma},
	{e4b, time_croma},
	{b4,  time_semicroma},
	{g4b, time_croma},
	{e4b, time_croma*3/2},
	
	{e4b, time_semicroma},
	{e4,  time_semicroma},
	{f4,  time_croma},
	{f4,  time_semicroma},
	{g4b, time_semicroma},
	{g4,  time_croma},
	{a4b, time_semicroma},
	{a4,  time_croma},
	{b4,  time_semiminima},
	
};
NOTE death[] = 
{
	// 1
	{a5b, time_semibiscroma/2},
	{g5, time_semibiscroma/2},
	{a5b, time_semibiscroma/2},
	{g5, time_semibiscroma/2},
	{g5b, time_semibiscroma/2},
	{g5, time_semibiscroma/2},
	{g5b, time_semibiscroma/2},
	{f5, time_semibiscroma/2},
	{g5b, time_semibiscroma/2},
	{f5, time_semibiscroma/2},
	{e5, time_semibiscroma/2},
	{e5b, time_semibiscroma/2},
	{e5, time_semibiscroma/2},
	{e5b, time_semibiscroma/2},
	{d5, time_semibiscroma/2},
	{e5b, time_semibiscroma/2},
	{d5, time_semibiscroma/2},
	{d5b, time_semibiscroma/2},
	{d5, time_semibiscroma/2},
	{d5b, time_semibiscroma/2},
	{c5, time_semibiscroma/2},
	{d5b, time_semibiscroma/2},
	{c5, time_semibiscroma/2},
	{b4, time_semibiscroma/2},
	{b4b, time_semibiscroma/2},
	{b4, time_semibiscroma/2},
	{b4b, time_semibiscroma/2},
	{a4, time_semibiscroma/2},
	{b4b, time_semibiscroma/2},
	{a4, time_semibiscroma/2},
	{a4b, time_semibiscroma/2},
	{a4, time_semibiscroma/2},
	{pause, time_semibiscroma/2},
	{g4, time_semibiscroma/2},
	{b4, time_semibiscroma/2},
	{d5, time_semibiscroma/2},
	{pause, time_semibiscroma},
	{g4, time_semibiscroma/2},
	{b4, time_semibiscroma/2},
	{d5, time_semibiscroma/2},
};

NOTE win[] = 
{
    {b3b, time_croma},
		{pause, time_croma},
		{g3b, time_croma},
		{pause, time_croma*3},
		{g3b, time_croma},
		{e3b, time_croma},
		{g3b, time_croma},
		{g3b, time_croma},
		{pause, time_croma*3},
		{g3b, time_croma},
		{e3b, time_croma},
		{g3b, time_croma},
		{g3b, time_croma},
		{pause, time_croma*3},
		{g3b, time_croma},
		{pause, time_croma*2},
		{b3b, time_croma},
		
};


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
				++down;
			}
		}else{
			down = 0;
			NVIC_EnableIRQ(EINT0_IRQn);
			LPC_PINCON->PINSEL4 |= (1<<20);
		}
	}
	// TODO fix speaker
	//i can reset the rit bot i configured in the RIT interrupt init to reset and count
	static int currentEatNote = 0;
	static int currentStartNote = 0;
	static int currentDeathNote =0;
	static int currentWinNote =0;
	static int ticks = 0;

	if(playWin== 1){
		if(!isNotePlaying()){
			++ticks;
			if(ticks == UPTICKS){
				ticks = 0;
				playNote(win[currentWinNote++]);
			}
			if(currentWinNote ==(sizeof(win)/sizeof(win[0]))){
				currentWinNote = 0;
				playWin=0;
			}
		}
	}
	
	if(playDeath== 1){
		if(!isNotePlaying()){
			++ticks;
			if(ticks == UPTICKS){
				ticks = 0;
				playNote(death[currentDeathNote ++]);
			}
			if(currentDeathNote ==(sizeof(death)/sizeof(death[0]))){
				currentDeathNote = 0;
				playDeath=0;
			}
		}
	}
	
	if(playEat== 1){
		if(!isNotePlaying()){
			++ticks;
			if(ticks == UPTICKS){
				ticks = 0;
				playNote(eat[currentEatNote++]);
			}
			if(currentEatNote ==(sizeof(eat)/sizeof(eat[0]))){
				currentEatNote = 0;
				playEat =0;
			}
		}
	}
	
	if(playStart== 1 && gameStatus==1){
		if(!isNotePlaying()){
			++ticks;
			if(ticks == UPTICKS){
				ticks = 0;
				playNote(start[currentStartNote++]);
			}
			if(currentStartNote == (sizeof(start)/sizeof(start[0]))){
				currentStartNote = 0;
				playStart =0;
			}
		}
	}
	
	reset_RIT();
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
  return;
}
/******************************************************************************
**                            End Of File
******************************************************************************/
