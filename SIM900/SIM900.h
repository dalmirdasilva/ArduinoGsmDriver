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
#include <SoftwareSerialAttentionDevice.h>
#include <string.h>

#define SIM900_INITIALIZATION_TIMEOUT           10000UL

class SIM900: public SoftwareSerialAttentionDevice {

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
     * Configures echo mode
     * 
     * @param echo
     */
    void setEcho(bool echo);

    unsigned char disconnect(DisconnectParamter param);

    /*
     void getProductIdentificationInformation();

     void setMonitorSpeakerLoudness();

     void setMonitorSpeakerMode();
     */
};

#endif /* __ARDUINO_DRIVER_GSM_SIM900_H__ */
