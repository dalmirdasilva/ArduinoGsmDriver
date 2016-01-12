/**
 * Arduino - Gsm driver
 * 
 * GprsSIM900.h
 * 
 * GPRS connection using SIM900.
 * 
 * Steps to connect to the GPRS net and issue a get request.
 *
 * <ul>
 *  <li>call init</li>
 *  <li>call useMultiplexer</li>
 *  <li>call attach</li>
 *  <li>call bringUp</li>
 *  <li>call obtainIp</li>
 *  <li>configureDns("8.8.8.8", "8.8.4.4")</li>
 * </ul>
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
    bool multiplexed;
    
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
     * @return          > 0 if success, 0 otherwise.
     */
    unsigned char begin(long bound);

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
    unsigned char attach(const char *apn, const char *login, const char *password);

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
    unsigned char configureDns(const char *primary, const char *secondary);

    /**
     * Start Up TCP or UDP Connection
     * 
     * @return 
     */
    unsigned char open(const char *mode, const char *address, unsigned int port);

    /**
     * Start Up TCP or UDP Connection
     * 
     * @return 
     */
    unsigned char open(char connection, const char *mode, const char *address, unsigned int port);

    /**
     * Close TCP or UDP Connection
     * 
     * @param connection
     * @return 
     */
    unsigned char close(char connection);

    /**
     * Close TCP or UDP Connection
     * 
     * @return 
     */
    unsigned char close();

    /**
     * Query the IP Address of Given Domain Name
     * 
     * @return 
     */
    unsigned char resolve(const char *name, unsigned char *buf, unsigned int len);

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
    unsigned char send(char connection, unsigned char *buf, unsigned int len);
    
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
