################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/autoctrl.c 

OBJS += \
./Drivers/autoctrl.o 

C_DEPS += \
./Drivers/autoctrl.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/%.o: ../Drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F446xx -I"C:/Users/tomok/Documents/catch_robo/Encoder_test/Inc" -I"C:/Users/tomok/Documents/catch_robo/Encoder_test/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/tomok/Documents/catch_robo/Encoder_test/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/tomok/Documents/catch_robo/Encoder_test/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/tomok/Documents/catch_robo/Encoder_test/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


