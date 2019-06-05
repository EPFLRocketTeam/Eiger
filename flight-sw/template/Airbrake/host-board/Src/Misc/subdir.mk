################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Src/Misc/datagram_builder.cpp \
/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Src/Misc/telemetry_handling.cpp 

OBJS += \
./host-board/Src/Misc/datagram_builder.o \
./host-board/Src/Misc/telemetry_handling.o 

CPP_DEPS += \
./host-board/Src/Misc/datagram_builder.d \
./host-board/Src/Misc/telemetry_handling.d 


# Each subdirectory must supply rules for building sources it contributes
host-board/Src/Misc/datagram_builder.o: /Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Src/Misc/datagram_builder.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DAIRBRAKE_BOARD -DUSE_FULL_LL_DRIVER '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F446xx -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/flight-sw/template/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FatFs/src" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Inc"  -Og -g3 -pedantic -Wall -Wextra -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

host-board/Src/Misc/telemetry_handling.o: /Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Src/Misc/telemetry_handling.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DAIRBRAKE_BOARD -DUSE_FULL_LL_DRIVER '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F446xx -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/flight-sw/template/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FatFs/src" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Inc"  -Og -g3 -pedantic -Wall -Wextra -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


