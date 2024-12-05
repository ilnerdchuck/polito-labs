#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"

#define mainTASK_PRIORITY    ( tskIDLE_PRIORITY + 4 )
#define highTASK_PRIORITY    ( tskIDLE_PRIORITY + 3 )
#define mediumTASK_PRIORITY  ( tskIDLE_PRIORITY + 2 )
#define lowTASK_PRIORITY     ( tskIDLE_PRIORITY + 1 )
#define MAXconveyors 3

struct {
  int items[10];
  int MAXitems;
  int CurrItem;
  SemaphoreHandle_t sync;
} typedef conveyor_t;

void initSystem(void *pvParameters);
void ConveyorSystem(void *pvParameters);
void InspectionSystem(void *pvParameters);
void LogSystem(void *pvParameters);
void Watchdog(void *pvParameters);


