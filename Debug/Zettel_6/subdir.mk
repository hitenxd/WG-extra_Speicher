################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Zettel_6/Test_aufgabe19.c 

OBJS += \
./Zettel_6/Test_aufgabe19.o 

C_DEPS += \
./Zettel_6/Test_aufgabe19.d 


# Each subdirectory must supply rules for building sources it contributes
Zettel_6/%.o: ../Zettel_6/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


