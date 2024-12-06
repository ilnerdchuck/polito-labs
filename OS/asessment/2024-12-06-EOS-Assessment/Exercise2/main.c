/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "uart.h"

/* Standard includes. */
#include <stdio.h>
#include <string.h>

/* Application includes. */
//#include "IntTimer.h"

/* printf() output uses the UART.  These constants define the addresses of the
 * required UART registers. */

#define UART0_ADDRESS                         ( 0x40004000UL )
#define UART0_DATA                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 0UL ) ) ) )
#define UART0_STATE                           ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 4UL ) ) ) )
#define UART0_CTRL                            ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 8UL ) ) ) )
#define UART0_BAUDDIV                         ( *( ( ( volatile uint32_t * ) ( UART0_ADDRESS + 16UL ) ) ) )
#define TX_BUFFER_MASK                        ( 1UL )

#define workTASK_PRIORITY (tskIDLE_PRIORITY + 1)
/* GLOBAL VARIABLES */

void taskA(void* param);
void taskB(void* param);

SemaphoreHandle_t semph;


static void prvUARTInit( void )
{
    UART0_BAUDDIV = 16;
    UART0_CTRL = 1;
}


void main( void )
{

    /* Hardware initialisation.   */
    prvUARTInit();
    //vInitialiseTimers();
    semph = xSemaphoreCreateMutex();
    xTaskCreate(
                taskA,
                "TaskA",
                configMINIMAL_STACK_SIZE,
                NULL,
                workTASK_PRIORITY+2,
                NULL      
                );
  
    xTaskCreate(
                taskB,
                "TaskB",
                configMINIMAL_STACK_SIZE,
                NULL,
                workTASK_PRIORITY,
                NULL      
                );
    /* Start the scheduler. */
    vTaskStartScheduler();

    for( ; ; ){}
}

// task A goes to sleep so task B is scheduled
// so B takes the semaphore and begins operation
// task A wakes up but goes back to waiting on the semaphore so TaskB
// is executing even if it has a minor priority
void taskA(void *param){
  (void) param;
  for (;;) {
    printf("Is TaskA time\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
    printf("TaskA is back\n");

    xSemaphoreTake(semph,portMAX_DELAY);
    
    //work on shared resurce
    printf("TaskA working\n");
    for (int i=0; i<555555555; ++i) {}
    printf("TaskA finished working\n");
    
    xSemaphoreGive(semph);
  }
}

void taskB(void *param){
  (void) param;
  for (;;) {
    printf("Is TaskB time\n");
    xSemaphoreTake(semph,portMAX_DELAY);
    printf("TaskB working\n");
    //work on shared resurce
    for (int i=0; i<555555555; ++i) {}
    printf("TaskB finished working\n");
    xSemaphoreGive(semph);
  }
}
