/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MessageLock.h
 * Author: Mariana
 *
 * Created on 16 de Fevereiro de 2018, 14:17
 */

//\TODO Documentação

#ifndef MESSAGELOCK_H
#define MESSAGELOCK_H

#include "HAMSTERMessage.h"
#include <condition_variable>

namespace hamster{
namespace comm{
namespace messaging{

class MessageLock {
public:
    MessageLock();
    MessageLock(HAMSTER_MESSAGE_CODE message_code,
                utils::Uuid id,
                std::condition_variable * lock,
                HAMSTERMessage ** response);
    MessageLock(const MessageLock& orig);
    virtual ~MessageLock();
    
    class LockKey{
    public:
        LockKey();
        LockKey(HAMSTER_MESSAGE_CODE message_code,utils::Uuid id);
        LockKey(LockKey &orig);
        LockKey(const LockKey &orig);
        virtual ~LockKey();
        
        utils::Uuid getPeerID() const;
        void setPeerID(utils::Uuid peer_id);
        HAMSTER_MESSAGE_CODE getSentCode() const;
        void setSentCode(HAMSTER_MESSAGE_CODE sent_code);
        
//        bool operator<(const LockKey& other_key);
    friend bool operator<(const LockKey key1,const LockKey key2){
        if(key1.sent_code == key2.sent_code){
            return key1.getPeerID()< key2.getPeerID();
        }
        return key1.sent_code < key2.sent_code;
    }
    
    inline LockKey& operator=(const LockKey& other_key){
        this->peer_id = other_key.peer_id;
        this->sent_code = other_key.sent_code;
        return *this;
    }
        
    private:
        HAMSTER_MESSAGE_CODE sent_code;
        utils::Uuid peer_id;
    };
    
    LockKey getKey() const;
    void setKey(LockKey key);
    std::condition_variable* getMessage_lock();
    void setMessageLock(std::condition_variable* message_lock);
    comm::messaging::HAMSTERMessage* getResponse();
    void setResponse(comm::messaging::HAMSTERMessage* response);
    
    inline MessageLock& operator=(const MessageLock& other_lock){
        this->key = other_lock.key;
        this->message_lock = other_lock.message_lock;
        *(this->response) = *(other_lock.response);
        return *this;
    }
    
private:
    LockKey key;
    std::condition_variable * message_lock;
    comm::messaging::HAMSTERMessage ** response;

};


} /* namespace messaging */
} /* namespace comm */
} /* namespace hamster */

#endif /* MESSAGELOCK_H */

