################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c \
/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c \
/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/list.c \
/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c \
/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/queue.c \
/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/timers.c 

OBJS += \
./Middlewares/FreeRTOS/cmsis_os.o \
./Middlewares/FreeRTOS/croutine.o \
./Middlewares/FreeRTOS/event_groups.o \
./Middlewares/FreeRTOS/heap_4.o \
./Middlewares/FreeRTOS/list.o \
./Middlewares/FreeRTOS/port.o \
./Middlewares/FreeRTOS/queue.o \
./Middlewares/FreeRTOS/tasks.o \
./Middlewares/FreeRTOS/timers.o 

C_DEPS += \
./Middlewares/FreeRTOS/cmsis_os.d \
./Middlewares/FreeRTOS/croutine.d \
./Middlewares/FreeRTOS/event_groups.d \
./Middlewares/FreeRTOS/heap_4.d \
./Middlewares/FreeRTOS/list.d \
./Middlewares/FreeRTOS/port.d \
./Middlewares/FreeRTOS/queue.d \
./Middlewares/FreeRTOS/tasks.d \
./Middlewares/FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FreeRTOS/cmsis_os.o: /Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DAIRBRAKE_BOARD -DUSE_FULL_LL_DRIVER '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F446xx -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/flight-sw/template/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FatFs/src" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Inc"  -Og -g3 -pedantic -Wall -Wextra -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/croutine.o: /Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/croutine.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DAIRBRAKE_BOARD -DUSE_FULL_LL_DRIVER '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F446xx -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/flight-sw/template/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FatFs/src" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Inc"  -Og -g3 -pedantic -Wall -Wextra -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/event_groups.o: /Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DAIRBRAKE_BOARD -DUSE_FULL_LL_DRIVER '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F446xx -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/flight-sw/template/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FatFs/src" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Inc"  -Og -g3 -pedantic -Wall -Wextra -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/heap_4.o: /Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DAIRBRAKE_BOARD -DUSE_FULL_LL_DRIVER '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F446xx -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/flight-sw/template/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FatFs/src" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Inc"  -Og -g3 -pedantic -Wall -Wextra -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/list.o: /Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/list.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DAIRBRAKE_BOARD -DUSE_FULL_LL_DRIVER '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F446xx -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/flight-sw/template/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FatFs/src" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Inc"  -Og -g3 -pedantic -Wall -Wextra -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/port.o: /Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DAIRBRAKE_BOARD -DUSE_FULL_LL_DRIVER '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F446xx -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/flight-sw/template/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FatFs/src" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Inc"  -Og -g3 -pedantic -Wall -Wextra -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/queue.o: /Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/queue.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DAIRBRAKE_BOARD -DUSE_FULL_LL_DRIVER '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F446xx -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/flight-sw/template/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FatFs/src" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Inc"  -Og -g3 -pedantic -Wall -Wextra -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/tasks.o: /Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DAIRBRAKE_BOARD -DUSE_FULL_LL_DRIVER '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F446xx -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/flight-sw/template/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FatFs/src" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Inc"  -Og -g3 -pedantic -Wall -Wextra -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/timers.o: /Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/timers.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DAIRBRAKE_BOARD -DUSE_FULL_LL_DRIVER '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F446xx -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/flight-sw/template/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FatFs/src" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Inc"  -Og -g3 -pedantic -Wall -Wextra -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


