/**
 * Arduino - Gsm driver
 * 
 * Call.h
 * 
 * Interface to calls.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_GSM_CALL_H__
#define __ARDUINO_DRIVER_GSM_CALL_H__ 1

class Call {
    
public:

    /**
    * Answer an Incoming Call
    * 
    * TA sends off-hook to the remote station.
    * 
    * @return
    */
    virtual unsigned char answer() = 0;

    /**
    * Mobile Originated Call to Dial A Number
    * 
    * This Command can be used to set up outgoing voice, data or fax calls. 
    * It also serves to control supplementary services.
    * 
    * @param number        The number to make the call to.
    * @return
    */
    virtual unsigned char callNumber(unsigned char *number) = 0;

    /**
    * Originate Call to Phone Number in Current Memory
    * 
    * This Command can be used to dial a phone number from current phonebook.
    * 
    * @param position      Phonebook position.
    * @return 
    */
    virtual unsigned char callFromPhonebook(unsigned char position) = 0;

    /**
    * Originate Call to Phone Number in Memory Which Corresponds to Field
    * 
    * This Command make the TA attempts to set up an outgoing call to stored 
    * number which has the name matching with the entry string.
    * 
    * @param entry         Phonebook entry.
    * @return 
    */
    virtual unsigned char callByPhonebookMatch(unsigned char *entry) = 0;

    /**
    * Redial Last Telephone Number Used
    * 
    * This Command redials the last voice and data call number used.
    * 
    * @return 
    */
    virtual unsigned char redial() = 0;

    /**
    * Disconnect Existing Connection
    * 
    * @return 
    */
    virtual unsigned char disconnect() = 0;
};

#endif /* __ARDUINO_DRIVER_GSM_CALL_H__ */