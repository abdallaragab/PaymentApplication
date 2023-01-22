################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Application/app.c 

C_DEPS += \
./src/Application/app.d 

OBJS += \
./src/Application/app.o 


# Each subdirectory must supply rules for building sources it contributes
src/Application/%.o: ../src/Application/%.c src/Application/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Xlinker -Map=output.map -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-Application

clean-src-2f-Application:
	-$(RM) ./src/Application/app.d ./src/Application/app.o

.PHONY: clean-src-2f-Application

