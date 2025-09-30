################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/extra/widgets/span/lv_span.c 

OBJS += \
./lvgl/src/extra/widgets/span/lv_span.o 

C_DEPS += \
./lvgl/src/extra/widgets/span/lv_span.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/extra/widgets/span/%.o lvgl/src/extra/widgets/span/%.su lvgl/src/extra/widgets/span/%.cyclo: ../lvgl/src/extra/widgets/span/%.c lvgl/src/extra/widgets/span/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"D:/ClassRoom/ComputerNetworking/Final/F407_LVGL/ILI9341" -I"D:/ClassRoom/ComputerNetworking/Final/F407_LVGL/XPT2064" -I"D:/ClassRoom/ComputerNetworking/Final/F407_LVGL/lvgl" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-extra-2f-widgets-2f-span

clean-lvgl-2f-src-2f-extra-2f-widgets-2f-span:
	-$(RM) ./lvgl/src/extra/widgets/span/lv_span.cyclo ./lvgl/src/extra/widgets/span/lv_span.d ./lvgl/src/extra/widgets/span/lv_span.o ./lvgl/src/extra/widgets/span/lv_span.su

.PHONY: clean-lvgl-2f-src-2f-extra-2f-widgets-2f-span

