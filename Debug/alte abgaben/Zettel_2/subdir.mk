################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../alte\ abgaben/Zettel_2/Brett.c \
../alte\ abgaben/Zettel_2/springerproblem.c 

OBJS += \
./alte\ abgaben/Zettel_2/Brett.o \
./alte\ abgaben/Zettel_2/springerproblem.o 

C_DEPS += \
./alte\ abgaben/Zettel_2/Brett.d \
./alte\ abgaben/Zettel_2/springerproblem.d 


# Each subdirectory must supply rules for building sources it contributes
alte\ abgaben/Zettel_2/Brett.o: ../alte\ abgaben/Zettel_2/Brett.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"alte abgaben/Zettel_2/Brett.d" -MT"alte\ abgaben/Zettel_2/Brett.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

alte\ abgaben/Zettel_2/springerproblem.o: ../alte\ abgaben/Zettel_2/springerproblem.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"alte abgaben/Zettel_2/springerproblem.d" -MT"alte\ abgaben/Zettel_2/springerproblem.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


