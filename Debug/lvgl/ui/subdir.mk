################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/ui/images.c \
../lvgl/ui/screens.c \
../lvgl/ui/styles.c \
../lvgl/ui/ui.c \
../lvgl/ui/ui_image_airbag.c \
../lvgl/ui/ui_image_autolight.c \
../lvgl/ui/ui_image_battery.c \
../lvgl/ui/ui_image_bg.c \
../lvgl/ui/ui_image_brake.c \
../lvgl/ui/ui_image_car_fuel.c \
../lvgl/ui/ui_image_hazard_light.c \
../lvgl/ui/ui_image_headlight.c \
../lvgl/ui/ui_image_highbeam.c \
../lvgl/ui/ui_image_lowbeam.c \
../lvgl/ui/ui_image_position_light.c \
../lvgl/ui/ui_image_turn_sign.c \
../lvgl/ui/ui_image_turn_sign_1.c 

OBJS += \
./lvgl/ui/images.o \
./lvgl/ui/screens.o \
./lvgl/ui/styles.o \
./lvgl/ui/ui.o \
./lvgl/ui/ui_image_airbag.o \
./lvgl/ui/ui_image_autolight.o \
./lvgl/ui/ui_image_battery.o \
./lvgl/ui/ui_image_bg.o \
./lvgl/ui/ui_image_brake.o \
./lvgl/ui/ui_image_car_fuel.o \
./lvgl/ui/ui_image_hazard_light.o \
./lvgl/ui/ui_image_headlight.o \
./lvgl/ui/ui_image_highbeam.o \
./lvgl/ui/ui_image_lowbeam.o \
./lvgl/ui/ui_image_position_light.o \
./lvgl/ui/ui_image_turn_sign.o \
./lvgl/ui/ui_image_turn_sign_1.o 

C_DEPS += \
./lvgl/ui/images.d \
./lvgl/ui/screens.d \
./lvgl/ui/styles.d \
./lvgl/ui/ui.d \
./lvgl/ui/ui_image_airbag.d \
./lvgl/ui/ui_image_autolight.d \
./lvgl/ui/ui_image_battery.d \
./lvgl/ui/ui_image_bg.d \
./lvgl/ui/ui_image_brake.d \
./lvgl/ui/ui_image_car_fuel.d \
./lvgl/ui/ui_image_hazard_light.d \
./lvgl/ui/ui_image_headlight.d \
./lvgl/ui/ui_image_highbeam.d \
./lvgl/ui/ui_image_lowbeam.d \
./lvgl/ui/ui_image_position_light.d \
./lvgl/ui/ui_image_turn_sign.d \
./lvgl/ui/ui_image_turn_sign_1.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/ui/%.o lvgl/ui/%.su lvgl/ui/%.cyclo: ../lvgl/ui/%.c lvgl/ui/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"D:/ClassRoom/ComputerNetworking/Final/F407_LVGL/ILI9341" -I"D:/ClassRoom/ComputerNetworking/Final/F407_LVGL/XPT2064" -I"D:/ClassRoom/ComputerNetworking/Final/F407_LVGL/lvgl" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-ui

clean-lvgl-2f-ui:
	-$(RM) ./lvgl/ui/images.cyclo ./lvgl/ui/images.d ./lvgl/ui/images.o ./lvgl/ui/images.su ./lvgl/ui/screens.cyclo ./lvgl/ui/screens.d ./lvgl/ui/screens.o ./lvgl/ui/screens.su ./lvgl/ui/styles.cyclo ./lvgl/ui/styles.d ./lvgl/ui/styles.o ./lvgl/ui/styles.su ./lvgl/ui/ui.cyclo ./lvgl/ui/ui.d ./lvgl/ui/ui.o ./lvgl/ui/ui.su ./lvgl/ui/ui_image_airbag.cyclo ./lvgl/ui/ui_image_airbag.d ./lvgl/ui/ui_image_airbag.o ./lvgl/ui/ui_image_airbag.su ./lvgl/ui/ui_image_autolight.cyclo ./lvgl/ui/ui_image_autolight.d ./lvgl/ui/ui_image_autolight.o ./lvgl/ui/ui_image_autolight.su ./lvgl/ui/ui_image_battery.cyclo ./lvgl/ui/ui_image_battery.d ./lvgl/ui/ui_image_battery.o ./lvgl/ui/ui_image_battery.su ./lvgl/ui/ui_image_bg.cyclo ./lvgl/ui/ui_image_bg.d ./lvgl/ui/ui_image_bg.o ./lvgl/ui/ui_image_bg.su ./lvgl/ui/ui_image_brake.cyclo ./lvgl/ui/ui_image_brake.d ./lvgl/ui/ui_image_brake.o ./lvgl/ui/ui_image_brake.su ./lvgl/ui/ui_image_car_fuel.cyclo ./lvgl/ui/ui_image_car_fuel.d ./lvgl/ui/ui_image_car_fuel.o ./lvgl/ui/ui_image_car_fuel.su ./lvgl/ui/ui_image_hazard_light.cyclo ./lvgl/ui/ui_image_hazard_light.d ./lvgl/ui/ui_image_hazard_light.o ./lvgl/ui/ui_image_hazard_light.su ./lvgl/ui/ui_image_headlight.cyclo ./lvgl/ui/ui_image_headlight.d ./lvgl/ui/ui_image_headlight.o ./lvgl/ui/ui_image_headlight.su ./lvgl/ui/ui_image_highbeam.cyclo ./lvgl/ui/ui_image_highbeam.d ./lvgl/ui/ui_image_highbeam.o ./lvgl/ui/ui_image_highbeam.su ./lvgl/ui/ui_image_lowbeam.cyclo ./lvgl/ui/ui_image_lowbeam.d ./lvgl/ui/ui_image_lowbeam.o ./lvgl/ui/ui_image_lowbeam.su ./lvgl/ui/ui_image_position_light.cyclo ./lvgl/ui/ui_image_position_light.d ./lvgl/ui/ui_image_position_light.o ./lvgl/ui/ui_image_position_light.su ./lvgl/ui/ui_image_turn_sign.cyclo ./lvgl/ui/ui_image_turn_sign.d ./lvgl/ui/ui_image_turn_sign.o ./lvgl/ui/ui_image_turn_sign.su ./lvgl/ui/ui_image_turn_sign_1.cyclo ./lvgl/ui/ui_image_turn_sign_1.d ./lvgl/ui/ui_image_turn_sign_1.o ./lvgl/ui/ui_image_turn_sign_1.su

.PHONY: clean-lvgl-2f-ui

