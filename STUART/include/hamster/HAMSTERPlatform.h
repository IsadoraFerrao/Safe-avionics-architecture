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
 *    \class hamster::HAMSTERPlatform HAMSTERPlatform.h
 *    \brief Provides a basic structure for all platforms in the application.
 *    \details 
 *       \note This class is present only in Design Model, not existing in the
 *             conceptual model.
 * 
 *       \n
 *       This class is used as a point of inheritance for HAMSTER platforms
 *       in conceptual model, establishing the struction for the application
 *       multi-thread execution.
 * 
 *  \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 *  \copyright GNU Lesser General Public License.
 * \endif
 */

#ifndef HAMSTERPLATFORM_H
#define HAMSTERPLATFORM_H

#include "HAMSTER.h"
#include "HAMSTERUnitCommInfo.h"
#include "HAMSTERMessage.h"
#include "HAMSTERQueue.h"
#include "HAMSTERPeer.h"
#include "MessageLock.h"
#include "comm/MessagePooler.h"

namespace hamster{
    
class Unit;
    
class HAMSTERPlatform {
    
    friend class comm::CommBroker;

public:
//-----------------------------------------------------------------------------
// Constructor / Destructor
//----------------------------------------------------------------------------- 
    HAMSTERPlatform(Unit * unit, HAMSTERUnitCommInfo * info):my_unit(unit),my_unit_comm_info(info){};
    virtual ~HAMSTERPlatform(){};
    
//-----------------------------------------------------------------------------
// HAMSTER Platform methods
//----------------------------------------------------------------------------- 
    /*! 
     * \fn void HAMSTERPlatform::platformInitialization()
     * \brief Initialization of the platform.
     * \details Pure virtual method which perform the necessary steps to 
     * initialize a HAMSTERPlatform.
     * \attention All concrete child classes must provide an implementation 
     * for this method.
     * 
     * 
     */

    virtual void platformInitialization(void) = 0;
    //virtual void dados(void);
    /*! 
     * \fn void HAMSTERPlatform::platformLoop()
     * \brief Main loop of the platform.
     * \details Initialize the platform thread, saving the thread pointer to be
     *  joined in platform termination.
     */
    
    virtual void platformLoop(void){
        this->platform_main_thread = new std::thread(HAMSTERPlatformThread,this);
    }
    
    /*! 
     * \fn void HAMSTERPlatform::platformTermination()
     * \brief Termination of the platform.
     * \details Pure virtual method which perform the necessary steps to 
     * correctly terminate a HAMSTERPlatform.
     * \attention All concrete child classes must provide an implementation 
     * for this method.
     */
    virtual void platformTermination(void) = 0;
    
    /*! 
     * \fn void HAMSTERPlatform::parseMessage()
     * \brief Method of message parsing.
     * \details Pure virtual method which perform the necessary steps to 
     * parse possible messages received by the platform.
     * \attention All concrete child classes must provide an implementation 
     * for this method.
     */
    virtual void parseMessage(hamster::comm::messaging::HAMSTERMessage * msg) = 0;
    
    /*!
     * \fn inline friend std::ostream& hamster::HAMSTERPlatform::operator<<(std::ostream& stream,HAMSTERPlatform& platform)
     * \brief Operator << overload for all HAMSTER Platforms.
     * \details This method invokes method printPlatform, which is a private, pure
     * virtual function in HAMSTERPlatform class. This ensures that all HAMSTER Platforms
     * provides a function in which their important data is sent to output stream.
     */
    inline friend std::ostream& operator<<(std::ostream& stream, HAMSTERPlatform * platform) {
        return platform->printPlatform(stream);
    }

    inline friend std::ostream& operator<<(std::ostream& stream, HAMSTERPlatform& platform) {
        return platform.printPlatform(stream);
    }
    
    Unit* GetUnit() const {
        return my_unit;
    }
    
    // \todo tornar virtual pura
    virtual bool setupFinished(){
        return true;
    }
    
protected:
    
//-----------------------------------------------------------------------------
// Thread Method
//----------------------------------------------------------------------------- 
    /*! 
     * \fn static void HAMSTERPlatform::HAMSTERPlatformThread(HAMSTERPlatform * platform)
     * \brief Method to be implemented in multi-thread execution.
     * \details This method is called by the std::thread constructor to be
     * executed by a new thread. This inline method is a wrapper so that 
     * executionLoop() method is called by a static function.
     */
    static void HAMSTERPlatformThread(HAMSTERPlatform * platform) {
        platform->executionLoop();
    }
    
//-----------------------------------------------------------------------------
// Communication
//----------------------------------------------------------------------------- 
    void sendMessage(comm::messaging::HAMSTERMessage msg){
        this->outgoing_queue->pushMessage(msg);        
    }
    
    comm::messaging::HAMSTERMessage * sendMessaageAndWaitResponse(comm::messaging::HAMSTERMessage msg){
        std::mutex mtx;
        std::unique_lock<std::mutex> lk(mtx);
        std::condition_variable lock;
        comm::messaging::HAMSTERMessage * response = NULL;
        
        // Put watch for response
        if(this->insertMessageWatch(msg.getCode(),msg.getRecipient()->GetID(),&lock,&response) != true){
            return NULL;
        }
        
        // Put message in buffer
        this->sendMessage(msg);
        // Wait for response
        lock.wait(lk);
        // Return response
        return response;
    }
    
    HAMSTERUnitCommInfo* getCommInfo() const {
        return my_unit_comm_info;
    }
    
        comm::MessagePooler * getMessagePool(){
            return &message_pool;
        }


        
//-----------------------------------------------------------------------------
// Main loop of execution
//-----------------------------------------------------------------------------
    /*!
     * \fn virtual std::ostream& hamster::HAMSTERPlatform::executionLoop
     * \brief Main execution loop of the platform.
     * \details This method is called by the platform to be executed within a
     * thread, and must be overwritten by all concrete child classes.
     */
    virtual void executionLoop() = 0;
//-----------------------------------------------------------------------------
// Queue handling
//-----------------------------------------------------------------------------
comm::HAMSTERQueue* GetIncomingQueue() const {
    return incoming_queue;
}
void SetIncomingQueue(comm::HAMSTERQueue* incoming_queue) {
    this->incoming_queue = incoming_queue;
}
comm::HAMSTERQueue* GetOutgoingQueue() const {
    return outgoing_queue;
}
void SetOutgoingQueue(comm::HAMSTERQueue* outgoing_queue) {
    this->outgoing_queue = outgoing_queue;
}

bool isFinalized(){
    return this->finalize;
}

void terminate(void){
    this->finalize = true;
}

bool insertMessageWatch(comm::messaging::HAMSTER_MESSAGE_CODE message_code,utils::Uuid peer_id,std::condition_variable * lock,comm::messaging::HAMSTERMessage ** response){
    comm::messaging::MessageLock my_lock(message_code,peer_id,lock,response);
    
    std::pair<comm::messaging::MessageLock::LockKey,comm::messaging::MessageLock> toinsert(my_lock.getKey(),my_lock);
    std::pair<std::map<comm::messaging::MessageLock::LockKey,comm::messaging::MessageLock>::iterator,bool> ret = this->sync_messages_locks.insert(toinsert);
    return ret.second;
}

bool removeMessageWatch(comm::messaging::MessageLock::LockKey key){
    int ret = this->sync_messages_locks.erase(key);
    return (ret == 1);
}

bool checkForMessageWatch(comm::messaging::HAMSTER_MESSAGE_CODE message_code, utils::Uuid peer_id){
    comm::messaging::MessageLock::LockKey received_key(message_code,peer_id);
    std::map<comm::messaging::MessageLock::LockKey,comm::messaging::MessageLock>::iterator it;
    it = this->sync_messages_locks.find(received_key);
    return (it != this->sync_messages_locks.end());
}

comm::messaging::MessageLock * getMessageWatch(comm::messaging::HAMSTER_MESSAGE_CODE message_code, utils::Uuid peer_id){
    comm::messaging::MessageLock::LockKey received_key(message_code,peer_id);
    std::map<comm::messaging::MessageLock::LockKey,comm::messaging::MessageLock>::iterator it;
    it = this->sync_messages_locks.find(received_key);
    if(it != this->sync_messages_locks.end()){
        return new comm::messaging::MessageLock(it->second);
    }else{
        return NULL;
    }
}

private:
    /*! \brief Points to the entity to which the platforms belong to. */
    Unit * my_unit;
    /*! \brief Points to the communication info of the unit which the platform
     *  belongs to.
     */
    HAMSTERUnitCommInfo * my_unit_comm_info;
    
    /*! \brief Points to the outgoing message queue of the platform to be used 
     * in multi-thread execution. The queue reference is shared
     */
    comm::HAMSTERQueue * outgoing_queue;
    /*! \brief Incoming message queue of the platform to be used in multi-thread
     * execution.
     */
    comm::HAMSTERQueue * incoming_queue;
    
    /*!> \brief Pointer to thread in which the platform main loop runs. */
    std::thread * platform_main_thread;
    
    bool finalize = false;
    
    // \todo documentacao
    comm::MessagePooler message_pool;
    
    std::map<comm::messaging::MessageLock::LockKey,comm::messaging::MessageLock> sync_messages_locks;
    
    /*!
     * \fn virtual std::ostream& hamster::HAMSTERPlatform::printPlatform(std::ostream& stream) const
     * \brief Outputs the information of the HAMSTERPlatform to the output stream.
     * \details Pure virtual method which inserts the details of a HAMSTER Platform
     * in an output stream to be used in operator << overload.
     * \attention All concrete child classes must provide an implementation for
     * this method.
     */
    virtual std::ostream& printPlatform(std::ostream& stream) const = 0;

};

} /* namespace hamster */

#endif /* HAMSTERPLATFORM_H */

