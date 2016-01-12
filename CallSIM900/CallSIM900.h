/**
 * Arduino - Gsm driver
 * 
 * CallSIM900.h
 * 
 * Interface to calls.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_GSM_CALL_SIM900_H__
#define __ARDUINO_DRIVER_GSM_CALL_SIM900_H__ 1

#include <SIM900.h>
#include <Call.h>

class CallSIM900 : public Call {

    SIM900 *sim;

public:

    enum CallResponse {

        // Success
        OK = 0,

        // If error is related to ME functionality
        CME_ERROR = 1,

        // If no dial tone and (parameter setting ATX2 or ATX4)
        NO_DIALTONE = 2,

        // If busy and (parameter setting ATX3 or ATX4)
        BUSY = 3,

        // If a connection cannot be established
        NO_CARRIER = 4,

        // If the remote station does not answer
        NO_ANSWER = 5,

        // If connection successful and non-voice call.
        // CONNECT<text> TA switches to data mode.
        // Note: <text> output only if ATX<value> parameter setting with the
        // <value> >0
        CONNECT_TEXT = 6
    };

    CallSIM900(SIM900 *sim);

    virtual ~CallSIM900();

    /**
     * Answer an Incoming Call
     * 
     * TA sends off-hook to the remote station.
     * 
     * @return
     */
    unsigned char answer();

    /**
     * Mobile Originated Call to Dial A Number
     * 
     * This Command can be used to set up outgoing voice, data or fax calls. 
     * It also serves to control supplementary services.
     * 
     * @param number        The number to make the call to.
     * @return
     */
    unsigned char callNumber(unsigned char *number);

    /**
     * Originate Call to Phone Number in Current Memory
     * 
     * This Command can be used to dial a phone number from current phonebook.
     * 
     * @param position      Phonebook position.
     * @return 
     */
    unsigned char callFromPhonebook(unsigned char position);

    /**
     * Originate Call to Phone Number in Memory Which Corresponds to Field
     * 
     * This Command make the TA attempts to set up an outgoing call to stored 
     * number which has the name matching with the entry string.
     * 
     * @param entry         Phonebook entry.
     * @return 
     */
    unsigned char callByPhonebookMatch(unsigned char *entry);

    /**
     * Redial Last Telephone Number Used
     * 
     * This Command redials the last voice and data call number used.
     * 
     * @return 
     */
    unsigned char redial();

    /**
     * Disconnect Existing Connection
     * 
     * @return 
     */
    unsigned char disconnect();

    /**
     * Set number of rings before automatically answering the call
     *
     * @param rings Number of rings before automatically answering. 0 means disable.
     * @return 0 if error, > 0 otherwise.
     */
    unsigned char setAutomaticallyAnswering(unsigned char rings);

    /**
     * Check call response.
     */
    unsigned char checkResponse();
};

#endif /* __ARDUINO_DRIVER_GSM_CALL_SIM900_H__ */
