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

int counter =0;

uint16_t SinTable[45] =                                       /* ?????                       */
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};
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
	
	static int sineticks=0;
	/* DAC management */	
	static int currentValue; 
	currentValue = SinTable[sineticks];
	//is this the volume?
	currentValue -= 410;
	currentValue /= 1;
	currentValue += 410;
	LPC_DAC->DACR = currentValue <<4; //volume
	sineticks++;
	if(sineticks==45) sineticks=0;
	
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
	
	if(counter%powerUPspeed == 0 && ghostSpawn == 0){
		//---------------Blinky Updating----------------------------
		if(blinkyState.aFrame<8){
			animateBlinkyFrame();
		}else{
			updateBlinkyPos();
		}
	}
	
	if(counter%100 == 0){
		//-------------Pacman updating------------------------
	
		if(pacmanState.aFrame<8){
			animateFrame();
		}else{
			//ok to solve all issues you check nextpos: if valid u update it
			//othewise you check next currPos if valid you move
			//otherwise you are at a wall you draw filled pacman
			cellType _res = GetNextCellType(pacmanState.pmNextDir); //if wall i dont do anything i go check currNext dir call
			//If wall uses pmCurDir as next direction
			if(CheckIfWall(_res)){
				//non � un muro mi sposto quindi di nuova posizione
				updatePacmanPos(pacmanState.pmNextDir); //if no error update pacmanState
			}else if(pacmanState.pmCurrDir != pmStuck){
				//� un muro continuo con currdir
				_res = GetNextCellType(pacmanState.pmCurrDir);
				if(CheckIfWall(_res)){
					//Pacman is not at a wall
					updatePacmanPos(pacmanState.pmCurrDir);
				}else{
					//pacman is at a wall for the ffirst time u draw filled pacman
					updatePacmanPos(pmStuck);
				}
			}
		}
	}
	counter++;
	LPC_TIM1->IR = 1;
	
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
	//DrawTime(--gameTime, White, Black);
	--gameTime;
	if(powerUP==0){
		powerUP=0;
		powerUPspeed = 95;
	}else{
		--powerUP;
	}
	
	ghostSpawn = ghostSpawn==0?ghostSpawn:ghostSpawn-1;
	
	SendCanInfo();
	if(!gameTime){
		SetGameOver();
	}
	if(getRandomDecision() && pacmanState.pmCurrDir!=pmStuck && largeDotRemaining){
		SpawnLargeDot();
	}
	LPC_TIM2->IR = 1;			/* clear interrupt flag */
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
void TIMER3_IRQHandler (void){
	disable_timer(0);
	LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}
/******************************************************************************
**                            End Of File
******************************************************************************/
