################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include lvgl/ui/subdir.mk
-include lvgl/tests/lv_test_widgets/subdir.mk
-include lvgl/tests/lv_test_fonts/subdir.mk
-include lvgl/tests/lv_test_core/subdir.mk
-include lvgl/tests/subdir.mk
-include lvgl/src/widgets/subdir.mk
-include lvgl/src/misc/subdir.mk
-include lvgl/src/hal/subdir.mk
-include lvgl/src/gpu/subdir.mk
-include lvgl/src/font/subdir.mk
-include lvgl/src/extra/widgets/win/subdir.mk
-include lvgl/src/extra/widgets/tileview/subdir.mk
-include lvgl/src/extra/widgets/tabview/subdir.mk
-include lvgl/src/extra/widgets/spinner/subdir.mk
-include lvgl/src/extra/widgets/spinbox/subdir.mk
-include lvgl/src/extra/widgets/span/subdir.mk
-include lvgl/src/extra/widgets/msgbox/subdir.mk
-include lvgl/src/extra/widgets/meter/subdir.mk
-include lvgl/src/extra/widgets/list/subdir.mk
-include lvgl/src/extra/widgets/led/subdir.mk
-include lvgl/src/extra/widgets/keyboard/subdir.mk
-include lvgl/src/extra/widgets/imgbtn/subdir.mk
-include lvgl/src/extra/widgets/colorwheel/subdir.mk
-include lvgl/src/extra/widgets/chart/subdir.mk
-include lvgl/src/extra/widgets/calendar/subdir.mk
-include lvgl/src/extra/widgets/animimg/subdir.mk
-include lvgl/src/extra/themes/mono/subdir.mk
-include lvgl/src/extra/themes/default/subdir.mk
-include lvgl/src/extra/themes/basic/subdir.mk
-include lvgl/src/extra/layouts/grid/subdir.mk
-include lvgl/src/extra/layouts/flex/subdir.mk
-include lvgl/src/extra/subdir.mk
-include lvgl/src/draw/subdir.mk
-include lvgl/src/core/subdir.mk
-include lvgl/examples/widgets/win/subdir.mk
-include lvgl/examples/widgets/tileview/subdir.mk
-include lvgl/examples/widgets/textarea/subdir.mk
-include lvgl/examples/widgets/tabview/subdir.mk
-include lvgl/examples/widgets/table/subdir.mk
-include lvgl/examples/widgets/switch/subdir.mk
-include lvgl/examples/widgets/spinner/subdir.mk
-include lvgl/examples/widgets/spinbox/subdir.mk
-include lvgl/examples/widgets/span/subdir.mk
-include lvgl/examples/widgets/slider/subdir.mk
-include lvgl/examples/widgets/roller/subdir.mk
-include lvgl/examples/widgets/obj/subdir.mk
-include lvgl/examples/widgets/msgbox/subdir.mk
-include lvgl/examples/widgets/meter/subdir.mk
-include lvgl/examples/widgets/list/subdir.mk
-include lvgl/examples/widgets/line/subdir.mk
-include lvgl/examples/widgets/led/subdir.mk
-include lvgl/examples/widgets/label/subdir.mk
-include lvgl/examples/widgets/keyboard/subdir.mk
-include lvgl/examples/widgets/imgbtn/subdir.mk
-include lvgl/examples/widgets/img/subdir.mk
-include lvgl/examples/widgets/dropdown/subdir.mk
-include lvgl/examples/widgets/colorwheel/subdir.mk
-include lvgl/examples/widgets/checkbox/subdir.mk
-include lvgl/examples/widgets/chart/subdir.mk
-include lvgl/examples/widgets/canvas/subdir.mk
-include lvgl/examples/widgets/calendar/subdir.mk
-include lvgl/examples/widgets/btnmatrix/subdir.mk
-include lvgl/examples/widgets/btn/subdir.mk
-include lvgl/examples/widgets/bar/subdir.mk
-include lvgl/examples/widgets/arc/subdir.mk
-include lvgl/examples/widgets/animimg/subdir.mk
-include lvgl/examples/styles/subdir.mk
-include lvgl/examples/scroll/subdir.mk
-include lvgl/examples/porting/subdir.mk
-include lvgl/examples/layouts/grid/subdir.mk
-include lvgl/examples/layouts/flex/subdir.mk
-include lvgl/examples/get_started/subdir.mk
-include lvgl/examples/event/subdir.mk
-include lvgl/examples/assets/subdir.mk
-include lvgl/examples/anim/subdir.mk
-include XPT2064/subdir.mk
-include ILI9341/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := F407_LVGL
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
F407_LVGL.elf \

MAP_FILES += \
F407_LVGL.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
F407_LVGL.list \


# All Target
all: main-build

# Main-build Target
main-build: F407_LVGL.elf secondary-outputs

# Tool invocations
F407_LVGL.elf F407_LVGL.map: $(OBJS) $(USER_OBJS) D:\ClassRoom\ComputerNetworking\Final\F407_LVGL\STM32F407VETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "F407_LVGL.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\ClassRoom\ComputerNetworking\Final\F407_LVGL\STM32F407VETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="F407_LVGL.map" -Wl,--gc-sections -static -L"D:\ClassRoom\ComputerNetworking\Final\F407_LVGL\ILI9341" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

F407_LVGL.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "F407_LVGL.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) F407_LVGL.elf F407_LVGL.list F407_LVGL.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
