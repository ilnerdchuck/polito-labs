;            Computer Architectures - 02LSEOV 02LSEOQ            ;
; author: 		Paolo BERNARDI - Politecnico di Torino           ;
; creation: 	11 November 2018								 ;
; last update:  1 Dicember 2020								 	 ;
; functionalities:												 ;
;		nothing but bringing to the reset handler				 ;

; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
				SPACE   Stack_Size/2
Stack_Mem       SPACE   Stack_Size/2
__initial_sp		




; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
												; 0x10000200
__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     WDT_IRQHandler            ; 16: Watchdog Timer
                DCD     TIMER0_IRQHandler         ; 17: Timer0
                DCD     TIMER1_IRQHandler         ; 18: Timer1
                DCD     TIMER2_IRQHandler         ; 19: Timer2
                DCD     TIMER3_IRQHandler         ; 20: Timer3
                DCD     UART0_IRQHandler          ; 21: UART0
                DCD     UART1_IRQHandler          ; 22: UART1
                DCD     UART2_IRQHandler          ; 23: UART2
                DCD     UART3_IRQHandler          ; 24: UART3
                DCD     PWM1_IRQHandler           ; 25: PWM1
                DCD     I2C0_IRQHandler           ; 26: I2C0
                DCD     I2C1_IRQHandler           ; 27: I2C1
                DCD     I2C2_IRQHandler           ; 28: I2C2
                DCD     SPI_IRQHandler            ; 29: SPI
                DCD     SSP0_IRQHandler           ; 30: SSP0
                DCD     SSP1_IRQHandler           ; 31: SSP1
                DCD     PLL0_IRQHandler           ; 32: PLL0 Lock (Main PLL)
                DCD     RTC_IRQHandler            ; 33: Real Time Clock
                DCD     EINT0_IRQHandler          ; 34: External Interrupt 0
                DCD     EINT1_IRQHandler          ; 35: External Interrupt 1
                DCD     EINT2_IRQHandler          ; 36: External Interrupt 2
                DCD     EINT3_IRQHandler          ; 37: External Interrupt 3
                DCD     ADC_IRQHandler            ; 38: A/D Converter
                DCD     BOD_IRQHandler            ; 39: Brown-Out Detect
                DCD     USB_IRQHandler            ; 40: USB
                DCD     CAN_IRQHandler            ; 41: CAN
                DCD     DMA_IRQHandler            ; 42: General Purpose DMA
                DCD     I2S_IRQHandler            ; 43: I2S
                DCD     ENET_IRQHandler           ; 44: Ethernet
                DCD     RIT_IRQHandler            ; 45: Repetitive Interrupt Timer
                DCD     MCPWM_IRQHandler          ; 46: Motor Control PWM
                DCD     QEI_IRQHandler            ; 47: Quadrature Encoder Interface
                DCD     PLL1_IRQHandler           ; 48: PLL1 Lock (USB PLL)
                DCD     USBActivity_IRQHandler    ; 49: USB Activity interrupt to wakeup
                DCD     CANActivity_IRQHandler    ; 50: CAN Activity interrupt to wakeup


                IF      :LNOT::DEF:NO_CRP
                AREA    |.ARM.__at_0x02FC|, CODE, READONLY
CRP_Key         DCD     0xFFFFFFFF
                ENDIF


				AREA 	matrixData, DATA, READONLY
				EXPORT Matrix_Coordinates
				EXPORT ROWS
				EXPORT COLUMNS
				
				ALIGN 2
				
Matrix_Coordinates 	
				DCD -5, 5,  -4, 5,  -3, 5,  -2, 5,  -1, 5,   0, 5,   1, 5,   2, 5,   3, 5,   4, 5,   5, 5
				DCD -5, 4,  -4, 4,  -3, 4,  -2, 4,  -1, 4,   0, 4,   1, 4,   2, 4,   3, 4,   4, 4,   5, 4
				DCD -5, 3,  -4, 3,  -3, 3,  -2, 3,  -1, 3,   0, 3,   1, 3,   2, 3,   3, 3,   4, 3,   5, 3
				DCD -5, 2,  -4, 2,  -3, 2,  -2, 2,  -1, 2,   0, 2,   1, 2,   2, 2,   3, 2,   4, 2,   5, 2
				DCD -5, 1,  -4, 1,  -3, 1,  -2, 1,  -1, 1,   0, 1,   1, 1,   2, 1,   3, 1,   4, 1,   5, 1
				DCD -5, 0,  -4, 0,  -3, 0,  -2, 0,  -1, 0,   0, 0,   1, 0,   2, 0,   3, 0,   4, 0,   5, 0
				DCD -5,-1,  -4,-1,  -3,-1,  -2,-1,  -1,-1,   0,-1,   1,-1,   2,-1,   3,-1,   4,-1,   5,-1
				DCD -5,-2,  -4,-2,  -3,-2,  -2,-2,  -1,-2,   0,-2,   1,-2,   2,-2,   3,-2,   4,-2,   5,-2
				DCD -5,-3,  -4,-3,  -3,-3,  -2,-3,  -1,-3,   0,-3,   1,-3,   2,-3,   3,-3,   4,-3,   5,-3
				DCD -5,-4,  -4,-4,  -3,-4,  -2,-4,  -1,-4,   0,-4,   1,-4,   2,-4,   3,-4,   4,-4,   5,-4
				DCD -5,-5,  -4,-5,  -3,-5,  -2,-5,  -1,-5,   0,-5,   1,-5,   2,-5,   3,-5,   4,-5,   5,-5
ROWS 			DCB 11
COLUMNS 		DCB 22


                AREA    |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]                                            
                                            
				IMPORT __main
				MRS R1, CONTROL	
				ORR R1, R1, #0x1
				MSR CONTROL, R1
				
				LDR 	R0, =__main
				LDR 	R1, =Heap_Mem
				BLX		R0
				
				B      	.
				ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
				
				STMFD SP!, {R0-R12, LR}
				
				;check the less significant byte in the LR to understand which was the SP used before the SVC
				
				;LR->0100 only bit 2 is to check 
				;D=  1101 -> PSP
				;9=  1001 -> MSP
				;1=  0001 -> MSP
				
				TST LR, #4
				
				ITE EQ
				MRSEQ R1, MSP
				MRSNE R1, PSP
				
				;Read program counter from the stack
				LDREQ R0, [R1, #20*4]
				LDRNE R0, [R1, #6*4]
			
				
				;Read SVC number
				LDRB R0, [R0,#-2]	;0x000000D8
				
				; your code here
				; R0 stores the value in 8 bit message to be encoded
				
				MOV R10, #0		; store encoded message
				MOV R11, #0		; counter
encode_loop		CMP R11, #8
				BEQ exit_encode_loop
				
				MOV R2, #1
				LSL R2, R11
				AND R3, R2, R0		; get i-th bit
				LSR R3, R11			; first bit of R3 is i-th bit
				
				; Now i take the counter and multiply it by 3
				RSB R4, R11, R11, LSL #2
				ADD R5, R4, #1
				ADD R6, R4, #2
				
				LSL R7, R3, R4
				LSL R8, R3, R5
				LSL R9, R3, R6
				
				ADD R7, R7, R8
				ADD R7, R7, R9		; R7 has now the bit repeted three times in the right position
				
				ORR R10, R10, R7
				
				ADD R11, R11, #1
				B encode_loop
exit_encode_loop
				NOP
				; Return the encoded message using the stack.
				STR R10, [R1]		; In this way I overwrite the value of R0 in the stack, but it is ok
				;PUSH {R10}
				; Before leaving I need to set the user mode unpriviliged
				MRS R1, CONTROL	
				ORR R1, R1, #0x1
				MSR CONTROL, R1
				LDMFD SP!, {R0-R12, LR}
				STR R0, [R1]
				BX LR
				
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  TIMER0_IRQHandler         [WEAK]
                EXPORT  TIMER1_IRQHandler         [WEAK]
                EXPORT  TIMER2_IRQHandler         [WEAK]
                EXPORT  TIMER3_IRQHandler         [WEAK]
                EXPORT  UART0_IRQHandler          [WEAK]
                EXPORT  UART1_IRQHandler          [WEAK]
                EXPORT  UART2_IRQHandler          [WEAK]
                EXPORT  UART3_IRQHandler          [WEAK]
                EXPORT  PWM1_IRQHandler           [WEAK]
                EXPORT  I2C0_IRQHandler           [WEAK]
                EXPORT  I2C1_IRQHandler           [WEAK]
                EXPORT  I2C2_IRQHandler           [WEAK]
                EXPORT  SPI_IRQHandler            [WEAK]
                EXPORT  SSP0_IRQHandler           [WEAK]
                EXPORT  SSP1_IRQHandler           [WEAK]
                EXPORT  PLL0_IRQHandler           [WEAK]
                EXPORT  RTC_IRQHandler            [WEAK]
                EXPORT  EINT0_IRQHandler          [WEAK]
                EXPORT  EINT1_IRQHandler          [WEAK]
                EXPORT  EINT2_IRQHandler          [WEAK]
                EXPORT  EINT3_IRQHandler          [WEAK]
                EXPORT  ADC_IRQHandler            [WEAK]
                EXPORT  BOD_IRQHandler            [WEAK]
                EXPORT  USB_IRQHandler            [WEAK]
                EXPORT  CAN_IRQHandler            [WEAK]
                EXPORT  DMA_IRQHandler            [WEAK]
                EXPORT  I2S_IRQHandler            [WEAK]
                EXPORT  ENET_IRQHandler           [WEAK]
                EXPORT  RIT_IRQHandler            [WEAK]
                EXPORT  MCPWM_IRQHandler          [WEAK]
                EXPORT  QEI_IRQHandler            [WEAK]
                EXPORT  PLL1_IRQHandler           [WEAK]
                EXPORT  USBActivity_IRQHandler    [WEAK]
                EXPORT  CANActivity_IRQHandler    [WEAK]

WDT_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
PWM1_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
I2C2_IRQHandler
SPI_IRQHandler
SSP0_IRQHandler
SSP1_IRQHandler
PLL0_IRQHandler
RTC_IRQHandler
EINT0_IRQHandler
EINT1_IRQHandler
EINT2_IRQHandler
EINT3_IRQHandler
ADC_IRQHandler
BOD_IRQHandler
USB_IRQHandler
CAN_IRQHandler
DMA_IRQHandler
I2S_IRQHandler
ENET_IRQHandler
RIT_IRQHandler
MCPWM_IRQHandler
QEI_IRQHandler
PLL1_IRQHandler
USBActivity_IRQHandler
CANActivity_IRQHandler

                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END

