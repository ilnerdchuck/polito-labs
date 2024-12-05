#include "u_task.h"

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

  UART_init();
  
	xTaskCreate(
		initSystem,
		"initSystem",
		configMINIMAL_STACK_SIZE,
		NULL,
		mainTASK_PRIORITY,
		NULL
	);

	xTaskCreate(
		ConveyorSystem,
		"Conveyor",
		configMINIMAL_STACK_SIZE,
		NULL,
		mediumTASK_PRIORITY,
		NULL
	);


	xTaskCreate(
		InspectionSystem,
		"Inspection",
		configMINIMAL_STACK_SIZE,
		NULL,
		highTASK_PRIORITY,
		NULL
	);

	xTaskCreate(
		Watchdog,
		"Watchdog",
		configMINIMAL_STACK_SIZE,
		NULL,
		highTASK_PRIORITY,
		NULL
	);

	xTaskCreate(
		LogSystem,
		"Logger",
		configMINIMAL_STACK_SIZE,
		NULL,
		lowTASK_PRIORITY,
		NULL
	);

	vTaskStartScheduler();
    for( ; ; );
}
