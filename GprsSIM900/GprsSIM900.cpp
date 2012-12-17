/**
 * Arduino - Gsm driver
 * 
 * GprsSIM900.h
 * 
 * GPRS connection using SIM900.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_GSM_GPRS_SIM900_CPP__
#define __ARDUINO_DRIVER_GSM_GPRS_SIM900_CPP__ 1

#include "GprsSIM900.h"

GprsSIM900::GprsSIM900(SIM900 *sim) : sim(sim) {
    multiconnection = false;
}

void GprsSIM900::begin(int bound) {
    sim->begin(bound);
    sim->sendCommand("+CIPSHUT", (bool) true);
}

unsigned char GprsSIM900::useMultiplexer(bool use) {
    char command[] = "+CIPMUX=0";
    if (use) {
        command[8] = '1';
    }
    multiconnection = use;
    return (unsigned char) sim->sendCommandExpecting(command, "OK", (bool) true);
}

unsigned char GprsSIM900::startTask(unsigned char *apn, unsigned char *login, unsigned char *password) {
    sim->write("AT+CSTT=");
    sim->write((const char*) apn);
    sim->write((const char*) login);
    sim->write((const char*) password);
    bool expected = sim->sendCommandExpecting("", "OK");
    return (unsigned char) (expected ? GprsSIM900::OK : GprsSIM900::ERROR);
}

unsigned char GprsSIM900::bringUp() {
    return (unsigned char) sim->sendCommandExpecting("+CIICR", "OK", true, 20000);
}

unsigned char GprsSIM900::obtainIp(unsigned char *buf) {
    sim->sendCommand("+CIFSR", (bool) true);
    if (!sim->doesResponseContains("ERROR")) {
        char n = 0, j, i = 0, part[4] = {0};
        unsigned char* p = sim->getLastResponse();
        while (*p != '\0' && n < 4) {
            if (*p >= '0' && *p <= '9') {
                part[i++ % 3] = *p;
            }
            if (*p == '.') {
                n++;
                *(buf++) = (unsigned char) atoi(part);
                for (j = 0; j < 4; j++) {
                    part[j] = 0;
                }
                i = 0;
            }
            p++;
        }
        if (i > 0) {
            n++;
            *(buf++) = (unsigned char) atoi(part);
        }
        return (n == 4) ? GprsSIM900::OK : GprsSIM900::ERROR;
    }
    return GprsSIM900::ERROR;
}

unsigned char GprsSIM900::status() {
    sim->sendCommand("+CIFSR", (bool) true);
}

unsigned char GprsSIM900::configureDns(unsigned char *primary, unsigned char *secondary) {
}

unsigned char GprsSIM900::open(unsigned char mode, unsigned char *address, unsigned char port) {
}

unsigned char GprsSIM900::open(unsigned char connection, unsigned char mode, unsigned char *address, unsigned char port) {
}

unsigned char GprsSIM900::close(unsigned char connection) {
}

unsigned char GprsSIM900::resolve(unsigned char *name, unsigned char *buf, unsigned int len) {
}

unsigned char GprsSIM900::send(unsigned char *buf, unsigned int len) {
}

unsigned char GprsSIM900::send(unsigned char connection, unsigned char *buf, unsigned int len) {
}

unsigned char GprsSIM900::setUpServer(unsigned char mode, unsigned int port) {
}

unsigned char GprsSIM900::shutdown() {
}

#endif /* __ARDUINO_DRIVER_GSM_GPRS_SIM900_CPP__ */

