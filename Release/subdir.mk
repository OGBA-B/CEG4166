################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CyclicScheduler.c \
../SerialLCDModule.c \
../WheelMotion.c \
../ledModule.c \
../main.c \
../motion.c \
../thermalSensor.c 

OBJS += \
./CyclicScheduler.o \
./SerialLCDModule.o \
./WheelMotion.o \
./ledModule.o \
./main.o \
./motion.o \
./thermalSensor.o 

C_DEPS += \
./CyclicScheduler.d \
./SerialLCDModule.d \
./WheelMotion.d \
./ledModule.d \
./main.d \
./motion.d \
./thermalSensor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\nnamdi\workspace\FreeRTOS801\include" -I"C:\Users\nnamdi\workspace\CEG4166_RTS_Lib\include" -DGCC_MEGA_AVR -Wall -O2 -ffunction-sections -fdata-sections -mcall-prologues -mrelax -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


