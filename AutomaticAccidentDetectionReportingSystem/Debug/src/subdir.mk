################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ADXL345.c \
../src/AutomaticAccidentDetectionReportingSystem.c \
../src/Functions.c \
../src/SIM808.c \
../src/cr_startup_lpc11xx.c \
../src/crp.c \
../src/sysinit.c 

OBJS += \
./src/ADXL345.o \
./src/AutomaticAccidentDetectionReportingSystem.o \
./src/Functions.o \
./src/SIM808.o \
./src/cr_startup_lpc11xx.o \
./src/crp.o \
./src/sysinit.o 

C_DEPS += \
./src/ADXL345.d \
./src/AutomaticAccidentDetectionReportingSystem.d \
./src/Functions.d \
./src/SIM808.d \
./src/cr_startup_lpc11xx.d \
./src/crp.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_LPCOPEN -D__LPC11XX__ -D__NEWLIB__ -I"C:\Work\Licenta\git\AutomaticAccidentDetectionReportingSystem\AutomaticAccidentDetectionReportingSystem\inc" -I"C:\Work\Licenta\git\AutomaticAccidentDetectionReportingSystem\nxp_lpcxpresso_11c24_board_lib\inc" -I"C:\Work\Licenta\git\AutomaticAccidentDetectionReportingSystem\lpc_chip_11cxx_lib\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


