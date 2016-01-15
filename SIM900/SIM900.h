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

#include <Arduino.h>
#include <string.h>
#include <SoftwareSerial.h>

#define SIM900_RX_BUFFER_SIZE 256

#define SIM900_DEFAULT_COMMAND_RESPONSE_TIMEOUT 500UL
#define SIM900_INITIALIZATION_TIMEOUT           10000UL

class SIM900: public SoftwareSerial {

    /**
     * RX buffer.
     */
    unsigned char rxBuffer[SIM900_RX_BUFFER_SIZE];

    /**
     * RX buffer position.
     */
    unsigned int rxBufferPos;

    /**
     * Using echo.
     */
    bool echo;

    /**
     * Soft reset pin.
     */
    unsigned char resetPin;

    /**
     * Soft power on/off pin.
     */
    unsigned char powerPin;

    /**
     * Bool indicating the last command's response was fully read by
     * readResponse method.
     */
    bool responseFullyRead;

    /**
     * Enable soft power and reset
     */
    bool softResetAndPowerEnabled;

public:

    enum DisconnectParamter {

        // Disconnect ALL calls on the channel the command is
        // requested. All active or waiting calls, CS data calls, GPRS call
        // of the channel will be disconnected
        ALL_CALLS_ON_CHANNEL = 0,

        // Disconnect all calls on ALL connected channels. All active or
        // waiting calls, CSD calls, GPRS call will be disconnected.
        // (clean up of all calls of the ME)
        ALL_CALL_ON_ALL_CHANNELS = 1,

        // Disconnect all connected CS data call only on the channel
        // the command is requested. (speech calls (active or waiting)
        // or GPRS calls are not disconnected)
        ALL_CS_ON_CHANNEL = 2,

        // Disconnect all connected GPRS calls only on the channel
        // the command is requested (speech calls (active or waiting)
        // or CS data calls are not disconnected.
        ALL_GPRS_ON_CHANNEL = 3,

        // Disconnect all CS calls (either speech or data) but does not
        // disconnect waiting call (either speech or data) on the
        // channel the command is requested.
        ALL_BUT_WAITING_ON_CHANNEL = 4,

        // Disconnect waiting call (either speech or data) but does not
        // disconnect other active calls (either CS speech, CS data or
        // GPRS) on the channel the command is requested.
        // (rejection of incoming call)
        ALL_WAITING_ON_CHANNEL = 5
    };

    /**
     * Public constructor.
     * 
     * @param serial
     */
    SIM900(unsigned char receivePin, unsigned char transmitPin);

    /**
     * Public constructor.
     *
     * @param serial
     */
    SIM900(unsigned char receivePin, unsigned char transmitPin, unsigned char resetPin, unsigned char powerPin);

    /**
     * Virtual destructor.
     */
    virtual ~SIM900();

    /**
     * Initializes the device.
     * 
     * @param           The bound rate to be used.
     * @return          0 if not success, > 0 otherwise.
     */
    unsigned char begin(long bound);

    /**
     * Soft controlled Reset
     */
    void softReset();

    /**
     * Soft controlled Power on/off
     */
    void softPower();

    /**
     * Get a pointer to the last response.
     * 
     * @return 
     */
    unsigned char *getLastResponse() {
        return &rxBuffer[0];
    }

    /**
     * Sends a command expecting some result.
     * 
     * @param command           The command string, should be \0 ended.
     * @param expectation       The expectation string.
     * @param timeout           The maximum time to perform the op.
     * @return 
     */
    bool sendCommandExpecting(const char *command, const char *expectation, bool append, unsigned long timeout);

    /**
     * Sends a command expecting some result.
     * 
     * @param   command             The command string, should be \0 ended.
     * @param   expectation         The expectation string.
     * @param   append              If should append AT+ in the command.
     * @return 
     */
    inline bool sendCommandExpecting(const char *command, const char *expectation, bool append) {
        return sendCommandExpecting(command, expectation, append, SIM900_DEFAULT_COMMAND_RESPONSE_TIMEOUT);
    }

    /**
     * Sends a command expecting some result.
     * 
     * @param   command             The command string, should be \0 ended.
     * @param   expectation         The expectation string.
     * @param   timeout             Timeout.
     * @return 
     */
    inline bool sendCommandExpecting(const char *command, const char *expectation, unsigned long timeout) {
        return sendCommandExpecting(command, expectation, false, timeout);
    }

    /**
     * Sends a command expecting some result.
     * 
     * @param command           The command string, should be \0 ended.
     * @param expectation       The expectation string.
     * @return 
     */
    inline bool sendCommandExpecting(const char *command, const char *expectation) {
        return sendCommandExpecting(command, expectation, (bool) false);
    }

    /**
     * Checks if the last response contains the given sub-string.
     * 
     * @param expectation       The expectation string.
     * @return 
     */
    bool doesResponseContains(const char *expectation);

    /**
     * Sends a command to the device.
     * 
     * @param command           The command string, should be \0 ended.
     * @param timeout           The maximum time to perform the op.
     * @return 
     */
    unsigned int sendCommand(const char *command, bool append, unsigned long timeout);

    /**
     * Sends a command to the device.
     * 
     * @param command           The command string, should be \0 ended.
     * @param append            Boolean saying if the AT must be appended.
     * @return 
     */
    inline unsigned int sendCommand(const char *command, bool append) {
        return sendCommand(command, append, 1000);
    }

    /**
     * Sends a command to the device.
     * 
     * @param command           The command string, should be \0 ended.
     * @param append            Boolean saying if the AT must be appended.
     * @return 
     */
    inline unsigned int sendCommand(const char *command, unsigned long timeout) {
        return sendCommand(command, (bool) false, timeout);
    }

    /**
     * Sends a command to the device.
     * 
     * @param command           The command string, should be \0 ended.
     * @return 
     */
    inline unsigned int sendCommand(const char *command) {
        return sendCommand(command, (bool) false);
    }

    /**
     * Sends a command to the device.
     */
    inline unsigned int sendCommand() {
        return sendCommand("");
    }

    /**
     * Reads the response from the device.
     * 
     * @param timeout           The maximum time to perform the op.
     * @return                  How many bytes was received. 0 if timeout.
     */
    inline unsigned int readResponse(unsigned long timeout) {
        return readResponse(timeout, false);
    }

    /**
     * Reads the response from the device.
     *
     * @param timeout           The maximum time to perform the op.
     * @param append            Append the response in the internal buffer.
     * @return                  How many bytes was received. 0 if timeout.
     */
    unsigned int readResponse(unsigned long timeout, bool append);

    /**
     * Configures echo mode
     * 
     * @param echo
     */
    void setCommandEcho(bool echo);

    unsigned char disconnect(DisconnectParamter param);

    /**
     * Checks if the rx is fully read.
     *
     * If false, a new call to readResponse will read more data from tx
     * placing the new data over the current data in it. Consecutive calls to
     * readResponse will write data into the same buffer.
     *
     * use getLastResponse to consume the current data and then call readResponse again
     * in case tx was not fully read.
     */
    bool wasResponseFullyRead();

    /**
     * Searches the response for a given string.
     *
     * @param   str     The string to be searched inside response
     * @return          The pointer to the first found string, NULL if not found
     */
    const char *findInResponse(const char *str);

    /**
     * Keeps reading the response until finds the str or timeout.
     *
     * @param   str         String it tries to find
     * @param   timeout     Timeout in millis
     * @return              The position to the first char it finds in the internal buffer, -1 otherwise
     */
    int waitUntilReceive(const char *str, unsigned int timeout);

    /**
     * Discards the internal buffer.
     */
    void discardBuffer();

    /*
     void getProductIdentificationInformation();

     void setMonitorSpeakerLoudness();

     void setMonitorSpeakerMode();
     */
};

#endif /* __ARDUINO_DRIVER_GSM_SIM900_H__ */
