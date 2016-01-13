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

GprsSIM900::GprsSIM900(SIM900 *sim)
        : sim(sim), multiplexed(false) {
}

unsigned char GprsSIM900::begin(long bound) {
    if (sim->begin(bound) == 0) {
        return 0;
    }
    sim->setCommandEcho(false);
    sim->sendCommand("+CIPSHUT", true);
    return 1;
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
    expected = sim->sendCommandExpecting("+CIICR", "OK", true, GPRS_SIM900_CIICR_TIMEOUT);
    return (unsigned char) (expected ? GprsSIM900::OK : GprsSIM900::ERROR);
}

unsigned char GprsSIM900::obtainIp(unsigned char ip[4]) {
    unsigned int receivedBytes = sim->sendCommand("+CIFSR", true, (unsigned long) GPRS_SIM900_CIICR_TIMEOUT);
    if (receivedBytes > 0) {
        const char* p = (const char*) sim->getLastResponse();
        return (parseIp(p, ip) == 4) ? GprsSIM900::OK : GprsSIM900::ERROR;
    }
    return GprsSIM900::ERROR;
}

unsigned char GprsSIM900::status() {
    sim->sendCommand("+CIFSR", true);
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

unsigned char GprsSIM900::open(char connection, const char *mode, const char *address, unsigned int port) {
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

unsigned char GprsSIM900::resolve(const char *name, unsigned char ip[4]) {
    bool ok;
    sim->write("AT+CDNSGIP=\"");
    sim->write(name);
    ok = sim->sendCommandExpecting("\"", "OK");
    if (ok) {
        int at = sim->waitUntilReceive("+CDNSGIP: 1", GPRS_SIM900_CDNSGIP_TIMEOUT);
        if (at >= 0) {
            at = sim->waitUntilReceive("\",\"", GPRS_SIM900_CDNSGIP_TIMEOUT);
            if (at >= 0) {
                const char* p = (const char*) sim->getLastResponse();
                return parseIp(p + at, ip) == 4 ? GprsSIM900::OK : GprsSIM900::ERROR;
            }
        }
    }
    return GprsSIM900::ERROR;
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

unsigned char GprsSIM900::parseIp(const char *buf, unsigned char ip[4]) {
    const char *p = buf;
    unsigned char j, i = 0, n = 0, part[4] = { 0 };
    while (*p != '\0' && n < 4) {
        if (*p >= '0' && *p <= '9') {
            part[i++ % 3] = *p;
        }
        if (*p == '.') {
            ip[n++] = (unsigned char) atoi((const char*) part);
            for (j = 0; j < 4; j++) {
                part[j] = '\0';
            }
            i = 0;
        }
        p++;
    }
    if (i > 0) {
        ip[n++] = (unsigned char) atoi((const char*) part);
    }
    return n;
}

#endif /* __ARDUINO_DRIVER_GSM_GPRS_SIM900_CPP__ */

