# Exercies 1 - FreeRTOS and Interrupt

Create a FreeRTOS project based on the mps2-an385 emulated board in QEMU and the basic skeleton provided in this folder.

The base project provides hardware support based on the CMSIS Board Support Package. It implements the printf function and initializes the hardware timer 0 available on the board to issue periodic interrupts.

The system must perform the following actions:
* Execute a periodic task with a period equal to 20ms. Every time the task is activated, it performs the multiplication of two 3x3 matrices.
The two matrices can be initialized with fixed values. The role of this task is to emulate a time-intensive task.
* Define the interrupt handler for TIMER0.
* The interrupt must be served using the deferred interrupt technique. The interrupt service routine must print a message indicating how many interrupts have been served.

Refer to the FreeRTOS documentation here: [https://www.freertos.org/Documentation/00-Overview
]()







