################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/encoder.c \
../Src/main.c \
../Src/motor.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c 

OBJS += \
./Src/encoder.o \
./Src/main.o \
./Src/motor.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o 

C_DEPS += \
./Src/encoder.d \
./Src/main.d \
./Src/motor.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F446xx -I"C:/Users/tomok/Documents/catch_robo/Encoder_test/Inc" -I"C:/Users/tomok/Documents/catch_robo/Encoder_test/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/tomok/Documents/catch_robo/Encoder_test/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/tomok/Documents/catch_robo/Encoder_test/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/tomok/Documents/catch_robo/Encoder_test/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


