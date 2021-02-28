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
 * \file    CommInterface.cc
 * \author: Mariana Rodrigues   rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#include "CommInterface.h"
#include "AcceptorConn.h"
#include "Connector.h"
#include "ConnectionHandler.h"
#include "AddressInfo.h"


namespace hamster{
namespace comm{
namespace interface{
    
// Constructor/Destructor
CommInterface::CommInterface(uint8_t number, Unit * unit, HAMSTERUnitCommInfo * info, COMM_INTERFACE_TYPE t,COMM_INTERFACE_TECH tech, AddressInfo * acceptor_info):
HAMSTERPlatform(unit,info),type(t),technology(tech),acceptor_address(acceptor_info),interface_number(number){
    
}
CommInterface::~CommInterface(){
}

void CommInterface::platformInitialization(){
    this->SetIncomingQueue(new comm::HAMSTERQueue());
    if(this->loadAcceptor() == RETURN_OK){
        logDebugMessage("Interface of type ",this->type," and tech ",
                this->technology," Initialization. ID = ",
                this->GetUnit()->getID());
    }else{
        logErrorMessage("Could not load acceptor of interface ",this->type,
                " and tech ",this->technology," in unit ID = ",
                this->GetUnit()->getID());
    }
}

void CommInterface::parseMessage(messaging::HAMSTERMessage* msg){

    logDebugMessage("CommInterface parse message. Message ",msg->getCode());
    uint8_t message_header;

    // Verify if the message is internal or external
    if(msg->getDirection() == messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL){
        // External message --- SEND it!!!
        logDebugMessage("External message parsed. Code = ",msg->getCode());
        // 1. Verify if the Peer is authorized. --- Before authorization??
        
          // 2. If not, return error.
        // 3. Send message
        this->sendMessageToPeer(msg,msg->getRecipient());
        logDebugMessage("External message sent.");

    }else{
        // Internal message
        logDebugMessage("Internal message in CommInterface. Code = ", msg->getCode());
        // Get Header
        message_header = msg->getHeader();
//        // Is it broadcast?
//        if((direction_code & HAMSTER_MESSAGE_MASK::PLATFORM_MASK) != 0){
//            // Redirect message to all platforms
//            this->csu_queue->pushMessage(*msg);
//            this->smu_queue->pushMessage(*msg);
//            this->semu_queue->pushMessage(*msg);
//            this->nci_queue->pushMessage(*msg);
//            if(this->GetHAMSTERUnit()->getNIMBLEPlatform() != NULL){
//                this->nimble_queue->pushMessage(*msg);
//            }
//            this->np_queue->pushMessage(*msg);
//        }else{
//            // Redirect message to correct platform
//            switch(direction_code & HAMSTER_MESSAGE_MASK::PLATFORM_MASK){
//                case HAMSTER_MESSAGE_MASK::CSU_MASK:
//                    this->csu_queue->pushMessage(*msg);
//                    break;
//                case HAMSTER_MESSAGE_MASK::SMU_MASK:
//                    this->smu_queue->pushMessage(*msg);
//                    break;
//                case HAMSTER_MESSAGE_MASK::SEMU_MASK:
//                    this->semu_queue->pushMessage(*msg);
//                    break;
//                case HAMSTER_MESSAGE_MASK::NCI_MASK:
//                    this->nci_queue->pushMessage(*msg);
//                    break;
//                case HAMSTER_MESSAGE_MASK::NIMBLE_MASK:
//                    if(this->GetHAMSTERUnit()->getNIMBLEPlatform() != NULL){
//                        this->nimble_queue->pushMessage(*msg);
//                    }else{
//                        logErrorMessage("NIMBLE message with code ",
//                                (uint32_t) msg->getCode()," arrived at HAMSTER Object ID = ",
//                                this->GetHAMSTERUnit()->getID());
//                    }
//                    break;
//                case HAMSTER_MESSAGE_MASK::NP_MASK:
//                    this->np_queue->pushMessage(*msg);
//                    break;
//                default:
//                    logErrorMessage("Message with wrong direction code received. Code = ",
//                        (uint32_t) msg->getCode(),", Unit ID = ",this->GetHAMSTERUnit()->getID());
//                    break;
//            }
//        }
    }
    logDebugMessage("CommInterface leave ParseMessage");
}

// SET methods
void CommInterface::setType(COMM_INTERFACE_TYPE type) {
    this->type = type;
}
void CommInterface::setAcceptor(AcceptorConn * acc){
    this->acceptor = acc;
}
void CommInterface::setConnector(Connector * con){
    this->connector = con;
}

// Interface Methods
uint8_t CommInterface::getInterfaceNumber(){
    return this->interface_number;
}
HAMSTER_RETURN CommInterface::loadAcceptor(){
    return this->acceptor->open();
}
bool CommInterface::isAcceptorOpen(){
    return this->acceptor->isOpen();
}
HAMSTER_RETURN CommInterface::connectToPeer(HAMSTERPeer * peer){
    ConnectionHandler * handler = this->connector->connectTo(peer->GetAddress());
    if(handler == NULL){
        //\todo colocar erro.
        return RETURN_NOK;
    }
    // Add to outgoing list
    this->addNewOutgoing(handler);
    // Initialize the handler
    peer->SetSenHanlder(handler);
    
    // Check if the peer already exists in list
    if(this->getCommInfo()->peerExists(peer->GetID()) == false){
        // If the peer is not yet in the list, insert it.
        this->getCommInfo()->AddPeer(peer);
    }else{
        /* If the peer already exists, verify the handler pair. */
        if(peer->getRecHandler() != NULL){
            // Peer fully connected
            peer->SetConnected(true);
        }
    }
    // Send ID message
    this->sendMessageToPeer(this->GetUnit()->getIDMessage(peer),peer);
    return RETURN_OK;
}
HAMSTER_RETURN CommInterface::closeInterface(){
    //\todo Makes the closing of all connections and the acceptor.
    return HAMSTER_RETURN::RETURN_OK;
}
int CommInterface::numIncomingConnections(){
    return this->incoming_connections.size();
}
int CommInterface::numOutgoingConnections(){
    return this->outgoing_connections.size();
}
HAMSTER_RETURN CommInterface::addNewIncoming(ConnectionHandler * handler){
    try { 
        this->incoming_connections.push_front(handler);
    } catch (const std::exception& e) {
        //\todo Inser Error codes
        logErrorMessage("Could not insert new Connection in CommInterface. "
                "Interface type = ",this->type," , HAMSTER Unit ID = ",
                this->GetUnit()->getID().toString(),". Exception message: ",e.what());
        return RETURN_NOK;
    }
    return RETURN_OK;
}
HAMSTER_RETURN CommInterface::addNewOutgoing(ConnectionHandler * handler){
    try { 
        this->outgoing_connections.push_front(handler);
    } catch (const std::exception& e) {
        //\todo Inser Error codes
        logErrorMessage("Could not insert new Connection in CommInterface. "
                "Interface type = ",this->type," , HAMSTER Unit ID = ",
                this->GetUnit()->getID().toString(),". Exception message: ",e.what());
    }
    return HAMSTER_RETURN::RETURN_OK;
}
HAMSTER_RETURN CommInterface::removeIncoming(ConnectionHandler * handler){
    try{
        this->incoming_connections.remove(handler);
    } catch (const std::exception& e) {
        //\todo Inser Error codes
        logErrorMessage("Could not remove incoming connection in CommInterface. "
                "Interface type = ",this->type," , HAMSTER Unit ID = ",
                this->GetUnit()->getID().toString(),". Exception message: ",e.what());
    }
    return HAMSTER_RETURN::RETURN_OK;
}
HAMSTER_RETURN CommInterface::removeOutgoing(ConnectionHandler * handler){
    try{
        this->outgoing_connections.remove(handler);
    } catch (const std::exception& e) {
        //\todo Inser Error codes
        logErrorMessage("Could not remove incoming connection in CommInterface. "
                "Interface type = ",this->type," , HAMSTER Unit ID = ",
                this->GetUnit()->getID().toString(),". Exception message: ",e.what());
    }
    return HAMSTER_RETURN::RETURN_OK;
}
HAMSTER_RETURN CommInterface::sendMessageToPeer(messaging::HAMSTERMessage * msg, HAMSTERPeer * peer){
    msg->setRecipient(peer);
    if(msg->getCode() != messaging::HAMSTER_MESSAGE_CODE::HAMSTER_UNIT_ID){
        logVerboseMessage("Encrypting...........");//>>> ENCRYPTION
//        msg = peer->GetPeer_crypto_handler()->encryptMessage(msg);
        logVerboseMessage("sendMessageToPeer(ComInterface)");
    }
    logEventMessage("Message ",msg->getCode()," sent.");
    return peer->getSenHandler()->sendMessage(msg);
}
void CommInterface::executionLoop(void){
    logDebugMessage("CommInterface Loop init.");
    do{
        if(!this->GetIncomingQueue()->isEmpty()){
            comm::messaging::HAMSTERMessage * msg = this->GetIncomingQueue()->popMessage();
            logDebugMessage("Message in CommInterface. Code = ",msg->getCode());
            this->parseMessage(msg);
            delete msg;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
    }while(this->isFinalized() == false);
}

COMM_INTERFACE_TYPE CommInterface::getType() const {
    return this->type;
}
COMM_INTERFACE_TECH CommInterface::getTechnology() const {
    return technology;
}
AcceptorConn* CommInterface::getAcceptor() const {
    return this->acceptor;
}

} /* namespace interface */
} /* namespace comm */
} /* namespace hamster */
