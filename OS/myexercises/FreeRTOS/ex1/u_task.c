#include "u_task.h"
#include "uart.h"
#include <stdint.h>

void InventoryPicker(void *pvParameters);
void PackingStation(void *pvParameters);
void ShippingController(void *pvParameters);
void LoggerSystem(void *pvParameters);

QueueHandle_t inv_to_pack; 
QueueHandle_t pack_to_ship;

void InventoryInitializer(void *pvParameters){
  UART_printf("InventoryInitializer\n");
  (void) pvParameters;

  inv_to_pack = xQueueCreate(10, sizeof(item)); 
  pack_to_ship= xQueueCreate(10, sizeof(item));

  vTaskDelete(NULL);
}

void InventoryPicker(void *pvParameters) { 
  UART_printf("InventoryPicker\n");   
	(void) pvParameters;
  uint8_t order_ID = 0;
    for (;;) {
      item new_item ={
          .id = 0,
          .item_status = picked,
          .info = NULL};
      //se succede un errore come dichiarare le variabili static e quindi la coda non é creata il probramma non si blocca
    //
      if (xQueueSend(inv_to_pack,&new_item, portMAX_DELAY) == pdPASS) {
          UART_printf("InventoryPicker: Order ID:%d -- Item Picked and sent to the PackingStation\n");   
      }else {
          UART_printf("InventoryPicker: Order ID:%d -- Error while picking the item and sending it\n");   
      }
      vTaskDelay(pdMS_TO_TICKS(1000));
      
    }
}


void PackingStation(void *pvParameters) { 

  UART_printf("PackingStation\n");   
	(void) pvParameters;
    
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(5000));
        item pick_item = {0};
        if (xQueueReceive(inv_to_pack, &pick_item, portMAX_DELAY) == pdPASS) {
          pick_item.item_status = packed;
          if(xQueueSend(pack_to_ship, &pick_item, portMAX_DELAY) == pdPASS){
              UART_printf("PackingStation: Order ID:%d -- Packed and sent to ShippingController\n");   
          }else{
              UART_printf("PackingStation: Order ID:%d -- Can't send the package to the ShippingController\n");   
          }  
        }else{
            UART_printf("PackingStation: Error while taking an item from the inventory\n");   
        } 
    }
}


void ShippingController(void *pvParameters) { 

	(void) pvParameters;
    
  UART_printf("ShippingController\n");   
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(7000));
        item pick_item = {0};
        if (xQueueReceive(pack_to_ship, &pick_item, portMAX_DELAY) == pdPASS) {
            pick_item.item_status = shipped;
            UART_printf("ShippingController: Order ID:%d -- Shipped\n");   
        }else{
            UART_printf("ShippingController: Error while taking an item from the Packed ones\n");   
        } 
    }
}

