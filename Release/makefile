################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
RealTime.lss \

FLASH_IMAGE += \
RealTime.hex \

EEPROM_IMAGE += \
RealTime.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: RealTime.elf secondary-outputs

dependents:
	-cd C:/Users/nnamdi/workspace/FreeRTOS801/Release && $(MAKE) all
	-cd C:/Users/nnamdi/workspace/CEG4166_RTS_Lib/Release && $(MAKE) all

# Tool invocations
RealTime.elf: $(OBJS) $(USER_OBJS) C:/Users/nnamdi/workspace/FreeRTOS801/Release/libFreeRTOS801.a C:/Users/nnamdi/workspace/CEG4166_RTS_Lib/Release/libCEG4166_RTS_Lib.a
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,RealTime.map --gc-sections -Wl,-u,vfprintf -Wl -L"C:\Users\nnamdi\workspace\FreeRTOS801\Release" -L"C:\Users\nnamdi\workspace\CEG4166_RTS_Lib\Release" -mmcu=atmega2560 -o "RealTime.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

RealTime.lss: RealTime.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S RealTime.elf  >"RealTime.lss"
	@echo 'Finished building: $@'
	@echo ' '

RealTime.hex: RealTime.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex RealTime.elf  "RealTime.hex"
	@echo 'Finished building: $@'
	@echo ' '

RealTime.eep: RealTime.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex RealTime.elf  "RealTime.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: RealTime.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega2560 RealTime.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) RealTime.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:
C:/Users/nnamdi/workspace/FreeRTOS801/Release/libFreeRTOS801.a:
C:/Users/nnamdi/workspace/CEG4166_RTS_Lib/Release/libCEG4166_RTS_Lib.a:

-include ../makefile.targets
