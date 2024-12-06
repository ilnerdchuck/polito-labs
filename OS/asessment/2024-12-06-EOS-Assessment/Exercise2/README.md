# Exercise 2- FreeRTOS and Priority Inversion

Create a FreeRTOS project based on the mps2-an385 emulated board in QEMU and the basic skeleton provided in this folder.

The base project provides hardware support based on the CMSIS Board Support Package. It implements the printf function and initializes the hardware timer 0 available on the board to issue periodic interrupts.

The project must create two periodic tasks (TASK A, TASKB) with different priorities. TaskA is the task with higher priority, and TaskB has lower priority. Task A and Task B share a common resource (e.g., a variable). 

Can you organize to generate a priority inversion situation? It is not important what the task performs. You can execute dummy operations as far as priority inversion is generated.

Refer to the FreeRTOS documentation here: [https://www.freertos.org/Documentation/00-Overview
]()








