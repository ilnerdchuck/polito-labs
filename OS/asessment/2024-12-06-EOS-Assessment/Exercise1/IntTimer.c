/* Scheduler includes. */
#include "FreeRTOS.h"
#include "semphr.h"
#include "stdio.h"
/* Demo includes. */
#include "IntTimer.h"
/* Library includes. */
#include "SMM_MPS2.h"

#define tmrTIMER_0_FREQUENCY	( 20 )


void vInitialiseTimers( void )
{
	CMSDK_TIMER0->INTCLEAR = ( 1ul <<  0 );
	CMSDK_TIMER0->RELOAD   = ( configCPU_CLOCK_HZ / tmrTIMER_0_FREQUENCY );
	CMSDK_TIMER0->CTRL     = ( ( 1ul <<  3 ) | /* Enable Timer interrupt. */
						     ( 1ul <<  0 ) );  /* Enable Timer. */
	NVIC_EnableIRQ( TIMER0_IRQn );
}

volatile uint32_t intServ = 0;
extern SemaphoreHandle_t sem;

void Timer0_Handler( void ){

    BaseType_t tsk = pdFALSE;
    //Clearing the timer interrupt
    CMSDK_TIMER0->INTCLEAR = ( 1ul <<  0 );
    printf("Interrupt served %u\n", ++intServ);
    //giving the semaphore so the task can go 
    xSemaphoreGiveFromISR(sem, &tsk);
    //checking if i woke up a high prio task
	  portEND_SWITCHING_ISR( tsk );
    return;
}
