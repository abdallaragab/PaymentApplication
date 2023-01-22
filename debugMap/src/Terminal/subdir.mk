################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Terminal/terminal.c 

C_DEPS += \
./src/Terminal/terminal.d 

OBJS += \
./src/Terminal/terminal.o 


# Each subdirectory must supply rules for building sources it contributes
src/Terminal/%.o: ../src/Terminal/%.c src/Terminal/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Xlinker -Map=output.map -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-Terminal

clean-src-2f-Terminal:
	-$(RM) ./src/Terminal/terminal.d ./src/Terminal/terminal.o

.PHONY: clean-src-2f-Terminal

