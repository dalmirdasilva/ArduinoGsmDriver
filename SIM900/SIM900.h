/**
 * Arduino - Gsm driver
 * 
 * SIM900.h
 * 
 * SIM900 implementation of the SIM900 modem.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_GSM_SIM900_H__
#define __ARDUINO_DRIVER_GSM_SIM900_H__ 1

#include <SoftwareSerial.h>
#include <Arduino.h>
#include <string.h>

#define SIM900_RX_BUFFER_SIZE 256

class SIM900 : public SoftwareSerial {
    /**
     * RX buffer.
     */
    unsigned char rxBuffer[SIM900_RX_BUFFER_SIZE];

    /**
     * Pointer to the RX buffer.
     */
    unsigned char *rxPointer;
    
    /**
     * Using echo.
     */
    bool echo;

public:

    /**
     * Public constructor.
     * 
     * @param serial
     */
    SIM900(unsigned char receivePin, unsigned char transmitPin);

    /**
     * Initializes the device.
     * 
     * @param           The bound rate to be used.
     */
    void begin(long bound);

    /**
     * Get a pointer to the last response.
     * 
     * @return 
     */
    unsigned char *getLastResponse() {
        rxPointer = &rxBuffer[0];
        return rxPointer;
    }

    /**
     * Sends a command expecting some result.
     * 
     * @param command           The command string, should be \0 ended.
     * @param expectation       The expectation string.
     * @param timeout           The maximum time to perform the op.
     * @return 
     */
    bool sendCommandExpecting(char *command, char *expectation, bool append, unsigned long timeout);

    /**
     * Sends a command expecting some result.
     * 
     * DEFAULT TIMEOUT
     * 
     * @param command           The command string, should be \0 ended.
     * @param expectation       The expectation string.
     * @return 
     */
    inline bool sendCommandExpecting(const char *command, char *expectation, bool append) {
        return sendCommandExpecting(command, expectation, append, 1000);
    }

    /**
     * Sends a command expecting some result.
     * 
     * DEFAULT APPEND
     * 
     * @param command           The command string, should be \0 ended.
     * @param expectation       The expectation string.
     * @return 
     */
    inline bool sendCommandExpecting(const char *command, char *expectation, unsigned long timeout) {
        return sendCommandExpecting(command, expectation, false, timeout);
    }

    /**
     * Sends a command expecting some result.
     * 
     * DEFAULT TIMEOUT
     * DEFAULT APPEND
     * 
     * @param command           The command string, should be \0 ended.
     * @param expectation       The expectation string.
     * @return 
     */
    inline bool sendCommandExpecting(const char *command, char *expectation) {
        return sendCommandExpecting(command, expectation, (bool) false);
    }

    /**
     * Checks if the last response contains the given sub-string.
     * 
     * @param expectation       The expectation string.
     * @return 
     */
    bool doesResponseContains(char *expectation);

    /**
     * Sends a command to the device.
     * 
     * @param command           The command string, should be \0 ended.
     * @param timeout           The maximum time to perform the op.
     * @return 
     */
    int sendCommand(const char **command, bool append, unsigned long timeout);

    /**
     * Sends a command to the device.
     * 
     * DEFAULT TIMEOUT
     * 
     * @param command           The command string, should be \0 ended.
     * @param append            Boolean saying if the AT must be appended.
     * @return 
     */
    inline int sendCommand(const char **command, bool append) {
        return sendCommand(command, append, 1000);
    }

    /**
     * Sends a command to the device.
     * 
     * DEFAULT APPEND
     * 
     * @param command           The command string, should be \0 ended.
     * @param append            Boolean saying if the AT must be appended.
     * @return 
     */
    inline int sendCommand(const char **command, unsigned long timeout) {
        return sendCommand(command, (bool) false, timeout);
    }

    /**
     * Sends a command to the device.
     * 
     * DEFAULT TIMEOUT
     * DEFAULT APPEND
     * 
     * @param command           The command string, should be \0 ended.
     * @return 
     */
    inline int sendCommand(const char **command) {
        return sendCommand(command, (bool) false);
    }

    /**
     * Reads the response from the device.
     * 
     * @param timeout           The maximum time to perform the op.
     * @return                  How many bytes was received. 0 if timeout.
     */
    int readResponse(unsigned long timeout);

    /**
     * Configures echo mode
     * 
     * @param echo
     */
    void setCommandEcho(bool echo);
};

#endif /* __ARDUINO_DRIVER_GSM_SIM900_H__ */