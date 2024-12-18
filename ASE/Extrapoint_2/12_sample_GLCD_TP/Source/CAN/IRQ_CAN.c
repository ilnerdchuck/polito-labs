/*----------------------------------------------------------------------------
 * Name:    Can.c
 * Purpose: CAN interface for for LPC17xx with MCB1700
 * Note(s): see also http://www.port.de/engl/canprod/sv_req_form.html
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <LPC17xx.h>                  /* LPC17xx definitions */
#include "CAN.h"                      /* LPC17xx CAN adaption layer */
#include "../GLCD/GLCD.h"
#include "../pacman/pacman_lib.h"

extern uint8_t icr ; 										//icr and result must be global in order to work with both real and simulated landtiger.
extern uint32_t result;
extern CAN_msg       CAN_TxMsg;    /* CAN message for sending */
extern CAN_msg       CAN_RxMsg;    /* CAN message for receiving */                                

/*----------------------------------------------------------------------------
  CAN interrupt handler
 *----------------------------------------------------------------------------*/
int oldtime =0;
int oldscore =0;
int oldlives =0;
void CAN_IRQHandler (void)  {

	icr = 0;
	icr = (LPC_CAN2->ICR | icr) & 0xFF;             /* clear interrupts */

	if (icr & (1 << 0)) {
	
		CAN_rdMsg (2, &CAN_RxMsg);	                		/* Read the message */
    LPC_CAN2->CMR = (1 << 2);                    		/* Release receive buffer */
		uint16_t score = 0;
		uint16_t lives = 0;
		uint16_t time = 0;
		
		//TODO: review send i dont like sending the high part then the low part
		score = (CAN_RxMsg.data[0] << 8);
		score = score | CAN_RxMsg.data[1];
		
		lives = CAN_RxMsg.data[2];
		time = CAN_RxMsg.data[3];

		if(gameTime!=oldtime){
			DrawTime(time, White, Black);
		}
		if(playerPoints!=oldscore){
			DrawScore(score, White, Black);
		}
		if(playerLives!=oldlives){
			DrawLives(lives);
		}
		
		oldscore = score;
		oldlives = lives;
		oldtime = time;
	}
	
}
