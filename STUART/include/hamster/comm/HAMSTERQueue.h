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
 *  \anchor HAMSTERQueue
 *  \class hamster::comm::HAMSTERQueue HAMSTERQueue.h
 *  \brief Implements a queue of HAMSTER Messages to be used by HAMSTER platforms.
 *  \details The queue provides message passing between HAMSTER Platforms in a 
 *  First In, First Out (FIFO) scheme. It is possible to insert both normal and
 *  emergency messages.
 * 
 *  \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 *  \copyright GNU Lesser General Public License.
 * 
 *  \endif
 */

#ifndef HAMSTERQUEUE_H
#define HAMSTERQUEUE_H

#include <deque>
#include <mutex>
#include "HAMSTERMessage.h"

namespace hamster {
namespace comm {

class HAMSTERQueue {
public:
//-----------------------------------------------------------------------------
// Constructor/Destructor
//-----------------------------------------------------------------------------
    HAMSTERQueue();
    virtual ~HAMSTERQueue();

//-----------------------------------------------------------------------------
// Message handling
//-----------------------------------------------------------------------------
    /*!
     * \fn hamster::comm::HAMSTERQueue::pushMessage
     * \brief Insert a HAMSTER Message at the end of the queue.
     */
    void pushMessage(messaging::HAMSTERMessage msg);
    /*!
     * \fn hamster::comm::HAMSTERQueue::putEmergencyMessage
     * \brief Put an emergency HAMSTER Message at the queue beginning.
     */
    void putEmergencyMessage(messaging::HAMSTERMessage msg);
    /*!
     * \fn hamster::comm:HAMSTERQueue::popMessage
     * \brief Get a HAMSTER Message from the beginning of the queue, removing it.
     */
    messaging::HAMSTERMessage * popMessage(void);
    /*!
     * \fn hamster::comm::HAMSTERQueue::peek
     * \brief Provides a copy of the first message of the queue without removing
     * it from the queue.
     */
    const messaging::HAMSTERMessage * peek(void);

//-----------------------------------------------------------------------------
// Queue management
//-----------------------------------------------------------------------------
    /*!
     * \fn hamster::comm::HAMSTERQueue::isEmpty
     * \brief Verify if the queue is empty.
     */
    bool isEmpty(void);
    /*!
     * \fn hamster::comm::HAMSTERQueue::size
     * \brief Return the queue size.
     */
    long unsigned int size(void);
    /*!
     * \fn hamster::comm::HAMSTERQueue::clear
     * \brief Empty the queue, destroying all its elements. The queue size after
     * this operation is 0.
     */
    void clear(void);
private:
    /*!
     * \brief The queue used for message passing. A Double-edge container
     * is used so that emergency messages can be inserted at front.
     */
    std::deque<messaging::HAMSTERMessage> queue;
    /*!
     * \brief Mutex used to control access to the queue and prevent race conditions.
     */
    std::mutex queue_mutex;
};

} /* namespace comm */
} /* namespace hamster */
#endif /* HAMSTERQUEUE_H */

