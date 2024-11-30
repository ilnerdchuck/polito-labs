# Exercise 4 - FreeRTOS tasks

Create a FreeRTOS project based on the template available here: [https://baltig.polito.it/teaching-material/exercises-caos-and-os/FreeRTOSsampleapp](https://baltig.polito.it/teaching-material/exercises-caos-and-os/FreeRTOSsampleapp).

```
├── App
│   ├── FreeRTOSConfig.h
│   ├── Makefile
│   ├── main.c
│   ├── mps2_m3.ld
│   ├── startup.c
│   ├── uart.c
│   └── uart.h
└── README.md
```

The project should create the following tasks:

* `startup` it is the first task running with the highest priority in the system. Let's name this priority `MAX_PRIRITY`. This task create three additional tasks named `task1`, `task2`, `task3`. Finally the task ends.
* `task1` and `task2` have both priority equal to `MAX_PRIRITY-2`. They work together to fill a global array of 20 elements. `task1` fills the even elements with consecutives powers of 2. `task2` fills the odd elements with consecutives powers of 3. When they are complete they end.
* `task3` must wait the end of `task1` and `task2` and print the array on screen. 

**Syncronyzation should be obtained without the use of semaphores or other syncronization primitives**

**When you submit your exam only the App folder must be included in the ZIP. Please remove the .git hidden folder**

Refer to the FreeRTOS documentation here: [https://www.freertos.org/Documentation/00-Overview](https://www.freertos.org/Documentation/00-Overview)
