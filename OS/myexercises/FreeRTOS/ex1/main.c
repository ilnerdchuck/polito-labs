#include "u_task.h"
#include "uart.h"

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

  UART_init();
	BaseType_t _err = xTaskCreate(
		InventoryPicker,
		"InventoryPicker",
		configMINIMAL_STACK_SIZE,
		NULL,
		mainTASK_PRIORITY,
		NULL
	);


	_err = xTaskCreate(
		PackingStation,
		"PackingStation",
		configMINIMAL_STACK_SIZE,
		NULL,
		mainTASK_PRIORITY,
		NULL
	);
	_err = xTaskCreate(
		ShippingController,
		"ShippingController",
		configMINIMAL_STACK_SIZE,
		NULL,
		mainTASK_PRIORITY,
		NULL
	);
	// BaseType_t xTaskReturn = xTaskCreate(
	// 	LoggerSystem,
	// 	"LoggerSystem",
	// 	configMINIMAL_STACK_SIZE,
	// 	NULL,
	// 	logTASK_PRIORITY,
	// 	NULL
	// );
  // // Error handling
  // configASSERT(xTaskReturn == pdPASS);

	vTaskStartScheduler();
    for( ; ; );
}

