/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MessageLock.cc
 * Author: Mariana
 * 
 * Created on 16 de Fevereiro de 2018, 14:17
 */

#include "MessageLock.h"

namespace hamster{
namespace comm{
namespace messaging{



MessageLock::MessageLock() {
    logDetailedMessage("MessageLock padrão");
    this->response = NULL;
}

MessageLock::MessageLock(HAMSTER_MESSAGE_CODE message_code,
                utils::Uuid id,
                std::condition_variable * lock,
                HAMSTERMessage ** resp){
    this->key.setSentCode(message_code);
    this->key.setPeerID(id);
    this->message_lock = lock;
    this->response = resp;
}

MessageLock::MessageLock(const MessageLock& orig) {
    this->key.setSentCode(orig.key.getSentCode());
    this->key.setPeerID(orig.key.getPeerID());
    this->message_lock = orig.message_lock;
    this->response = orig.response;
}

MessageLock::~MessageLock() {
}

MessageLock::LockKey MessageLock::getKey() const{
    return key;
}

void MessageLock::setKey(LockKey key) {
    this->key = key;
}

std::condition_variable* MessageLock::getMessage_lock(){
    return message_lock;
}

void MessageLock::setMessageLock(std::condition_variable* message_lock) {
    this->message_lock = message_lock;
}

comm::messaging::HAMSTERMessage* MessageLock::getResponse(){
    return (*response);
}

void MessageLock::setResponse(comm::messaging::HAMSTERMessage * resp) {
    *(this->response) = resp;
}


MessageLock::LockKey::LockKey(){
    
}

MessageLock::LockKey::LockKey(HAMSTER_MESSAGE_CODE message_code,utils::Uuid id){
    this->sent_code = message_code;
    this->peer_id = id;    
}

MessageLock::LockKey::LockKey(LockKey &orig){
    this->peer_id = orig.peer_id;
    this->sent_code = orig.sent_code;
}

MessageLock::LockKey::LockKey(const LockKey &orig){
    this->peer_id = orig.peer_id;
    this->sent_code = orig.sent_code;
}

MessageLock::LockKey::~LockKey(){
    
}

utils::Uuid MessageLock::LockKey::getPeerID() const{
    return peer_id;
}

void MessageLock::LockKey::setPeerID(utils::Uuid id) {
    this->peer_id = id;
}

HAMSTER_MESSAGE_CODE MessageLock::LockKey::getSentCode() const {
    return sent_code;
}

void MessageLock::LockKey::setSentCode(HAMSTER_MESSAGE_CODE sent_code) {
    this->sent_code = sent_code;
}

//bool MessageLock::LockKey::operator<(const LockKey& other_key){
//    if(this->sent_code == other_key.sent_code){
//        return this->peer_id < other_key.peer_id;
//    }
//    return this->sent_code < other_key.sent_code;
//}

} /* namespace messaging */
} /* namespace comm */
} /* namespace hamster */