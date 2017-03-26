################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: AutomaticAccidentDetectionReportingSystem.axf

# Tool invocations
AutomaticAccidentDetectionReportingSystem.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Work\Licenta\git\AutomaticAccidentDetectionReportingSystem\nxp_lpcxpresso_11c24_board_lib\Debug" -L"C:\Work\Licenta\git\AutomaticAccidentDetectionReportingSystem\lpc_chip_11cxx_lib\Debug" -Xlinker -Map="AutomaticAccidentDetectionReportingSystem.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0 -mthumb -T "AutomaticAccidentDetectionReportingSystem_Debug.ld" -o "AutomaticAccidentDetectionReportingSystem.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) AutomaticAccidentDetectionReportingSystem.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "AutomaticAccidentDetectionReportingSystem.axf"; # arm-none-eabi-objcopy -v -O binary "AutomaticAccidentDetectionReportingSystem.axf" "AutomaticAccidentDetectionReportingSystem.bin" ; # checksum -p LPC1115_303 -d "AutomaticAccidentDetectionReportingSystem.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
