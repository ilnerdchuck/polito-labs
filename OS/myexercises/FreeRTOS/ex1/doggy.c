#include "FreeRTOSConfig.h"
#include "doggy.h"
#include "projdefs.h"
#include "u_task.h"
#include "uart.h"
#include "timers.h"
#include <stdint.h>

taskInfo taskList[10];
int currRegTsk = 0;
TaskHandle_t doggyTaskHandle = NULL;

//main watchdog task 
void doggyTask(void *pvParameters){
  int timer = (int)pvParameters;
  vTaskDelay(pdMS_TO_TICKS(timer));
  char msg[500];
  for (int i=0; i<currRegTsk; ++i) {
    //check notification form task i and 
    if(ulTaskNotifyTakeIndexed(i, 0, 0) != 0){
      //no notification found, i will restart task i 
      vTaskDelete(taskList[i].TaskHandler);
      xTaskCreate(taskList[i].TaskCallback, 
                  taskList[i].TaskName, 
                  taskList[i].StackSize, 
                  taskList[i].Parameters, 
                  taskList[i].Prio, 
                  &taskList[i].TaskHandler);
    sprintf(msg, "%ul,%s, %ul,%ul,%d,%ul\n",taskList[i].TaskCallback, 
                  taskList[i].TaskName, 
                  taskList[i].StackSize, 
                  taskList[i].Parameters, 
                  taskList[i].Prio, 
                  &taskList[i].TaskHandler);
    UART_printf(msg);
    }
  }
  return;
} 

int initDoggy(int timer){
  if(doggyTaskHandle){
    UART_printf("ERROR: watchdog already initiated\n");
    return -1;
  }
  xTaskCreate(doggyTask, "Watchdog  doggy", configMINIMAL_STACK_SIZE, (void*)timer, configMAX_PRIORITIES - 4, &doggyTaskHandle);
  if(!doggyTaskHandle){
    UART_printf("ERROR: Can not create watchdog task\n");
    return -1;
  }
  UART_printf("INFO: Watchdog started\n");
  return 0;
}

//Function to register a task to the watchdog
int TaskDoggyRegister(taskInfo tskInfo){
  if (currRegTsk == 9) {
    //TODO: add sprintf to format string (maybe write your sprintf_uart)
    UART_printf("ERROR: Can't register task %s to the watchdog\n");
    return -1;
  }
  taskList[currRegTsk++] = tskInfo;
  return 0;
}

//Function to send a notification to the watchdog
int DoggySendAlive(int notifyIndex){
  if(!doggyTaskHandle){
    UART_printf("INFO: watchdog NOT INITIALIZED\n");
    return -1;
  }
  if(!xTaskNotify(doggyTaskHandle, notifyIndex, eSetValueWithOverwrite)){ 
    UART_printf("ERROR: Can't notify watchdog\n");
    return -1;
  }
  UART_printf("INFO: Task has notified\n");
  return 0;
}
