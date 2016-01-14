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

#define GPRS_SIM900_MAX_COMMAND_LENGHT  64
#define GPRS_SIM900_CDNSGIP_TIMEOUT     5000
#define GPRS_SIM900_CIICR_TIMEOUT       10000
#define GPRS_SIM900_CIPSTART_TIMEOUT    5000
#define GPRS_SIM900_SEND_TIMEOUT        10000

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
    
    enum DnsResolution {
        NOT_AUTHORIZATION = 0,
        INVALID_PARAMTER = 1,
        NETWORK_ERROR = 2,
        NO_SERVER = 3,
        TIMEOUT = 4,
        NO_CONFIGURATION = 5,
        NO_MEMORY = 6,
        SUCCESS = 0xff
    };

    /**
     * Public constructor.
     * 
     * @param sim       The SIM900 pointer.
     */
    GprsSIM900(SIM900 *sim);

    virtual ~GprsSIM900() {}

    /**
     * Initializes the device.
     * 
     * Example:
     * > AT+CIPSHUT
     * < SHUT OK
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
     * Example:
     * > +CIPMUX=0|1
     * < OK
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
     * Example:
     * > AT+CSTT="tim.br","tim","tim"
     * < OK
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
     * Example:
     * > AT+CIICR
     * < OK
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
     * Example:
     * > AT+CIFSR
     * < OK
     * <
     * < 100.83.135.48
     *
     * @param entry         Phonebook entry.
     * @return 
     */
    unsigned char obtainIp(unsigned char ip[4]);

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
     * Example:
     * > AT+CIPSTART="TCP","184.73.238.232", "80"
     * < OK
     * <
     * < CONNECT OK
     *
     * @param   connection  If multi-IP connection (+CIPMUX=1)
     *                      0..7 A numeric parameter which indicates the connection number
     * @param   mode        A string parameter(string should be included in quotation
     *                      marks) which indicates the connection type
     *                      "TCP" Establish a TCP connection
     *                      "UDP" Establish a UDP connection
     * @param   address     A string parameter(string should be included in quotation
     *                      marks) which indicates remote server IP address
     * @param   port        Remote server port
     * @return              OperationResult
     */
    unsigned char open(char connection, const char *mode, const char *address, unsigned int port);

    /**
     * Send Data Through TCP or UDP Connection
     *
     * Example:
     * > AT+CIPSEND= <0-7>,<length>
     * < >
     * > data
     * DATA ACCEPT:<length>
     *
     * @return
     */
    unsigned int send(unsigned char *buf, unsigned int len);

    /**
     * Send Data Through TCP or UDP Connection
     *
     * @return
     */
    unsigned int send(char connection, unsigned char *buf, unsigned int len);

    /**
     * Close TCP or UDP Connection
     * 
     * Example:
     * > AT+CIPCLOSE=1[,connection]
     * < CLOSE OK
     *
     * @param   connection  If multi-IP connection (+CIPMUX=1)
     *                      0..7 A numeric parameter which indicates the connection number
     * @return              OperationResult
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
     * Example:
     * > AT+CDNSGIP="www.google.com"
     * < OK
     * <
     * < +CDNSGIP: 1,"www.google.com","64.233.186.99"
     *
     * @return  DnsResolution
     * @param   name    Domain name. Should contains less than 256 bytes
     * @param   ip      4-byte-long array where the ip will be placed
     */
    unsigned char resolve(const char *name, unsigned char ip[4]);
    
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

    /**
     * Tries to parse an IP from string.
     *
     * @param           buf should have the following format: [0-9]{1,4}.[0-9]{1,4}.[0-9]{1,4}.[0-9]{1,4}
     * @param           ip  whre to store the parsed ip, 4 bytes.
     */
    unsigned char static parseIp(const char *buf, unsigned char ip[4]);
};

#endif /* __ARDUINO_DRIVER_GSM_GPRS_SIM900_H__ */
