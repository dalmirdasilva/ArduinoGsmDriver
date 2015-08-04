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

GprsSIM900::GprsSIM900(SIM900 *sim) :
        sim(sim) {
    multiplexed = false;
}

void GprsSIM900::begin(long bound) {
    sim->begin(bound);
    sim->setCommandEcho(false);
    sim->sendCommand("+CIPSHUT", (bool) true);
}

unsigned char GprsSIM900::useMultiplexer(bool use) {
    char command[] = "+CIPMUX=0";
    if (use) {
        command[8] = '1';
    }
    multiplexed = use;
    return (unsigned char) sim->sendCommandExpecting(command, "OK", (bool) true);
}

unsigned char GprsSIM900::attach(const char *apn, const char *login, const char *password) {
    bool expected;
    sim->write("AT+CSTT=\"");
    sim->write(apn);
    sim->write("\",\"");
    sim->write(login);
    sim->write("\",\"");
    sim->write(password);
    expected = sim->sendCommandExpecting("\"", "OK");
    return (unsigned char) (expected ? GprsSIM900::OK : GprsSIM900::ERROR);
}

unsigned char GprsSIM900::bringUp() {
    bool expected;
    expected = sim->sendCommandExpecting("+CIICR", "OK", true, 20000);
    return (unsigned char) (expected ? GprsSIM900::OK : GprsSIM900::ERROR);
}

unsigned char GprsSIM900::obtainIp(unsigned char *buf) {
    sim->sendCommand("+CIFSR", (bool) true);
    if (!sim->doesResponseContain("ERROR")) {
        char n = 0, j, i = 0, part[4] = { 0 };
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

unsigned char GprsSIM900::configureDns(const char *primary, const char *secondary) {
    bool expected;
    sim->write("AT+CDNSCFG=\"");
    sim->write(primary);
    sim->write("\",\"");
    sim->write(secondary);
    expected = sim->sendCommandExpecting("\"", "OK");
    return (unsigned char) (expected ? GprsSIM900::OK : GprsSIM900::ERROR);
}

unsigned char GprsSIM900::open(const char *mode, const char *address, unsigned int port) {
    return open(-1, mode, address, port);
}

unsigned char GprsSIM900::open(char connection, const char *mode, const char *address,
        unsigned int port) {
    bool expected;
    sim->write("AT+CIPSTART=");
    if (connection != -1) {
        sim->write('0' + connection);
        sim->write(',');
    }
    sim->write('"');
    sim->write(mode);
    sim->write("\",\"");
    sim->write(address);
    sim->write("\",\"");
    sim->print(port, DEC);
    expected = sim->sendCommandExpecting("\"", "OK");
    return (unsigned char) (expected ? GprsSIM900::OK : GprsSIM900::ERROR);
}

unsigned char GprsSIM900::close(char connection) {
    bool expected;
    sim->write("AT+CIPCLOSE=1");
    if (connection != -1) {
        sim->write(',');
        sim->write('0' + connection);
    }
    expected = sim->sendCommandExpecting("", "OK");
    return (unsigned char) (expected ? GprsSIM900::OK : GprsSIM900::ERROR);
}

unsigned char GprsSIM900::close() {
    return close(-1);
}

unsigned char GprsSIM900::resolve(const char *name, unsigned char *buf, unsigned int len) {
    bool expected;
    sim->write("AT+CDNSGIP=");
    expected = sim->sendCommandExpecting(name, "OK");
    return (unsigned char) (expected ? GprsSIM900::OK : GprsSIM900::ERROR);
}

unsigned char GprsSIM900::send(unsigned char *buf, unsigned int len) {
    //AT+CIPSEND=<length>
    // sim->write(buf, len);
}

unsigned char GprsSIM900::send(char connection, unsigned char *buf, unsigned int len) {
    sim->readBytes((char *) buf, len);
}

unsigned char GprsSIM900::setUpServer(unsigned char mode, unsigned int port) {
}

unsigned char GprsSIM900::shutdown() {
}

#endif /* __ARDUINO_DRIVER_GSM_GPRS_SIM900_CPP__ */

