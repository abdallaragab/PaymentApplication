################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Server/server.c 

C_DEPS += \
./src/Server/server.d 

OBJS += \
./src/Server/server.o 


# Each subdirectory must supply rules for building sources it contributes
src/Server/%.o: ../src/Server/%.c src/Server/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Xlinker -Map=output.map -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-Server

clean-src-2f-Server:
	-$(RM) ./src/Server/server.d ./src/Server/server.o

.PHONY: clean-src-2f-Server

