################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
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
SECONDARY_FLASH += \
smart\ lock.hex \

SECONDARY_LIST += \
smart\ lock.lst \

SECONDARY_SIZE += \
smart\ lock.siz \


# 所有目标
all: smart\ lock.elf secondary-outputs

# 工具调用
smart\ lock.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -T "C:\Users\33511\Desktop\lock\lock\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"smart lock.map" --specs=nano.specs --specs=nosys.specs -o "smart lock.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
smart\ lock.hex: smart\ lock.elf
	@	riscv-none-embed-objcopy -O ihex "smart lock.elf"  "smart lock.hex"
	@	@
smart\ lock.lst: smart\ lock.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble "smart lock.elf" > "smart lock.lst"
	@	@
smart\ lock.siz: smart\ lock.elf
	@	riscv-none-embed-size --format=berkeley "smart lock.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) "smart lock.elf"
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
