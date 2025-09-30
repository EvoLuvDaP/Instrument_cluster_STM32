################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/examples/widgets/imgbtn/lv_example_imgbtn_1.c 

OBJS += \
./lvgl/examples/widgets/imgbtn/lv_example_imgbtn_1.o 

C_DEPS += \
./lvgl/examples/widgets/imgbtn/lv_example_imgbtn_1.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/examples/widgets/imgbtn/%.o lvgl/examples/widgets/imgbtn/%.su lvgl/examples/widgets/imgbtn/%.cyclo: ../lvgl/examples/widgets/imgbtn/%.c lvgl/examples/widgets/imgbtn/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"D:/ClassRoom/ComputerNetworking/Final/F407_LVGL/ILI9341" -I"D:/ClassRoom/ComputerNetworking/Final/F407_LVGL/XPT2064" -I"D:/ClassRoom/ComputerNetworking/Final/F407_LVGL/lvgl" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-examples-2f-widgets-2f-imgbtn

clean-lvgl-2f-examples-2f-widgets-2f-imgbtn:
	-$(RM) ./lvgl/examples/widgets/imgbtn/lv_example_imgbtn_1.cyclo ./lvgl/examples/widgets/imgbtn/lv_example_imgbtn_1.d ./lvgl/examples/widgets/imgbtn/lv_example_imgbtn_1.o ./lvgl/examples/widgets/imgbtn/lv_example_imgbtn_1.su

.PHONY: clean-lvgl-2f-examples-2f-widgets-2f-imgbtn

