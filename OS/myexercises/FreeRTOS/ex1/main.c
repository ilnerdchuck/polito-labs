#include "FreeRTOSConfig.h"
#include "doggy.h"
#include "u_task.h"
#include "uart.h"

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

  UART_init();
  TaskHandle_t taskTmp;
	BaseType_t _err = xTaskCreate(
		InventoryInitializer,
		"invInit",
		configMINIMAL_STACK_SIZE,
		NULL,
		mainTASK_PRIORITY,
		NULL
	);
    
  _err = xTaskCreate(
		InventoryPicker,
		"InventoryPicker",
		configMINIMAL_STACK_SIZE,
		NULL,
		workerTASK_PRIORITY,
		&taskTmp
	);
	taskInfo tsk1_info = { 
                        .TaskCallback = InventoryPicker,
                        .TaskName = "InventoryPicker",
                        .StackSize = configMINIMAL_STACK_SIZE,
                        .Parameters = NULL,
                        .Prio = workerTASK_PRIORITY,
                        .TaskHandler = taskTmp
                };
  TaskDoggyRegister(tsk1_info);

	_err = xTaskCreate(
		PackingStation,
		"PackingStation",
		configMINIMAL_STACK_SIZE,
		NULL,
		workerTASK_PRIORITY,
		&taskTmp
	);
	taskInfo tsk2_info = { 
                        .TaskCallback = PackingStation,
                        .TaskName = "PackingStation",
                        .StackSize = configMINIMAL_STACK_SIZE,
                        .Parameters = NULL,
                        .Prio = workerTASK_PRIORITY,
                        .TaskHandler = taskTmp
                };
  TaskDoggyRegister(tsk2_info);
	_err = xTaskCreate(
		ShippingController,
		"ShippingController",
		configMINIMAL_STACK_SIZE,
		NULL,
		workerTASK_PRIORITY,
		&taskTmp
	);
	taskInfo tsk3_info = { 
                        .TaskCallback = ShippingController,
                        .TaskName = "ShippingController",
                        .StackSize = configMINIMAL_STACK_SIZE,
                        .Parameters = NULL,
                        .Prio = workerTASK_PRIORITY,
                        .TaskHandler = taskTmp
        };
  TaskDoggyRegister(tsk3_info);
	vTaskStartScheduler();
    for( ; ; );
}

