/**
 * Arduino - Gsm driver
 * 
 * Interface to phonebook.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_GSM_PHONEBOOK_H__
#define __ARDUINO_DRIVER_GSM_PHONEBOOK_H__ 1

class Phonebook {
    
public:

    /**
    * Find Phonebook Entries
    * 
    * @return
    */
    virtual unsigned char findEntries() = 0;

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

    /**
     * Set number of rings before automatically answering the call
     *
     * @param rings Number of rings before automatically answering. 0 means disable.
     * @return 0 if error, > 0 otherwise.
     */
    virtual unsigned char setAutomaticallyAnswering(unsigned char rings) = 0;
};

#endif /* __ARDUINO_DRIVER_GSM_PHONEBOOK_H__ */
