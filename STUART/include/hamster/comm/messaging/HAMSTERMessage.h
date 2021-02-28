/*
 * Copyright (C) 2017     Critical Embedded System Laboratory (LSEC)
 * 
 * This program is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * See the GNU Lesser General Public License for more details.
 * <http://www.gnu.org/licenses/>
 */

/*!
 * \if DESIGN_MODEL
 * 
 *  \anchor HAMSTERMessage
 *  \class hamster::comm::HAMSTERQueue HAMSTERMessage.h
 *  \brief Class to enable message exchange between HAMSTER Units.
 *  \details HAMSTER Messages have a predefined structure, whith a message code 
 *  and the message payload. To see HAMSTER Messages, refer to \ref "HAMSTER 
 *  Messages" HAMSTERMessages.
 * 
 *  \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 *  \copyright GNU Lesser General Public License.
 * 
 *  \endif
 */

#ifndef HAMSTERMESSAGE_H
#define HAMSTERMESSAGE_H

#include "stdio.h"
#include "HAMSTER.h"
#include "HAMSTER_MESSAGE_CODE.h"
#include "HAMSTERPeer.h"

namespace hamster{
namespace comm{
namespace messaging{
/*! \namespace messaging */
    
class MessageField;
    
#define MAX_BUFFER_SIZE 2000

enum HAMSTER_MESSAGE_DIRECTION : uint8_t{
    INTERNAL,
    EXTERNAL
};

class HAMSTERMessage {
public:
    HAMSTERMessage(HAMSTER_MESSAGE_DIRECTION dir,HAMSTER_MESSAGE_CODE code);
    HAMSTERMessage(HAMSTER_MESSAGE_DIRECTION dir,char * buffer,int size);
    HAMSTERMessage(HAMSTER_MESSAGE_DIRECTION dir,HAMSTER_MESSAGE_CODE code, int buffer_size);
    HAMSTERMessage(HAMSTER_MESSAGE_DIRECTION dir, char * payload, HAMSTER_MESSAGE_CODE code, uint16_t size, comm::HAMSTERPeer * peer);
    HAMSTERMessage(const HAMSTERMessage& orig);
    virtual ~HAMSTERMessage();
    
    HAMSTER_RETURN addInt8ToPayload(int8_t value);
//    HAMSTER_RETURN addToPayload(uint8_t value);
    HAMSTER_RETURN addToPayload(char * string);
    HAMSTER_RETURN copyToPayload(char * buffer, int size);
    int extractInt8FromPayload(uint8_t * value);
    void extractCode(void);
    void extractSize(void);
    void rewind(void);
    char * extractStringFromPayload();
    char * getUserMessage();
    
    HAMSTER_MESSAGE_CODE getCode() const {
        return message_code;
    }

    HAMSTERPeer * getRecipient() const {
        return recipient;
    }
    
    char* getMessagePayload() const {
        return message_payload;
    }

    uint16_t getMessageSize() const {
        return message_size;
    }


    void setRecipient(HAMSTERPeer* recipient) {
        this->recipient = recipient;
    }
    
    HAMSTER_MESSAGE_DIRECTION getDirection(){
        return this->direction;
    }
    
    uint8_t getHeader(){
        uint32_t code = ((this->message_code & 0xFF000000) >> 24);
        return (uint8_t) (code & 0xFF);
    }

    inline std::ostream& operator<<(std::ostream& stream) {
        stream << "Code: " << (int) this->message_code << std::endl;
        stream << "Recipient ID: " << this->recipient->GetID() << std::endl;
        return stream;
    }
    
    void destroyBuffer(){
//        logVerboseMessage("HAMSTERMessage destroyBuffer.");
//        if(this->message_payload != NULL){
//            logVerboseMessage("payload != NULL, = ",this->message_payload);
//            delete this->message_payload;
//            logVerboseMessage("message payload deleted");
//            this->message_payload = NULL;
//            logVerboseMessage("MessagePayload reset");
//        }
//        logVerboseMessage("HAMSTERMessage Buffer destroyed.");
    }
    
    void switchToInternal(){
        this->direction = HAMSTER_MESSAGE_DIRECTION::INTERNAL;
    }
    
    int pullMessageField(MessageField * field);
    void pushMessageField(MessageField * field);
    
    static int pushInt8IntoPayload(char ** buffer, uint8_t value);
    static int pullInt8FromPalyload(char * buffer, uint8_t * value);
    
    
    void printPayload(){
        printf("Message Payload:\n");
        for (int i = 0; i < this->message_size; i++) {
            printf("%c",this->message_payload[i]);
        }
        printf("\n");
    }
    
    void rewritePayload(char * new_payload,int size){
        memset(message_payload,0,MAX_BUFFER_SIZE);
        memcpy(message_payload,new_payload,size);
    }
    
private:
    static uint8_t const header_size = 12;
    uint8_t remainingSize();
    HAMSTER_RETURN updateSize();
    
    HAMSTER_MESSAGE_CODE message_code;
    HAMSTER_MESSAGE_DIRECTION direction;
    uint16_t message_payload_size;
    uint16_t message_size = 0;
    uint8_t message_buffer_index = 0;
    char * message_payload = NULL;
    HAMSTERPeer * recipient;

};


} /* namesapce messaging */
} /* namespace comm */
} /* namespace hamster */

#endif /* HAMSTERMESSAGE_H */

