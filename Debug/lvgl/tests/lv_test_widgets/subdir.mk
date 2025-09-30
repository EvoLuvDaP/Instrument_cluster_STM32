################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/tests/lv_test_widgets/lv_test_label.c 

OBJS += \
./lvgl/tests/lv_test_widgets/lv_test_label.o 

C_DEPS += \
./lvgl/tests/lv_test_widgets/lv_test_label.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/tests/lv_test_widgets/%.o lvgl/tests/lv_test_widgets/%.su lvgl/tests/lv_test_widgets/%.cyclo: ../lvgl/tests/lv_test_widgets/%.c lvgl/tests/lv_test_widgets/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"D:/ClassRoom/ComputerNetworking/Final/F407_LVGL/ILI9341" -I"D:/ClassRoom/ComputerNetworking/Final/F407_LVGL/XPT2064" -I"D:/ClassRoom/ComputerNetworking/Final/F407_LVGL/lvgl" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-tests-2f-lv_test_widgets

clean-lvgl-2f-tests-2f-lv_test_widgets:
	-$(RM) ./lvgl/tests/lv_test_widgets/lv_test_label.cyclo ./lvgl/tests/lv_test_widgets/lv_test_label.d ./lvgl/tests/lv_test_widgets/lv_test_label.o ./lvgl/tests/lv_test_widgets/lv_test_label.su

.PHONY: clean-lvgl-2f-tests-2f-lv_test_widgets

