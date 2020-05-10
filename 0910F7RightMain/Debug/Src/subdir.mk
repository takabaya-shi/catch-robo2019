################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/auto_pass.c \
../Src/autoctrl.c \
../Src/brushless.c \
../Src/controller.c \
../Src/encoder.c \
../Src/main.c \
../Src/microswitch.c \
../Src/motor.c \
../Src/robotstate.c \
../Src/servomotor.c \
../Src/stm32f7xx_hal_msp.c \
../Src/stm32f7xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f7xx.c 

OBJS += \
./Src/auto_pass.o \
./Src/autoctrl.o \
./Src/brushless.o \
./Src/controller.o \
./Src/encoder.o \
./Src/main.o \
./Src/microswitch.o \
./Src/motor.o \
./Src/robotstate.o \
./Src/servomotor.o \
./Src/stm32f7xx_hal_msp.o \
./Src/stm32f7xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f7xx.o 

C_DEPS += \
./Src/auto_pass.d \
./Src/autoctrl.d \
./Src/brushless.d \
./Src/controller.d \
./Src/encoder.d \
./Src/main.d \
./Src/microswitch.d \
./Src/motor.d \
./Src/robotstate.d \
./Src/servomotor.d \
./Src/stm32f7xx_hal_msp.d \
./Src/stm32f7xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F767xx -I"C:/Users/tomok/Documents/catch_robo/0910F7RightMain/Inc" -I"C:/Users/tomok/Documents/catch_robo/0910F7RightMain/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/tomok/Documents/catch_robo/0910F7RightMain/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"C:/Users/tomok/Documents/catch_robo/0910F7RightMain/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/tomok/Documents/catch_robo/0910F7RightMain/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


