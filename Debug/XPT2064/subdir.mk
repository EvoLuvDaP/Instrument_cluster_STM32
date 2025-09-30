################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../XPT2064/XPT2064.c \
../XPT2064/lv_drv.c 

OBJS += \
./XPT2064/XPT2064.o \
./XPT2064/lv_drv.o 

C_DEPS += \
./XPT2064/XPT2064.d \
./XPT2064/lv_drv.d 


# Each subdirectory must supply rules for building sources it contributes
XPT2064/%.o XPT2064/%.su XPT2064/%.cyclo: ../XPT2064/%.c XPT2064/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"D:/ClassRoom/ComputerNetworking/Final/F407_LVGL/ILI9341" -I"D:/ClassRoom/ComputerNetworking/Final/F407_LVGL/XPT2064" -I"D:/ClassRoom/ComputerNetworking/Final/F407_LVGL/lvgl" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-XPT2064

clean-XPT2064:
	-$(RM) ./XPT2064/XPT2064.cyclo ./XPT2064/XPT2064.d ./XPT2064/XPT2064.o ./XPT2064/XPT2064.su ./XPT2064/lv_drv.cyclo ./XPT2064/lv_drv.d ./XPT2064/lv_drv.o ./XPT2064/lv_drv.su

.PHONY: clean-XPT2064

