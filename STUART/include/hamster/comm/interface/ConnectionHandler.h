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
 *  \anchor ConnectionHandler
 *  \class hamster::comm::interface::ConnectionHandler ConnectionHandler.h
 *  \brief Class to handle different connections of a HAMSTER Unit.
 *  \details This class encapsulates a handler for a HAMSTER Unit connection and
 *  allows the unit to send and receive messages.
 *  
 *  This is an abstract class that must have a child implementation for each 
 *  type of connection interface. Every concrete child class must provide 
 *  implementations for both sendMessage() and receiveMessage() in order to
 *  exchange messages through the corresponding interface.
 * 
 *  \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 *  \copyright GNU Lesser General Public License.
 * 
 *  \endif
 */

#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include "HAMSTER.h"
#include "HAMSTERMessage.h"
#include "HAMSTERPeer.h"
#include "CommInterface.h"

namespace hamster{
namespace comm{
namespace interface{

class ConnectionHandler {
    
    friend class AcceptorConn;
    
public:
    
// Constructor / Destructor
    ConnectionHandler(CommInterface * interface):my_interface(interface){};
    virtual ~ConnectionHandler(){};
    
// Connection Handler Methods
    /*!
     * \fn hamster::comm::interface::ConnectionHandler::sendMessage()
     * \brief Sends a \ref messaging::HAMSTERMessage to another HAMSTER Unit.
     */
    virtual HAMSTER_RETURN sendMessage(messaging::HAMSTERMessage * message) = 0;
    /*!
     * \fn hamster::comm::interface::ConnectionHandler::receiveMessage()
     * \brief Retrieves a message from the connection.
     */
    virtual messaging::HAMSTERMessage * const receiveMessage() = 0;
        /*!
     * \fn hamster::comm::interface::ConnectionHandler::closeConnection()
     * \brief Closes the established connection with another HAMSTER Unit.
     */
    virtual HAMSTER_RETURN closeConnection() = 0;

    virtual void closeHandler(){
        this->terminate = true;
    }

    static void waitForMessage(ConnectionHandler * handler){
        logDebugMessage("Wait for message in Connection handler");
        do{ 
            std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));;
            messaging::HAMSTERMessage * received_message;
        
            received_message = handler->receiveMessage();
            if(received_message->getCode() != messaging::HAMSTER_MESSAGE_CODE::HAMSTER_UNIT_ID){
                 //>>> DECRYPT
//                logVerboseMessage("Decrypt..............");
//                received_message = handler->getMyPeer()->GetPeer_crypto_handler()->decryptMessage(received_message);
            }
            logEventMessage("Message ",received_message->getCode()," received.");
            if(received_message != NULL){
                // Make the message from external to internal
                received_message->switchToInternal();
                // Forward it to CommBroker
                handler->my_interface->GetOutgoingQueue()->pushMessage(*received_message);
                delete received_message;
            }
        }while(handler->terminate == false);
        handler->terminateHandler();
    }
    
protected:
    HAMSTERPeer * getMyPeer(){
        return this->my_interface->getCommInfo()->getPeerFromHandler(this);
    }
    
    void setConnection_thread(std::thread* connection_thread) {
        this->connection_thread = connection_thread;
    }
    
    CommInterface * getInterface(){
        return this->my_interface;
    }
    
    
    HAMSTER_RETURN terminateHandler(){
        logDebugMessage("Terminate Handler.");
        // Get ID from handler
        HAMSTERPeer * peer = this->my_interface->getCommInfo()->getPeerFromHandler(this);
        this->getInterface()->removeIncoming(peer->getRecHandler());
        this->getInterface()->removeOutgoing(peer->getSenHandler());
        logDebugMessage("Peer ID = ",peer->GetID().toString()," to be disconnected.");
        return peer->disconnect();
    }
    
private:
    std::thread * connection_thread;
    CommInterface * my_interface;

    bool terminate = false;
    
//#if(CRYPTOGRAPHY_AVAILABLE > 0)
   
    
//#endif
    
};

} /* namespace interface */
} /* namespace comm */
} /* namespace hamster */

#endif /* CONNECTIONHANDLER_H */

