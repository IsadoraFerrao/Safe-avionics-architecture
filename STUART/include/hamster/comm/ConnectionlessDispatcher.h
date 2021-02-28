/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * \file   ConnectionlessDispatcher.h
 * \author rodrigues.mariana@gmail.com
 * \date 2018
 * \copyright
 */

#ifndef CONNECTIONLESSDISPATCHER_H
#define CONNECTIONLESSDISPATCHER_H

#include "HAMSTER.h"
#include "HAMSTER_MESSAGE_CODE.h"
#include "HAMSTERMessage.h"
#include "HAMSTERQueue.h"
#include <map>

/*!
 * \class ConnectionlessDispatcher ConnectionlessDispatcher.h "ConnectionlessDispatcher.h"
 * \brief A class to handle messages from connectionless messages
 * \detail The class ConnectionlessDispatcher handle messages received by all 
 *  Unit's Listeners, which are connectionless endpoints. The messages and their
 *  respective handlers must be registered in the dispacther in order to be 
 *  correctly handled. This class is unique for each unit, following the
 *  Singleton \cite{gamma1994design} design pattern.
 */

namespace hamster{
namespace comm{


class ConnectionlessDispatcher {
public:
    /*! \brief Returns the unique ConnectionlessDispatcher instance of the unit.*/
    static ConnectionlessDispatcher * getConnectionlessDispatcher();
    /*! \brief Register new handler for a message code. */
    HAMSTER_RETURN registerHandler(comm::messaging::HAMSTER_MESSAGE_CODE message_code,comm::messaging::HAMSTERMessage (*message_handler)(comm::messaging::HAMSTERMessage));
    /*! \brief Remove handler for a message code. */
    HAMSTER_RETURN removeHandler(comm::messaging::HAMSTER_MESSAGE_CODE message_code);
    /*! \brief Insert message in queue to be handled. */
    HAMSTER_RETURN dispatch(comm::messaging::HAMSTERMessage message);

private:
    
    ConnectionlessDispatcher();
    virtual ~ConnectionlessDispatcher();
    
    /*! \brief Unique ConnectionlessDispatcher instance of the unit. */
    static ConnectionlessDispatcher * unique_dispatcher;
    /*! \brief Map with registered handlers. */
    std::map<comm::messaging::HAMSTER_MESSAGE_CODE,comm::messaging::HAMSTERMessage (*)(comm::messaging::HAMSTERMessage)> message_handlers;
    /*! \brief input queue for received messages. */
    comm::HAMSTERQueue received_messages;
};

        
} /* namespace comm */
} /* namespace hamster */

#endif /* CONNECTIONLESSDISPATCHER_H */

