################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/bsp_driver_sd.c \
../Src/can.c \
../Src/dma.c \
../Src/fatfs.c \
../Src/freertos.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/main.c \
../Src/quadspi.c \
../Src/sd_diskio.c \
../Src/sdio.c \
../Src/spi.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_hal_timebase_tim.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c \
../Src/tim.c \
../Src/usart.c 

OBJS += \
./Src/adc.o \
./Src/bsp_driver_sd.o \
./Src/can.o \
./Src/dma.o \
./Src/fatfs.o \
./Src/freertos.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/main.o \
./Src/quadspi.o \
./Src/sd_diskio.o \
./Src/sdio.o \
./Src/spi.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_hal_timebase_tim.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o \
./Src/tim.o \
./Src/usart.o 

C_DEPS += \
./Src/adc.d \
./Src/bsp_driver_sd.d \
./Src/can.d \
./Src/dma.d \
./Src/fatfs.d \
./Src/freertos.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/main.d \
./Src/quadspi.d \
./Src/sd_diskio.d \
./Src/sdio.d \
./Src/spi.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_hal_timebase_tim.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d \
./Src/tim.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DAIRBRAKE_BOARD -DUSE_FULL_LL_DRIVER '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F446xx -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/flight-sw/template/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FatFs/src" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/STM32Cube_FW_F4_V1.23.0/Drivers/CMSIS/Include" -I"/Users/Alberic/Desktop/EPFL/team_rocket/SW/Eiger/library/host-board/Inc"  -Og -g3 -pedantic -Wall -Wextra -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


