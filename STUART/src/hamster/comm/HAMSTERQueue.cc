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
 * \file    HAMSTERQueue.cc
 * \author: Mariana Rodrigues   rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */


#include "HAMSTERQueue.h"

namespace hamster{
    namespace comm{

//-----------------------------------------------------------------------------
// Constructor/Destructor
//-----------------------------------------------------------------------------
HAMSTERQueue::HAMSTERQueue() {
    this->queue.clear();
}

HAMSTERQueue::~HAMSTERQueue() {
}

//-----------------------------------------------------------------------------
// Message handling
//-----------------------------------------------------------------------------
void HAMSTERQueue::pushMessage(messaging::HAMSTERMessage msg){
    this->queue_mutex.lock();
    this->queue.push_back(msg);
    this->queue_mutex.unlock();
}
void HAMSTERQueue::putEmergencyMessage(messaging::HAMSTERMessage msg){
    //\todo Verify emergency code
    this->queue_mutex.lock();
    this->queue.push_front(msg);
    this->queue_mutex.unlock();
    
}
messaging::HAMSTERMessage * HAMSTERQueue::popMessage(void){
    this->queue_mutex.lock();
    messaging::HAMSTERMessage * newMsg = new messaging::HAMSTERMessage(this->queue.front());
    this->queue.pop_front();
    this->queue_mutex.unlock();
    return newMsg;
}
const messaging::HAMSTERMessage * HAMSTERQueue::peek(void){
    this->queue_mutex.lock();
    messaging::HAMSTERMessage * newMsg = new messaging::HAMSTERMessage(this->queue.front());
    this->queue_mutex.unlock();
    return newMsg;
}

//-----------------------------------------------------------------------------
// Queue management
//-----------------------------------------------------------------------------

bool HAMSTERQueue::isEmpty(void){
    return this->queue.empty();
}
long unsigned int HAMSTERQueue::size(void){
    return this->queue.size();
}
void HAMSTERQueue::clear(void){
    this->queue.clear();
}

}
}