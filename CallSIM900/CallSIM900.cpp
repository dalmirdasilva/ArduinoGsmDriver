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

CallSIM900::CallSIM900(SIM900 *sim) : sim(sim) {
}

unsigned char CallSIM900::answer() {
//    sim->sendCommand((const char*) "ATA\n", 4);
//    return sim->receiveStatus();
}

unsigned char CallSIM900::callNumber(unsigned char *number) {

}

unsigned char CallSIM900::callFromPhonebook(unsigned char position) {

}

unsigned char CallSIM900::callByPhonebookMatch(unsigned char *entry) {

}

unsigned char CallSIM900::redial() {

}

unsigned char CallSIM900::disconnect() {
    
}

#endif /* __ARDUINO_DRIVER_GSM_CALL_SIM900_CPP__ */
