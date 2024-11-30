#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "uart.h"
#include "stdio.h"
#include <stdlib.h>
#include <limits.h>

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 5 )
#define subTASK_PRIORITY    ( mainTASK_PRIORITY -2 )

// startup it is the first task running with the highest priority in the system. 
// Let's name this priority MAX_PRIRITY. This task create three additional tasks 
// named task1, task2, task3. Finally the task ends.
// 
// task1 and task2 have both priority equal to MAX_PRIRITY-2. 
// They work together to fill a global array of 20 elements. 
// task1 fills the even elements with consecutives powers of 2. 
// task2 fills the odd elements with consecutives powers of 3. When they are complete they end.
// 
// task3 must wait the end of task1 and task2 and print the array on screen.

void startup(void *pvParameters);
void task_1(void *pvParameters);
void task_2(void *pvParameters);
void task_3(void *pvParameters);

int num[20] = {0};
int end = 2;

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

  UART_init();
  xTaskCreate(startup, 
              "startup", 
              configMINIMAL_STACK_SIZE, 
              NULL, mainTASK_PRIORITY , 
              NULL);

	// Give control to the scheduler
	vTaskStartScheduler();

	// If everything ok should never reach here
    for( ; ; );
}


void startup(void *pvParameters){
  (void) pvParameters;
  xTaskCreate(task_1, 
              "task1", 
              configMINIMAL_STACK_SIZE, 
              NULL, 
              subTASK_PRIORITY , 
              NULL);

  xTaskCreate(task_2, 
              "task2", 
              configMINIMAL_STACK_SIZE, 
              NULL, 
              subTASK_PRIORITY , 
              NULL);

  xTaskCreate(task_3, 
              "task3", 
              configMINIMAL_STACK_SIZE, 
              NULL, 
              subTASK_PRIORITY , 
              NULL);
  vTaskDelete(NULL);
}

void task_1(void *pvParameters){
  (void) pvParameters;
  
  for (int i=1; i<+20; i++) {
      if((i%2)==0){
        num[i-1]=2^i;  
      }
  }
  end--;
  vTaskDelete(NULL);
}

void task_2(void *pvParameters){
  (void) pvParameters;
  
  for (int i=1; i<+20; i++) {
      if(i%3==0){
        num[i-1]=3^i;  
      }
  }
  end--;
  vTaskDelete(NULL);
}


void task_3(void *pvParameters){
  (void) pvParameters;
  while(1){
    if(end == 0){
      for (int i=0; i<20; i++) {
        char buf[10] = {0};
        sprintf(buf, "%d\n",num[i]);
        UART_printf(buf);
      }
    }
  }
  vTaskDelete(NULL);
}

