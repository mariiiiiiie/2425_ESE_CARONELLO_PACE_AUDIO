################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/components/MCP23S17.c 

OBJS += \
./Core/Src/components/MCP23S17.o 

C_DEPS += \
./Core/Src/components/MCP23S17.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/components/%.o Core/Src/components/%.su Core/Src/components/%.cyclo: ../Core/Src/components/%.c Core/Src/components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"/Users/romingo/Desktop/ENSEA/3A/TP/2425_ESE_AutoRadio_CARONELLO_PACE/shell" -I"/Users/romingo/Desktop/ENSEA/3A/TP/2425_ESE_AutoRadio_CARONELLO_PACE/callBack" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-components

clean-Core-2f-Src-2f-components:
	-$(RM) ./Core/Src/components/MCP23S17.cyclo ./Core/Src/components/MCP23S17.d ./Core/Src/components/MCP23S17.o ./Core/Src/components/MCP23S17.su

.PHONY: clean-Core-2f-Src-2f-components

