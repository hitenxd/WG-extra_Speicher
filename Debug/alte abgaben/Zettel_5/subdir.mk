################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../alte\ abgaben/Zettel_5/Tcpclient.c \
../alte\ abgaben/Zettel_5/unp_readline.c 

OBJS += \
./alte\ abgaben/Zettel_5/Tcpclient.o \
./alte\ abgaben/Zettel_5/unp_readline.o 

C_DEPS += \
./alte\ abgaben/Zettel_5/Tcpclient.d \
./alte\ abgaben/Zettel_5/unp_readline.d 


# Each subdirectory must supply rules for building sources it contributes
alte\ abgaben/Zettel_5/Tcpclient.o: ../alte\ abgaben/Zettel_5/Tcpclient.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"alte abgaben/Zettel_5/Tcpclient.d" -MT"alte\ abgaben/Zettel_5/Tcpclient.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

alte\ abgaben/Zettel_5/unp_readline.o: ../alte\ abgaben/Zettel_5/unp_readline.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"alte abgaben/Zettel_5/unp_readline.d" -MT"alte\ abgaben/Zettel_5/unp_readline.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


