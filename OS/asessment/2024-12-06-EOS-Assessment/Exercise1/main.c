/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "portmacro.h"
#include "projdefs.h"
#include "task.h"
#include "semphr.h"

/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Application includes. */
#include "IntTimer.h"

/* printf() output uses the UART.  These constants define the addresses of the
 * required UART registers. */

#define UART0_ADDRESS                         ( 0x40004000UL )
#define UART0_DATA                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 0UL ) ) ) )
#define UART0_STATE                           ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 4UL ) ) ) )
#define UART0_CTRL                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 8UL ) ) ) )
#define UART0_BAUDDIV                         ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 16UL ) ) ) )
#define TX_BUFFER_MASK                        ( 1UL )


#define workTASK_PRIORITY (tskIDLE_PRIORITY + 1)


static void prvUARTInit( void )
{
    UART0_BAUDDIV = 16;
    UART0_CTRL = 1;
}

//timer handler in iniTimer.c

SemaphoreHandle_t sem;

void taskA(void *param);

void main( void )
{

    /* Hardware initialisation.   */
    prvUARTInit();
    vInitialiseTimers();
    sem = xSemaphoreCreateBinary();
    xTaskCreate(
                taskA,
                "TaskA",
                configMINIMAL_STACK_SIZE,
                NULL,
                workTASK_PRIORITY,
                NULL      
                );
    /* Start the scheduler. */
    vTaskStartScheduler();

    for( ; ; )
    {
    }

}

void taskA(void *param){
  (void) param;
  int matrix1[9];
  int matrix2[9];
  int matrix3[9];
  for (;;) {
    xSemaphoreTake(sem, portMAX_DELAY);
    printf("Started multiplications\n");
    for (int i=0; i<3 ;++i) {  
      for (int j=0; j<3 ;++j) {
        matrix1[i+j] = rand()% 1000;
        matrix2[i+j] = rand()% 1000;
        matrix3[i+j] = matrix1[i+j]*matrix2[i+j];  
      } 
    }
    printf("Finished multiplications\n");
  }
}
