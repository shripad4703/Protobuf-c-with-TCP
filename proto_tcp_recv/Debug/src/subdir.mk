################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/addressbook.pb-c.c \
../src/cmessage.pb-c.c \
../src/proto_tcp_recv.c 

OBJS += \
./src/addressbook.pb-c.o \
./src/cmessage.pb-c.o \
./src/proto_tcp_recv.o 

C_DEPS += \
./src/addressbook.pb-c.d \
./src/cmessage.pb-c.d \
./src/proto_tcp_recv.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


