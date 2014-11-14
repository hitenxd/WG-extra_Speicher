################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../handler.c \
../sock.c \
../tcpserver.c \
../unp_readline.c 

OBJS += \
./handler.o \
./sock.o \
./tcpserver.o \
./unp_readline.o 

C_DEPS += \
./handler.d \
./sock.d \
./tcpserver.d \
./unp_readline.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


