################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/tests/lv_test_fonts/font_1.c \
../lvgl/tests/lv_test_fonts/font_2.c \
../lvgl/tests/lv_test_fonts/font_3.c 

OBJS += \
./lvgl/tests/lv_test_fonts/font_1.o \
./lvgl/tests/lv_test_fonts/font_2.o \
./lvgl/tests/lv_test_fonts/font_3.o 

C_DEPS += \
./lvgl/tests/lv_test_fonts/font_1.d \
./lvgl/tests/lv_test_fonts/font_2.d \
./lvgl/tests/lv_test_fonts/font_3.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/tests/lv_test_fonts/%.o lvgl/tests/lv_test_fonts/%.su lvgl/tests/lv_test_fonts/%.cyclo: ../lvgl/tests/lv_test_fonts/%.c lvgl/tests/lv_test_fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"D:/ClassRoom/ComputerNetworking/Final/F407_LVGL/ILI9341" -I"D:/ClassRoom/ComputerNetworking/Final/F407_LVGL/XPT2064" -I"D:/ClassRoom/ComputerNetworking/Final/F407_LVGL/lvgl" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-tests-2f-lv_test_fonts

clean-lvgl-2f-tests-2f-lv_test_fonts:
	-$(RM) ./lvgl/tests/lv_test_fonts/font_1.cyclo ./lvgl/tests/lv_test_fonts/font_1.d ./lvgl/tests/lv_test_fonts/font_1.o ./lvgl/tests/lv_test_fonts/font_1.su ./lvgl/tests/lv_test_fonts/font_2.cyclo ./lvgl/tests/lv_test_fonts/font_2.d ./lvgl/tests/lv_test_fonts/font_2.o ./lvgl/tests/lv_test_fonts/font_2.su ./lvgl/tests/lv_test_fonts/font_3.cyclo ./lvgl/tests/lv_test_fonts/font_3.d ./lvgl/tests/lv_test_fonts/font_3.o ./lvgl/tests/lv_test_fonts/font_3.su

.PHONY: clean-lvgl-2f-tests-2f-lv_test_fonts

