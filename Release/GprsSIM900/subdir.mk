################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../GprsSIM900/GprsSIM900.cpp 

OBJS += \
./GprsSIM900/GprsSIM900.o 

CPP_DEPS += \
./GprsSIM900/GprsSIM900.d 


# Each subdirectory must supply rules for building sources it contributes
GprsSIM900/%.o: ../GprsSIM900/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/usr/share/arduino/hardware/arduino/variants/standard -I/usr/share/arduino/hardware/arduino/cores/arduino -I/usr/share/arduino/libraries/SoftwareSerial -I"/storage/microcontroller/arduino/driver/gsm/Call" -I"/storage/microcontroller/arduino/driver/gsm/CallSIM900" -I"/storage/microcontroller/arduino/driver/gsm/Gprs" -I"/storage/microcontroller/arduino/driver/gsm/GprsSIM900" -I"/storage/microcontroller/arduino/driver/gsm/SIM900" -I"/storage/microcontroller/arduino/driver/gsm/Sms" -I"/storage/microcontroller/arduino/driver/gsm/SmsSIM900" -Wall -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


