#include "u_task.h" 

conveyor_t conveyors[MAXconveyors] = {0};
SemaphoreHandle_t xMutexConveyors;


void initSystem(void *pvParameters){
  (void) pvParameters;
  for (int i=0; i<MAXconveyors; ++i) {
    conveyors[i].sync = xSemaphoreCreateBinary();
    if(!conveyors[i].sync){
      UART_printf("Can't create semaphores halting\n");
      while (1){}
    }
    conveyors[i].MAXitems = 9;
    conveyors[i].CurrItem = 0;
  }
  xMutexConveyors = xSemaphoreCreateMutex();
  if (!xMutexConveyors) {
    UART_printf("Can't allocate Mutex halting\n");
    while(1){}
  }
  vTaskDelete(NULL);
}

void ConveyorSystem(void *pvParameters){
  (void) pvParameters;
  for (;;) {
    for (int i=0; i<MAXconveyors; ++i) {
      if(xSemaphoreTake(xMutexConveyors, portMAX_DELAY) == pdTRUE){
        // send to conveyor i an item
        if (conveyors[i].CurrItem == conveyors[i].MAXitems) {
          //Belt full need to wait so i continue to the next Belt
          //TODO:
        }else{
          //add an item and signal with the semaphore
          conveyors[i].items[conveyors[i].CurrItem++] = rand()%50;
          xSemaphoreGive(conveyors[i].sync);
        }
        //Singal for the mutex and skidaddle 
        if(!xSemaphoreGive(xMutexConveyors)){
          //Notify watchdog and autokill
          //TODO:
          vTaskDelete(NULL);
        }
      }
    }
  }
  vTaskDelete(NULL);
}

void InspectionSystem(void *pvParameters){  
  (void) pvParameters;
  for (;;) {
    if(xSemaphoreTake(xMutexConveyors, portMAX_DELAY)){
      for (int i=0; i<MAXconveyors; ++i) {
        //In this implementation i handle only one item per belt 
        if(xSemaphoreTake(conveyors[i].sync, pdMS_TO_TICKS(1))){
          //i have taken the conveyor now i remove the item
          conveyors[i].items[--conveyors[i].CurrItem] = 0;
        }
      }
      //Release the mutex 
      if(!xSemaphoreGive(xMutexConveyors)){
        //Notify watchdog and autokill
        vTaskDelete(NULL);
      }
    }
  }
}

void LogSystem(void *pvParameters){
  (void) pvParameters;

  for (;;) {
    //logging logic 
  }
}

