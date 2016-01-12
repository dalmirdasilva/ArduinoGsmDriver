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

SIM900::SIM900(unsigned char receivePin, unsigned char transmitPin, unsigned char resetPin, unsigned char powerPin) :
        SoftwareSerial(receivePin, transmitPin), echo(true), resetPin(resetPin), powerPin(powerPin), responseFullyRead(
        true) {
    rxBuffer[0] = '\0';
    pinMode(resetPin, OUTPUT);
    pinMode(powerPin, OUTPUT);
}

SIM900::~SIM900() {
}

unsigned char SIM900::begin(long bound) {
    unsigned char ready = 0;
    SoftwareSerial::begin(bound);
    if (sendCommandExpecting((const char *) "AT", (const char *) "OK", (unsigned long) 100)) {
        ready = 1;
    } else {
        unsigned long start = millis();
        softPower();
        do {
            readResponse(SIM900_INITIALIZATION_TIMEOUT);
            ready = doesResponseContains("Call Ready");
        } while (!ready && millis() < start + SIM900_INITIALIZATION_TIMEOUT);
    }
    return ready;
}

void SIM900::softReset() {
    digitalWrite(resetPin, HIGH);
    delay(100);
    digitalWrite(resetPin, LOW);
}

void SIM900::softPower() {
    digitalWrite(powerPin, HIGH);
    delay(1000);
    digitalWrite(powerPin, LOW);
}

bool SIM900::sendCommandExpecting(const char *command, const char *expectation, bool append, unsigned long timeout) {
    if (sendCommand(command, append, timeout) == 0) {
        return false;
    }
    return doesResponseContains(expectation);
}

bool SIM900::doesResponseContains(const char *expectation) {
    return findInResponse(expectation) != NULL;
}

int SIM900::sendCommand(const char *command, bool append, unsigned long timeout) {
    rxBuffer[0] = '\0';
    if (append) {
        print("AT");
    }
    println(command);
    return readResponse(timeout);
}

unsigned int SIM900::readResponse(unsigned long timeout) {
    int availableBytes;
    unsigned long start = millis();
    unsigned int pointer = 0;
    while (!available() && (millis() - start) < timeout)
        ;
    start = millis();
    responseFullyRead = true;
    do {
        availableBytes = available();
        delay(10);
        if (availableBytes > 0) {
            if (pointer + availableBytes >= SIM900_RX_BUFFER_SIZE) {
                availableBytes = SIM900_RX_BUFFER_SIZE - (pointer + 1);
                responseFullyRead = false;
            }
            if (availableBytes == 0) {
                flush();
            } else {
                readBytes((char *) &rxBuffer[pointer], availableBytes);
                pointer += availableBytes;
                rxBuffer[pointer] = 0;
            }
        }
    } while ((millis() - start) < timeout && availableBytes > 0);
    return pointer;
}

void SIM900::setCommandEcho(bool echo) {
    this->echo = echo;
    char command[] = "E0";
    if (echo) {
        command[1] = '1';
    }
    sendCommand(command, true, 100);
}

unsigned char SIM900::disconnect(DisconnectParamter param) {
    return 3;
}

bool SIM900::wasResponseFullyRead() {
    return responseFullyRead;
}

const char *SIM900::findInResponse(const char *str) {
    const char *response = (const char *) &rxBuffer[0];
    return (const char *) strstr(response, str);
}

#endif /* __ARDUINO_DRIVER_GSM_SIM900_CPP__ */
