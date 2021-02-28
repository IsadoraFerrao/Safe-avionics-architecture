/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MessagePooler.cc
 * Author: Mariana
 * 
 * Created on 4 de Abril de 2018, 07:42
 */

#include "MessagePooler.h"

namespace hamster{
namespace comm{

MessagePooler::MessagePooler() {
}

MessagePooler::~MessagePooler() {
}

HAMSTER_RETURN MessagePooler::addResponse2Pool(messaging::HAMSTER_MESSAGE_CODE code,utils::Uuid id){
    
    std::pair<utils::Uuid,messaging::HAMSTER_MESSAGE_CODE> to_insert(id,code);
    this->message_pool.insert(this->message_pool.end(),to_insert);
    return RETURN_OK;
}

HAMSTER_RETURN MessagePooler::messageReceived(messaging::HAMSTER_MESSAGE_CODE code,utils::Uuid id){
    std::list<std::pair<utils::Uuid,messaging::HAMSTER_MESSAGE_CODE>>::iterator it;
    
    for(it = this->message_pool.begin();it != this->message_pool.end(); it++){
        if((*it).first == id && (*it).second == code){
            this->message_pool.erase(it);
            return RETURN_OK;
        }
    }
    return RETURN_NOK;
}

bool MessagePooler::isAwaitingMessage(messaging::HAMSTER_MESSAGE_CODE code){
    std::list<std::pair<utils::Uuid,messaging::HAMSTER_MESSAGE_CODE>>::iterator it;
    
    it = this->message_pool.begin();
    if(it == this->message_pool.end()){
        if((*it).second == code){
            return true;
        }
    }
    for(it = this->message_pool.begin();it != this->message_pool.end(); it++){
        if((*it).second == code){
            return true;
        }
    }
    return false;
};

}
}

