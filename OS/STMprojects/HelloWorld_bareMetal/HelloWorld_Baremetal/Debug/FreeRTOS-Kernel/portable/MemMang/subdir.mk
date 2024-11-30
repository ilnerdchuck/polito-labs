################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS-Kernel/portable/MemMang/heap_4.c 

OBJS += \
./FreeRTOS-Kernel/portable/MemMang/heap_4.o 

C_DEPS += \
./FreeRTOS-Kernel/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS-Kernel/portable/MemMang/%.o FreeRTOS-Kernel/portable/MemMang/%.su FreeRTOS-Kernel/portable/MemMang/%.cyclo: ../FreeRTOS-Kernel/portable/MemMang/%.c FreeRTOS-Kernel/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"/home/chuck/uni/Torino/Laboratori/OS/STMprojects/HelloWorld_bareMetal/HelloWorld_Baremetal/FreeRTOS-Kernel/include" -I"/home/chuck/uni/Torino/Laboratori/OS/STMprojects/HelloWorld_bareMetal/HelloWorld_Baremetal/FreeRTOS-Kernel/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FreeRTOS-2d-Kernel-2f-portable-2f-MemMang

clean-FreeRTOS-2d-Kernel-2f-portable-2f-MemMang:
	-$(RM) ./FreeRTOS-Kernel/portable/MemMang/heap_4.cyclo ./FreeRTOS-Kernel/portable/MemMang/heap_4.d ./FreeRTOS-Kernel/portable/MemMang/heap_4.o ./FreeRTOS-Kernel/portable/MemMang/heap_4.su

.PHONY: clean-FreeRTOS-2d-Kernel-2f-portable-2f-MemMang

