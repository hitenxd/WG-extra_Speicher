################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../alte\ abgaben/Zettel_3/matrix_datei.c \
../alte\ abgaben/Zettel_3/matrix_operationen.c \
../alte\ abgaben/Zettel_3/sum.c 

OBJS += \
./alte\ abgaben/Zettel_3/matrix_datei.o \
./alte\ abgaben/Zettel_3/matrix_operationen.o \
./alte\ abgaben/Zettel_3/sum.o 

C_DEPS += \
./alte\ abgaben/Zettel_3/matrix_datei.d \
./alte\ abgaben/Zettel_3/matrix_operationen.d \
./alte\ abgaben/Zettel_3/sum.d 


# Each subdirectory must supply rules for building sources it contributes
alte\ abgaben/Zettel_3/matrix_datei.o: ../alte\ abgaben/Zettel_3/matrix_datei.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"alte abgaben/Zettel_3/matrix_datei.d" -MT"alte\ abgaben/Zettel_3/matrix_datei.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

alte\ abgaben/Zettel_3/matrix_operationen.o: ../alte\ abgaben/Zettel_3/matrix_operationen.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"alte abgaben/Zettel_3/matrix_operationen.d" -MT"alte\ abgaben/Zettel_3/matrix_operationen.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

alte\ abgaben/Zettel_3/sum.o: ../alte\ abgaben/Zettel_3/sum.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"alte abgaben/Zettel_3/sum.d" -MT"alte\ abgaben/Zettel_3/sum.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


