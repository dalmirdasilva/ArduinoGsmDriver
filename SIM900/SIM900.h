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

//#include <SoftwareSerial.h>

class SIM900 {
    
    const char atCommands[] = "one\0asdasd\0asdasd\0dadasdasd\0";
    
    enum Command {
        
    }

public:
    
    void sendCommand();
    
    unsigned char write(unsigned char *buf, unsigned char len);

    unsigned char read(unsigned char *buf, unsigned char len);
};

#endif /* __ARDUINO_DRIVER_GSM_SIM900_H__ */