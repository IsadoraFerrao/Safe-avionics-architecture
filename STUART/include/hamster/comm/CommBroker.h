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
 * \anchor CommBroker
 * \class hamster::comm::CommBroker CommBroker.h
 * \brief Main class to deal with HAMSTER Messages within HAMSTER Units.
 * \details This class centralizes the message exchange in HAMSTER Architecture.
 * Its method parseMessage is the main point of message parsing, being invoked 
 * by all communication entry points when a HAMSTER Message is received.
 * 
 * Depending on the message, the broker can either forward it to the platform's 
 * (NCI, SPHERE, etc.) main loop of execution or invoke a platform method
 * directly.
 * 
 * In order to forward the received messages, the CommBroker has a shared pair
 * of queues with each HAMSTER platform.
 * 
 *  \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 *  \copyright GNU Lesser General Public License.
 * 
 *  \endif
 */

#ifndef COMMBROKER_H
#define COMMBROKER_H

#include "HAMSTERPlatform.h"
#include "HAMSTER_MESSAGE_CODE.h"
#include "Unit.h"
#include "SPHERE.h"
#include "CSU.h"
#include "SMU.h"
#include "SEMU.h"
#include "NPUnit.h"
#include "NIMBLE.h"
#include "NCI.h"

namespace hamster{
namespace comm{
    
class CommBroker : public HAMSTERPlatform{
public:
//-----------------------------------------------------------------------------
// Constructor/Destructor
//-----------------------------------------------------------------------------
    CommBroker(Unit * unit,HAMSTERUnitCommInfo * info);
    virtual ~CommBroker();
    
//-----------------------------------------------------------------------------
// HAMSTERPlatform methods
//-----------------------------------------------------------------------------
    /*! \brief Initialization of the platform. */
    void platformInitialization(void);
    void dados(void);
    /*!
     * \fn void hamster::comm::CommBroker::platformLoop()
     * \brief Main loop of execution.
     */
    void executionLoop(void);
    /*!
     * \fn void hamster::comm::CommBroker::platformTermination()
     * \brief Termination of the platform.
     */
    void platformTermination(void);
    /*!
     * \fn hamster::comm::CommBroker::parseMessage()
     * \brief The main message parser on HAMSTER Architecture. The CommBroker 
     * method is invoked everytime a message arrives at a HAMSTER Unit. 
     * Depending on the message, the Broker can either invoke a platform method
     * or forward it to the platform main loop trough the message queue.
     * \param msg a \ref HAMSTERMessage "HAMSTER Message"
     * \details Every HAMSTER Unit connection will invoke this method upon 
     * receiving a message. Depending on the message code, the communication
     * broker can either invoke a method of a HAMSTER platform or forward it to
     * the main execution loop of each platform through a queue.
     * 
     */
    void parseMessage(hamster::comm::messaging::HAMSTERMessage * msg);
    
private:
//-----------------------------------------------------------------------------
// HAMSTERPlatform methods
//-----------------------------------------------------------------------------
    /*!
     * \fn void hamster::comm::CommBroker::printPlatform(std::ostream& stream)
     * \param stream an output strean
     * \return a modified stream
     * \brief Insert platform type and its correspondent Unit info in the stream.
     */
    std::ostream& printPlatform(std::ostream& stream) const;
    
//-----------------------------------------------------------------------------
// Queues to all platforms
//-----------------------------------------------------------------------------
    /*! \brief Queue to establish message passing with CSU module of SPHERE 
     * platform. */
    HAMSTERQueue * csu_queue;
    /*! \brief Queue to establish message passing with CSU module of SPHERE 
     * platform. */
    HAMSTERQueue * smu_queue;
    /*! \brief Queue to establish message passing with SEMU module of SPHERE 
     * platform. */
    HAMSTERQueue * NCI_queue;
    /*! \brief Queue to establish message passing with SEMU module of SPHERE 
     * platform. */
    HAMSTERQueue * semu_queue;
    /*! \brief Queue to establish message passing with NP platform. */
    HAMSTERQueue * np_queue;
    /*! \brief Queue to establish message passing with NIMBLE platform. */
    HAMSTERQueue * nimble_queue;
    HAMSTERQueue ** interface_queues;
    
    
};

} /* namespace comm */
} /* namespace hamster */
#endif /* COMMBROKER_H */

