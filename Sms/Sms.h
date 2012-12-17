/**
 * Arduino - Gsm driver
 * 
 * Sms.h
 * 
 * Interface to calls.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_GSM_SMS_H__
#define __ARDUINO_DRIVER_GSM_SMS_H__ 1

class Sms {
    
public:

    /**
     * Delete SMS Message
     * 
     * 
     * @param index             Message location.
     * @param flags             Deletion flags.
     * @return 
     */
    virtual unsigned char remove(unsigned char index, unsigned char flags) = 0;

    /**
     * Select SMS Message Format
     * 
     * @param format            Message format.
     * @return 
     */
    virtual unsigned char format(bool format) = 0;

    /**
     * Bring Up Wireless Connection with Sms or CSD
     * 
     * Connects to the Sms network.
     * 
     * @return 
     */
    virtual unsigned char bringUp() = 0;

    /**
     * Get Local IP Address
     * 
     * Returns the the IP address assigned from Sms or CSD in 4
     * bytes format.
     * 
     * @param entry         Phonebook entry.
     * @return 
     */
    virtual unsigned char obtainIp(unsigned char *buf) = 0;

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
    virtual unsigned char open(unsigned char mode, unsigned char *address, unsigned char port) = 0;

    /**
     * Start Up TCP or UDP Connection
     * 
     * @return 
     */
    virtual unsigned char open(unsigned char connection, unsigned char mode, unsigned char *address, unsigned char port) = 0;

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
     * Deactivate Sms PDP Context
     * 
     * @return 
     */
    virtual unsigned char shutdown() = 0;
};

#endif /* __ARDUINO_DRIVER_GSM_SMS_H__ */
