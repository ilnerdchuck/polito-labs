#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 2 )

void producer(void *pvParameters);
void consumer(void *pvParameters);

SemaphoreHandle_t xRead,xWrite;

uint16_t buffer[10] = {0};
uint16_t head, tail = 0; 

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

  UART_init();
  xRead = xSemaphoreCreateCounting(10, 0);
  xWrite = xSemaphoreCreateCounting(10, 10);
  

	xTaskCreate(
		producer,
		"Task1",
		configMINIMAL_STACK_SIZE,
		NULL,
		mainTASK_PRIORITY,
		NULL
	);


	xTaskCreate(
		consumer,
		"Task2",
		configMINIMAL_STACK_SIZE,
		NULL,
		mainTASK_PRIORITY,
		NULL
	);

	vTaskStartScheduler();
    for( ; ; );
}

void producer(void *pvParameters) {

	(void) pvParameters;
    
    for (;;) {
        char buff[30] = {0};
        if(xSemaphoreTake(xWrite, portMAX_DELAY) == pdTRUE){
          
          buffer[head] = rand() % 300;
          sprintf(buff, "TASK0: numero loggato %d\n", buffer[head]);
          UART_printf(buff);
          head = (head+1)%10;

          xSemaphoreGive(xRead);
        }else{
          UART_printf("Task1: Can't access the shared resurce\n");
        }
        vTaskDelay(pdMS_TO_TICKS(rand()%3000 + 500));
    }
}


void consumer(void *pvParameters) {

	(void) pvParameters;
    for (;;) {
        char buff[30] = {0};
        if(xSemaphoreTake(xRead, portMAX_DELAY) == pdTRUE){
          sprintf(buff, "TASK2: numero loggato %d\n", buffer[tail]);
          UART_printf(buff);
          tail = (tail+1)%10;
          xSemaphoreGive(xWrite);
        }else{
          UART_printf("Task2: Can't access the shared resurce\n");
        }
        vTaskDelay(pdMS_TO_TICKS(rand()%3000 + 500));
    }
}
