################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Src/CAN_communication.c \
/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Src/Status_panel.c \
/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Src/led.c 

OBJS += \
./host-board/Src/CAN_communication.o \
./host-board/Src/Status_panel.o \
./host-board/Src/led.o 

C_DEPS += \
./host-board/Src/CAN_communication.d \
./host-board/Src/Status_panel.d \
./host-board/Src/led.d 


# Each subdirectory must supply rules for building sources it contributes
host-board/Src/CAN_communication.o: /Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Src/CAN_communication.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DAIRBRAKE_BOARD -DUSE_FULL_LL_DRIVER '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F446xx -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/flight-sw/template/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FatFs/src" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Inc"  -Og -g3 -pedantic -Wall -Wextra -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

host-board/Src/Status_panel.o: /Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Src/Status_panel.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DAIRBRAKE_BOARD -DUSE_FULL_LL_DRIVER '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F446xx -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/flight-sw/template/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FatFs/src" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Inc"  -Og -g3 -pedantic -Wall -Wextra -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

host-board/Src/led.o: /Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Src/led.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DAIRBRAKE_BOARD -DUSE_FULL_LL_DRIVER '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F446xx -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/flight-sw/template/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FatFs/src" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Inc"  -Og -g3 -pedantic -Wall -Wextra -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


