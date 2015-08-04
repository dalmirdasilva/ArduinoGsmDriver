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

#include "SIM900.h"

SIM900::SIM900(unsigned char receivePin, unsigned char transmitPin) : SoftwareSerial(receivePin, transmitPin) {
    rxBuffer[0] = '\0';
    echo = true;
}

void SIM900::begin(long bound) {
    bool ready = false;
    unsigned char tries = 3;
    SoftwareSerial::begin(bound);
    do {
        ready = sendCommandExpecting((const char *)"AT", (const char *)"OK", (unsigned long) 100);
        if (!ready) {
            delay(100);
        } else {
            break;
        }
    } while (tries--);
}

bool SIM900::sendCommandExpecting(const char *command, const char *expectation, bool append, unsigned long timeout) {
    if (sendCommand(command, append, timeout) == 0) {
        return false;
    }
    return doesResponseContain(expectation);
}

bool SIM900::doesResponseContain(const char *expectation) {
    rxPointer = &rxBuffer[0];
    bool does = strstr((const char*) rxPointer, (const char*) expectation) != NULL;
    return does;
}

int SIM900::sendCommand(const char *command, bool append, unsigned long timeout) {
    rxBuffer[0] = '\0';
    if (append) {
        print("AT");
    }
    println(command);
    readResponse(timeout);
}

int SIM900::readResponse(unsigned long timeout) {
    int availableBytes;
    unsigned long start = millis();
    int pointer = 0;
    while (!available() && (millis() - start) < timeout);
    start = millis();
    do {
        availableBytes = available();
        if (availableBytes > 0) {
            if (pointer + availableBytes >= SIM900_RX_BUFFER_SIZE) {
                availableBytes = SIM900_RX_BUFFER_SIZE - (pointer + 1);
            }
            if (availableBytes == 0) {
                flush();
            } else {
                readBytes((char *) &rxBuffer[pointer], availableBytes);
                pointer += availableBytes;
                rxBuffer[pointer] = 0;
            }
        }
    } while ((millis() - start) < timeout && availableBytes);
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

#endif /* __ARDUINO_DRIVER_GSM_SIM900_CPP__ */
