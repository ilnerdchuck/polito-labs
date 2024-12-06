#pragma once
#include "FreeRTOS.h"
#include "semphr.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h> 
#include "uart.h"
#include "task.h"
#include "portmacro.h"
#include "projdefs.h"
#include <doggy.h>

#define mainTASK_PRIORITY (tskIDLE_PRIORITY + 3)
#define workerTASK_PRIORITY (tskIDLE_PRIORITY + 2)
#define logTASK_PRIORITY (tskIDLE_PRIORITY + 1)

typedef enum {
  picked,
  packed,
  shipped,
}status;

typedef struct {
  uint8_t id;
  uint16_t prio;
  status item_status;
  char* info;
}item ;

extern QueueHandle_t inv_to_pack;
extern QueueHandle_t pack_to_ship;

void InventoryInitializer(void *pvParameters);
void InventoryPicker(void *pvParameters);
void PackingStation(void *pvParameters);
void ShippingController(void *pvParameters);
void LoggerSystem(void *pvParameters);


