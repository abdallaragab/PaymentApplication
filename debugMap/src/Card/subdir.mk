################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Card/card.c 

C_DEPS += \
./src/Card/card.d 

OBJS += \
./src/Card/card.o 


# Each subdirectory must supply rules for building sources it contributes
src/Card/%.o: ../src/Card/%.c src/Card/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Xlinker -Map=output.map -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-Card

clean-src-2f-Card:
	-$(RM) ./src/Card/card.d ./src/Card/card.o

.PHONY: clean-src-2f-Card

