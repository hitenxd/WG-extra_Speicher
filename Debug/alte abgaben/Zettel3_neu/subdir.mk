################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../alte\ abgaben/Zettel3_neu/Matrix_op.c \
../alte\ abgaben/Zettel3_neu/matrix_datei.c 

OBJS += \
./alte\ abgaben/Zettel3_neu/Matrix_op.o \
./alte\ abgaben/Zettel3_neu/matrix_datei.o 

C_DEPS += \
./alte\ abgaben/Zettel3_neu/Matrix_op.d \
./alte\ abgaben/Zettel3_neu/matrix_datei.d 


# Each subdirectory must supply rules for building sources it contributes
alte\ abgaben/Zettel3_neu/Matrix_op.o: ../alte\ abgaben/Zettel3_neu/Matrix_op.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"alte abgaben/Zettel3_neu/Matrix_op.d" -MT"alte\ abgaben/Zettel3_neu/Matrix_op.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

alte\ abgaben/Zettel3_neu/matrix_datei.o: ../alte\ abgaben/Zettel3_neu/matrix_datei.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"alte abgaben/Zettel3_neu/matrix_datei.d" -MT"alte\ abgaben/Zettel3_neu/matrix_datei.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


