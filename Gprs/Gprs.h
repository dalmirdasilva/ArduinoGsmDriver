/**
 * Arduino - Gsm driver
 * 
 * Gprs.h
 * 
 * Interface to calls.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_GSM_GPRS_H__
#define __ARDUINO_DRIVER_GSM_GPRS_H__ 1

class Gprs {
    
public:

    /**
     * Start Up Multi-IP Connection 
     * 
     * Enable or disable multi IP connection.
     * 
     * @param use           0 disables multi IP connection and 1 enables.
     * @return
     */
    virtual unsigned char useMultiplexer(bool use) = 0;

    /**
     * Start Task and Set APN, LOGIN, PASSWORD
     * 
     * Each param must be \0 teminated.
     * 
     * @param apn           The apn access point name.
     * @param login         The GPRS user name.
     * @param password      The GPRS password.
     * @return
     */
    virtual unsigned char startTask(unsigned char *apn, unsigned char *login, unsigned char *password) = 0;

    /**
     * Bring Up Wireless Connection with GPRS or CSD
     * 
     * Connects to the GPRS network.
     * 
     * @return 
     */
    virtual unsigned char bringUp() = 0;

    /**
     * Get Local IP Address
     * 
     * Returns the the IP address assigned from GPRS or CSD in 4
     * bytes format.
     * 
     * @param entry         Phonebook entry.
     * @return 
     */
    virtual unsigned char getAddress(unsigned char *buf) = 0;

    /**
     * Query Current Connection Status
     * 
     * @return 
     */
    virtual unsigned char status() = 0;

    /**
     * Configure Domain Name Server
     * 
     * @return 
     */
    virtual unsigned char configureDns(unsigned char *primary, unsigned char *secondary) = 0;

    /**
     * Start Up TCP or UDP Connection
     * 
     * @return 
     */
    virtual unsigned char start(unsigned char mode, unsigned char *address, unsigned char port) = 0;

    /**
     * Start Up TCP or UDP Connection
     * 
     * @return 
     */
    virtual unsigned char start(unsigned char connection, unsigned char mode, unsigned char *address, unsigned char port) = 0;

    /**
     * Close TCP or UDP Connection
     * 
     * @return 
     */
    virtual unsigned char close(unsigned char connection) = 0;

    /**
     * Query the IP Address of Given Domain Name
     * 
     * @return 
     */
    virtual unsigned char resolve(unsigned char *name, unsigned char *buf, unsigned int len) = 0;

    /**
     * Send Data Through TCP or UDP Connection
     * 
     * @return 
     */
    virtual unsigned char send(unsigned char *buf) = 0;

    /**
     * Send Data Through TCP or UDP Connection
     * 
     * @return 
     */
    virtual unsigned char send(unsigned char connection, unsigned char *buf, unsigned int len) = 0;
    
    /**
     * Configure Module as Server
     * 
     * @return 
     */
    virtual unsigned char setUpServer(unsigned char mode, unsigned int port) = 0;


    /**
     * Deactivate GPRS PDP Context
     * 
     * @return 
     */
    virtual unsigned char shutdown() = 0;
};

#endif /* __ARDUINO_DRIVER_GSM_GPRS_H__ */
