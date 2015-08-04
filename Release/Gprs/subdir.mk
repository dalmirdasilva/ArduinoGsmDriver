################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Gprs/Gprs.cpp 

OBJS += \
./Gprs/Gprs.o 

CPP_DEPS += \
./Gprs/Gprs.d 


# Each subdirectory must supply rules for building sources it contributes
Gprs/%.o: ../Gprs/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I/opt/arduino-1.6.5/hardware/arduino/avr/variants/standard/ -I/opt/arduino-1.6.5/hardware/arduino/avr/cores/arduino -I/opt/arduino-1.6.5/hardware/arduino/avr/libraries/SoftwareSerial -I"/work/opensource/personal/ArduinoGsmDriver/Call" -I"/work/opensource/personal/ArduinoGsmDriver/CallSIM900" -I"/work/opensource/personal/ArduinoGsmDriver/Gprs" -I"/work/opensource/personal/ArduinoGsmDriver/GprsSIM900" -I"/work/opensource/personal/ArduinoGsmDriver/SIM900" -I"/work/opensource/personal/ArduinoGsmDriver/Sms" -I"/work/opensource/personal/ArduinoGsmDriver/SmsSIM900" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


