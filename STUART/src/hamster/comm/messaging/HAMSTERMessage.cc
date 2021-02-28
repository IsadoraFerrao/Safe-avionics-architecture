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

/* 
 * \file    HAMSTERMessage.cc
 * \author: Mariana Rodrigues   rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#include <cstring>

#include "HAMSTERMessage.h"
#include "MessageField.h"

namespace hamster{
namespace comm{
namespace messaging{
    

HAMSTERMessage::HAMSTERMessage(messaging::HAMSTER_MESSAGE_DIRECTION dir,HAMSTER_MESSAGE_CODE code):direction(dir),message_code(code) {
    this->message_payload = new char[MAX_BUFFER_SIZE];
    sprintf((char *) &(this->message_payload[message_buffer_index]),"%08x",(uint32_t) code);
    message_payload_size = 0;
    this->message_buffer_index += 12;
    message_payload[message_buffer_index] = '\0';
    this->updateSize();
}

HAMSTERMessage::HAMSTERMessage(messaging::HAMSTER_MESSAGE_DIRECTION dir,char * buffer, int size):direction(dir){
    this->message_payload = buffer;
    this->message_size = size;
    this->extractCode();
    this->extractSize();
}

HAMSTERMessage::HAMSTERMessage(messaging::HAMSTER_MESSAGE_DIRECTION dir,HAMSTER_MESSAGE_CODE code, int buffer_size):direction(dir),message_code(code) {
    this->message_payload = new char[buffer_size];
    sprintf((char *) &(this->message_payload[message_buffer_index]),"%08x",(uint32_t) code);
    message_payload_size = 0;
    this->updateSize();
    this->message_buffer_index += 12;
    message_payload[message_buffer_index] = '\0';
}

HAMSTERMessage::HAMSTERMessage(
    messaging::HAMSTER_MESSAGE_DIRECTION dir,
    char * payload, 
    HAMSTER_MESSAGE_CODE code,
    uint16_t size,
    HAMSTERPeer * peer):
    direction(dir),message_payload(payload),message_code(code), message_size(size),recipient(peer){
    this->message_payload_size = size - header_size;
}

HAMSTERMessage::HAMSTERMessage(const HAMSTERMessage& orig) {
    this->direction = orig.direction;
    this->message_payload = orig.message_payload;
    this->message_buffer_index = orig.message_buffer_index;
    this->message_code= orig.message_code;
    this->message_payload_size = orig.message_payload_size;
    this->message_size = orig.message_size;
    this->recipient = orig.recipient;
}

HAMSTERMessage::~HAMSTERMessage() {
    this->destroyBuffer();
}

int HAMSTERMessage::pullMessageField(MessageField * field){
    int bytes_used = field->pullFromPayload(&(this->message_payload[message_buffer_index]));
    message_buffer_index += bytes_used;
    return bytes_used;
}

void HAMSTERMessage::pushMessageField(MessageField * field){
    char * buffer = new char[MAX_BUFFER_SIZE];
    int size = field->pushInPayload(&buffer);
    this->copyToPayload(buffer,size);
    delete buffer;
}

uint8_t HAMSTERMessage::remainingSize(){
    return (sizeof(this->message_payload) - this->message_buffer_index);
}

HAMSTER_RETURN HAMSTERMessage::addInt8ToPayload(int8_t value){
    if(remainingSize() >= 2){
        // Serialize value in hexa
        sprintf((char *) &(this->message_payload[message_buffer_index]),"%02x",value);
        message_buffer_index += 2;
        message_payload_size += 2;
        this->updateSize();
        return HAMSTER_RETURN::RETURN_OK;
    }
    return HAMSTER_RETURN::RETURN_NOK;
}
//HAMSTER_RETURN HAMSTERMessage::addToPayload(uint32_t value){
//
//}
HAMSTER_RETURN HAMSTERMessage::addToPayload(char * string){
    uint8_t size = strlen(string);
    if(remainingSize() >= size){
        this->message_payload[message_buffer_index] = size;
        message_buffer_index++;
        strncpy((char *) &(message_payload[message_buffer_index]),string,size);
        message_buffer_index += size;
        message_payload[message_buffer_index] = '\0';
        message_payload_size += (size + 1);
        this->updateSize();
        return HAMSTER_RETURN::RETURN_OK;
    }
    return HAMSTER_RETURN::RETURN_NOK;
}

HAMSTER_RETURN HAMSTERMessage::copyToPayload(char * buffer, int size){
    if(remainingSize() >= size){
        memcpy ((void *) &(message_payload[message_buffer_index]),(void *) buffer,size);
        message_buffer_index += size;
        message_payload[message_buffer_index] = '\0';
        message_payload_size += size;
        this->updateSize();
        return RETURN_OK;
    }
    return RETURN_NOK;
}

int HAMSTERMessage::extractInt8FromPayload(uint8_t * value){
    sscanf(&(this->message_payload[message_buffer_index]),"%02x",value);
    message_buffer_index += 2;
    return 2;
}

void HAMSTERMessage::extractCode(){
    uint32_t code;
//    char vector_code[8];
//    strncpy(vector_code,this->message_payload,8);
    sscanf(this->message_payload,"%08x",&code);
    this->message_code = static_cast<HAMSTER_MESSAGE_CODE>(code);
    message_buffer_index += 8;
}

void HAMSTERMessage::extractSize(){
    uint16_t size;
//    char size_vector[4];
//    strncpy(size_vector,&(this->message_payload[message_buffer_index]),4);
    sscanf(&(this->message_payload[message_buffer_index]),"%04x",&size);
    message_payload_size = size;
    message_buffer_index +=4;
}

void HAMSTERMessage::rewind(void){
    this->message_buffer_index = HAMSTERMessage::header_size;
}

char * HAMSTERMessage::extractStringFromPayload(){
    char size = this->message_payload[message_buffer_index];
//    sscanf((char *) &(message_payload[message_buffer_index]),"%c",&size);
    this->message_buffer_index++;
    char * str = new char[size];
    strncpy(str,(char *) &(message_payload[message_buffer_index]),size);
    str[size] = '\0';
    message_buffer_index += size;
    return str;
}

char * HAMSTERMessage::getUserMessage(){
    this->message_payload[message_payload_size+HAMSTERMessage::header_size] = '\0';
    return &(this->message_payload[message_buffer_index]);
}

HAMSTER_RETURN HAMSTERMessage::updateSize(){
    char * size = new char[4];
    sprintf(size,"%04x",this->message_payload_size);
    strncpy((char *) &(this->message_payload[8]),size,4);
    this->message_size = message_payload_size + header_size;
    delete size;
    return HAMSTER_RETURN::RETURN_OK;
}

int HAMSTERMessage::pushInt8IntoPayload(char ** buffer, uint8_t value){
    sprintf((*buffer),"%02x",value);
    return 2;
}

int HAMSTERMessage::pullInt8FromPalyload(char * buffer, uint8_t * value){
    sscanf(buffer,"%02x",value);
    return 2;
}

} /* namespace messaging */
} /* namespace comm */
} /* namespace hamster */