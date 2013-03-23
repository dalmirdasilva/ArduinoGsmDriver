################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CallSIM900/CallSIM900.cpp 

OBJS += \
./CallSIM900/CallSIM900.o 

CPP_DEPS += \
./CallSIM900/CallSIM900.d 


# Each subdirectory must supply rules for building sources it contributes
CallSIM900/%.o: ../CallSIM900/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/usr/share/arduino/hardware/arduino/variants/standard -I/usr/share/arduino/hardware/arduino/cores/arduino -I/usr/share/arduino/libraries/SoftwareSerial -I"/storage/microcontroller/arduino/driver/gsm/Call" -I"/storage/microcontroller/arduino/driver/gsm/CallSIM900" -I"/storage/microcontroller/arduino/driver/gsm/Gprs" -I"/storage/microcontroller/arduino/driver/gsm/GprsSIM900" -I"/storage/microcontroller/arduino/driver/gsm/SIM900" -I"/storage/microcontroller/arduino/driver/gsm/Sms" -I"/storage/microcontroller/arduino/driver/gsm/SmsSIM900" -Wall -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


