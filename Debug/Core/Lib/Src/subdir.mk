################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Lib/Src/ds18b20.c \
../Core/Lib/Src/onewire.c 

OBJS += \
./Core/Lib/Src/ds18b20.o \
./Core/Lib/Src/onewire.o 

C_DEPS += \
./Core/Lib/Src/ds18b20.d \
./Core/Lib/Src/onewire.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/Src/%.o Core/Lib/Src/%.su Core/Lib/Src/%.cyclo: ../Core/Lib/Src/%.c Core/Lib/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Project/Second/second_new/Core/Lib/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Lib-2f-Src

clean-Core-2f-Lib-2f-Src:
	-$(RM) ./Core/Lib/Src/ds18b20.cyclo ./Core/Lib/Src/ds18b20.d ./Core/Lib/Src/ds18b20.o ./Core/Lib/Src/ds18b20.su ./Core/Lib/Src/onewire.cyclo ./Core/Lib/Src/onewire.d ./Core/Lib/Src/onewire.o ./Core/Lib/Src/onewire.su

.PHONY: clean-Core-2f-Lib-2f-Src

