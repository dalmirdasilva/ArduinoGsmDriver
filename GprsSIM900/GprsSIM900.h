/**
 * Arduino - Gsm driver
 * 
 * GprsSIM900.h
 * 
 * GPRS connection using SIM900.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_GSM_GPRS_SIM900_H__
#define __ARDUINO_DRIVER_GSM_GPRS_SIM900_H__ 1

#define GPRS_SIM900_MAX_COMMAND_LENGHT 64

#include <Gprs.h>
#include <SIM900.h>
#include <stdlib.h>

class GprsSIM900 : public Gprs {
    
    /**
     * SIM900 pointer.
     */
    SIM900 *sim;
    
    /**
     * Multi connection.
     */
    bool multiconnection;
    
public:
    
    enum OperationResult {
        OK = 0,
        ERROR = 1,
        COMMAND_TOO_LONG = 2
    };
    
    /**
     * Public constructor.
     * 
     * @param sim       The SIM900 pointer.
     */
    GprsSIM900(SIM900 *sim);

    /**
     * Initializes the device.
     * 
     * @param           The bound rate to be used.
     */
    void begin(int bound);

    /**
     * Start Up Multi-IP Connection 
     * 
     * Enable or disable multi IP connection.
     * 
     * @param use           0 disables multi IP connection and 1 enables.
     * @return
     */
    unsigned char useMultiplexer(bool use);

    /**
     * Start Task and Set APN, LOGIN, PASSWORD
     * 
     * Each parameter must be \0 teminated.
     * 
     * @param apn           The apn access point name.
     * @param login         The GPRS user name.
     * @param password      The GPRS password.
     * @return
     */
    unsigned char startTask(unsigned char *apn, unsigned char *login, unsigned char *password);

    /**
     * Bring Up Wireless Connection with GPRS or CSD
     * 
     * Connects to the GPRS network.
     * 
     * @return 
     */
    unsigned char bringUp();

    /**
     * Get Local IP Address
     * 
     * Returns the the IP address assigned from GPRS or CSD in 4
     * bytes format.
     * 
     * @param entry         Phonebook entry.
     * @return 
     */
    unsigned char obtainIp(unsigned char *buf);

    /**
     * Query Current Connection Status
     * 
     * @return 
     */
    unsigned char status();

    /**
     * Configure Domain Name Server
     * 
     * @return 
     */
    unsigned char configureDns(unsigned char *primary, unsigned char *secondary);

    /**
     * Start Up TCP or UDP Connection
     * 
     * @return 
     */
    unsigned char open(unsigned char mode, unsigned char *address, unsigned char port);

    /**
     * Start Up TCP or UDP Connection
     * 
     * @return 
     */
    unsigned char open(unsigned char connection, unsigned char mode, unsigned char *address, unsigned char port);

    /**
     * Close TCP or UDP Connection
     * 
     * @return 
     */
    unsigned char close(unsigned char connection);

    /**
     * Query the IP Address of Given Domain Name
     * 
     * @return 
     */
    unsigned char resolve(unsigned char *name, unsigned char *buf, unsigned int len);

    /**
     * Send Data Through TCP or UDP Connection
     * 
     * @return 
     */
    unsigned char send(unsigned char *buf, unsigned int len);

    /**
     * Send Data Through TCP or UDP Connection
     * 
     * @return 
     */
    unsigned char send(unsigned char connection, unsigned char *buf, unsigned int len);
    
    /**
     * Configure Module as Server
     * 
     * @return 
     */
    unsigned char setUpServer(unsigned char mode, unsigned int port);

    /**
     * Deactivate GPRS PDP Context
     * 
     * @return 
     */
    unsigned char shutdown();
};

#endif /* __ARDUINO_DRIVER_GSM_GPRS_SIM900_H__ */
