/**
 * Arduino - Gsm driver
 * 
 * SIM900.cpp
 * 
 * SIM900 implementation of the SIM900 modem.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_GSM_SIM900_CPP__
#define __ARDUINO_DRIVER_GSM_SIM900_CPP__ 1

#include <Arduino.h>
#include "SIM900.h"

SIM900::SIM900(unsigned char receivePin, unsigned char transmitPin)
        : SIM900(receivePin, transmitPin, 0, 0) {
}

SIM900::SIM900(unsigned char receivePin, unsigned char transmitPin, unsigned char resetPin, unsigned char powerPin)
        : SoftwareSerialAttentionDevice(receivePin, transmitPin), echo(true), resetPin(resetPin), powerPin(powerPin) {
    pinMode(resetPin, OUTPUT);
    pinMode(powerPin, OUTPUT);
    softResetAndPowerEnabled = !(resetPin == 0 && powerPin == 0);
}

SIM900::~SIM900() {
}

unsigned char SIM900::begin(long bound) {
    SoftwareSerial::begin(bound);
    if (sendCommandExpecting("AT", "OK")) {
        return 1;
    }
    softPower();
    return (unsigned char) (waitUntilReceive("Call Ready", SIM900_INITIALIZATION_TIMEOUT) >= 0);
}

void SIM900::softReset() {
    if (softResetAndPowerEnabled) {
        digitalWrite(resetPin, HIGH);
        delay(100);
        digitalWrite(resetPin, LOW);
    }
}

void SIM900::softPower() {
    if (softResetAndPowerEnabled) {
        digitalWrite(powerPin, HIGH);
        delay(1000);
        digitalWrite(powerPin, LOW);
    }
}

void SIM900::setEcho(bool echo) {
    this->echo = echo;
    char command[] = "E0";
    if (echo) {
        command[1] = '1';
    }
    sendCommand(command, true, 100);
}

unsigned char SIM900::disconnect(DisconnectParamter param) {
    // TODO
    return 3;
}

#endif /* __ARDUINO_DRIVER_GSM_SIM900_CPP__ */
