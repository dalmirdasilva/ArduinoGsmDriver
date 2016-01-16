/**
 * Arduino - Gsm driver
 * 
 * CallSIM900.cpp
 * 
 * Interface to calls.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_GSM_CALL_SIM900_CPP__
#define __ARDUINO_DRIVER_GSM_CALL_SIM900_CPP__ 1

#include "CallSIM900.h"
#include <SIM900.h>

CallSIM900::CallSIM900(SIM900 *sim)
        : sim(sim) {
}

CallSIM900::~CallSIM900() {
}

unsigned char CallSIM900::answer() {
    return (unsigned char) sim->sendCommandExpecting((const char*) "A", (const char*) "CONNECT", true);
}

unsigned char CallSIM900::callNumber(unsigned char *number) {
}

unsigned char CallSIM900::callFromPhonebook(unsigned char position) {
    unsigned char cmd[4] = "D";
    itoa(position, (char *) &cmd[1], 10);
    sim->sendCommand((const char *) cmd, true);
    return checkResponse();
}

unsigned char CallSIM900::callByPhonebookMatch(unsigned char *entry) {
}

unsigned char CallSIM900::redial() {

}

unsigned char CallSIM900::disconnect() {
    return sim->disconnect(SIM900::ALL_CALL_ON_ALL_CHANNELS);
}

unsigned char CallSIM900::checkResponse() {
    CallResponse response = OK;
    if (sim->doesResponseContains((const char *) "OK")) {
        response = OK;
    } else if (sim->doesResponseContains((const char *) "CME")) {
        response = CME_ERROR;
    } else if (sim->doesResponseContains((const char *) "DIALTONE")) {
        response = NO_DIALTONE;
    } else if (sim->doesResponseContains((const char *) "BUSY")) {
        response = BUSY;
    } else if (sim->doesResponseContains((const char *) "CARRIER")) {
        response = NO_CARRIER;
    } else if (sim->doesResponseContains((const char *) "ANSWER")) {
        response = NO_ANSWER;
    } else if (sim->doesResponseContains((const char *) "CONNECT")) {
        response = CONNECT_TEXT;
    }
    return response;
}

#endif /* __ARDUINO_DRIVER_GSM_CALL_SIM900_CPP__ */
