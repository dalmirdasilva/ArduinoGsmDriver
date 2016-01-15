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
#include <WString.h>

GprsSIM900::GprsSIM900(SIM900 *sim) :
        sim(sim), multiplexed(false) {
}

unsigned char GprsSIM900::begin(long bound) {
    if (sim->begin(bound) == 0) {
        return 0;
    }
    sim->setCommandEcho(false);
    sim->sendCommand((const char *) F("+CIPSHUT"), true);
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
    sim->write((const char *) F("AT+CSTT=\""));
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
    expected = sim->sendCommandExpecting((const char *) F("+CIICR"), "OK", true, GPRS_SIM900_CIICR_TIMEOUT);
    return (unsigned char) (expected ? GprsSIM900::OK : GprsSIM900::ERROR);
}

unsigned char GprsSIM900::obtainIp(unsigned char ip[4]) {
    OperationResult op = GprsSIM900::ERROR;
    unsigned int receivedBytes = sim->sendCommand((const char *) F("+CIFSR"), true, GPRS_SIM900_CIICR_TIMEOUT);
    if (receivedBytes > 0) {
        const char* p = (const char*) sim->getLastResponse();
        if (parseIp(p, ip) == 4) {
            op = GprsSIM900::OK;
        }
    }
    return op;
}

unsigned char GprsSIM900::status() {
    return status(-1);
}

unsigned char GprsSIM900::status(unsigned char connection) {
    int at;
    ConnectionState state = GprsSIM900::ERROR_WHEN_QUERING;
    sim->write("AT+CIPSTATUS");
    if (connection != (char) -1) {
        sim->write('=');
        sim->write('0' + connection);
    }
    sim->sendCommandExpecting("", "OK");
    at = sim->waitUntilReceive("STATE", GPRS_SIM900_CIPSTATUS_TIMEOUT);
    if (at >= 0) {
        if (sim->doesResponseContains((const char *) F("INITIAL"))) {
            state = GprsSIM900::IP_INITIAL;
        } else if (sim->doesResponseContains((const char *) F("START"))) {
            state = GprsSIM900::IP_START;
        } else if (sim->doesResponseContains((const char *) F("CONFIG"))) {
            state = GprsSIM900::IP_CONFIG;
        } else if (sim->doesResponseContains((const char *) F("GPRSACT"))) {
            state = GprsSIM900::IP_GPRSACT;
        } else if (sim->doesResponseContains((const char *) F("STATUS"))) {
            state = GprsSIM900::IP_STATUS;
        } else if (sim->doesResponseContains((const char *) F("CONNECTING"))
                || sim->doesResponseContains((const char *) F("LISTENING"))) {
            state = GprsSIM900::CONNECTING_OR_LISTENING;
        } else if (sim->doesResponseContains((const char *) F("CONNECT OK"))) {
            state = GprsSIM900::CONNECT_OK;
        } else if (sim->doesResponseContains((const char *) F("CLOSING"))) {
            state = GprsSIM900::CLOSING;
        } else if (sim->doesResponseContains((const char *) F("CLOSED"))) {
            state = GprsSIM900::CLOSED;
        } else if (sim->doesResponseContains((const char *) F("DEACT"))) {
            state = GprsSIM900::PDP_DEACT;
        }
    }
    return state;
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
    int at;
    sim->write((const char *) F("AT+CIPSTART="));
    if (connection != (char) -1) {
        sim->write('0' + connection);
        sim->write(',');
    }
    sim->write('"');
    sim->write(mode);
    sim->write("\",\"");
    sim->write(address);
    sim->write("\",\"");
    sim->print(port, DEC);
    sim->sendCommand("\"");
    at = sim->waitUntilReceive((const char *) F("CONNECT"), GPRS_SIM900_CIPSTART_TIMEOUT);
    if (at >= 0 && !sim->doesResponseContains((const char *) F("FAIL"))) {
        return GprsSIM900::OK;
    }
    return (unsigned char) GprsSIM900::ERROR;
}

unsigned int GprsSIM900::send(unsigned char *buf, unsigned int len) {
    return send(-1, buf, len);
}

unsigned int GprsSIM900::send(char connection, unsigned char *buf, unsigned int len) {
    bool ok;
    int at = -1;
    unsigned int sent = 0;
    sim->write((const char *) F("AT+CIPSEND="));
    if (connection != (char) -1) {
        sim->write('0' + connection);
        sim->write(',');
    }
    sim->print(len, DEC);
    ok = sim->sendCommandExpecting("", ">");
    if (ok) {
        sent = (unsigned int) sim->write((const char *) buf, len);
        at = sim->waitUntilReceive((const char *) F("SEND OK"), GPRS_SIM900_SEND_TIMEOUT);
    }
    return at >= 0 ? sent : 0;
}

unsigned char GprsSIM900::close(char connection) {
    int at;
    OperationResult op = GprsSIM900::ERROR;
    sim->write((const char *) F("AT+CIPCLOSE=1"));
    if (connection != (char) -1) {
        sim->write(',');
        sim->write('0' + connection);
    }
    sim->sendCommand();
    at = sim->waitUntilReceive((const char *) F("CLOSE OK"), GPRS_SIM900_CIPSTART_TIMEOUT);
    if (at >= 0) {
        op = GprsSIM900::OK;
    }
    return op;
}

unsigned char GprsSIM900::close() {
    return close(-1);
}

// TODO
unsigned char GprsSIM900::resolve(const char *name, unsigned char ip[4]) {
    bool ok;
    int at;
    const char* p;
    OperationResult op = GprsSIM900::ERROR;
    sim->write((const char *) F("AT+CDNSGIP=\""));
    sim->write(name);
    ok = sim->sendCommandExpecting("\"", "OK");
    if (ok) {
        at = sim->waitUntilReceive((const char *) F("+CDNSGIP: 1"), GPRS_SIM900_CDNSGIP_TIMEOUT);
        if (at >= 0) {
            at = sim->waitUntilReceive("\",\"", GPRS_SIM900_CDNSGIP_TIMEOUT);
            if (at >= 0) {
                p = (const char*) sim->getLastResponse();
                if (parseIp(p + at, ip) == 4) {
                    op = GprsSIM900::OK;
                }
            }
        }
    }
    return op;
}

unsigned char GprsSIM900::configureServer(unsigned char mode, unsigned int port) {
    mode &= 0x01;
    sim->write((const char *) F("AT+CIPSERVER="));
    sim->print(mode, DEC);
    sim->write(',');
    sim->print(mode, DEC);
    return sim->sendCommandExpecting("", "OK") ? GprsSIM900::OK : GprsSIM900::ERROR;
}

unsigned char GprsSIM900::shutdown() {
    return sim->sendCommandExpecting((const char *) F("AT+CIPSHUT"), "SHUT OK") ? GprsSIM900::OK : GprsSIM900::ERROR;
}

void GprsSIM900::transmittingState(void *stateStruct) {
    transmittingState(-1, stateStruct);
}

void GprsSIM900::transmittingState(unsigned char connection, void *stateStruct) {
    int at;
    TransmittingState *state = (TransmittingState *) stateStruct;
    sim->write((const char *) F("AT+CIPACK="));
    if (connection != (char) -1) {
        sim->write(',');
        sim->write('0' + connection);
    }
    sim->sendCommand();
    at = sim->waitUntilReceive((const char *) F("+CIPACK"), GPRS_SIM900_CIPACK_TIMEOUT);
    if (at >= 0) {
        unsigned char *pos = sim->getLastResponse();
        // > +CIPACK: 2,2,0
        sscanf((const char *) (pos + at), (const char *) F("+CIPACK: %d,%d,%d"), &state->txlen, &state->acklen,
                &state->nacklen);
    } else {
        state->txlen = state->acklen = state->nacklen = 0;
    }
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

