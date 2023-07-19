################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/PWM.c \
../User/ch32v30x_it.c \
../User/display.c \
../User/key.c \
../User/lcd.c \
../User/main.c \
../User/system_ch32v30x.c \
../User/usart2.c 

OBJS += \
./User/PWM.o \
./User/ch32v30x_it.o \
./User/display.o \
./User/key.o \
./User/lcd.o \
./User/main.o \
./User/system_ch32v30x.o \
./User/usart2.o 

C_DEPS += \
./User/PWM.d \
./User/ch32v30x_it.d \
./User/display.d \
./User/key.d \
./User/lcd.d \
./User/main.d \
./User/system_ch32v30x.d \
./User/usart2.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"C:\Users\33511\Desktop\lock\lock\Debug" -I"C:\Users\33511\Desktop\lock\lock\Core" -I"C:\Users\33511\Desktop\lock\lock\User" -I"C:\Users\33511\Desktop\lock\lock\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

