/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SuperCSU.cpp
 * Author: Mariana
 * 
 * Created on 25 de Janeiro de 2018, 10:44
 */

#include "SuperCSU.h"
#include "AddressInfo.h"
#include <iostream>
#include "FlightData.h"
#include "HAMSTERLogger.h"
#include <iostream>
#include <cstring>

using namespace std;

namespace hamster{
namespace sphere{
namespace csu{

SuperCSU::SuperCSU(Unit * unit, HAMSTERUnitCommInfo * info):CentralCSU(unit,info) {
    logDebugMessage("New SuperCSU. ID = ",this->GetUnit()->getID().toString());
}

SuperCSU::~SuperCSU() {
}

//-----------------------------------------------------------------------------
// HAMSTERNode methods
//-----------------------------------------------------------------------------
void SuperCSU::executionLoop(void){
    logDebugMessage("Central CSU execution loop");
    comm::messaging::HAMSTERMessage * message;
    comm::HAMSTERPeer * unit;
    
    logEventMessage("CentralCSU State = INITIAL");
    do{
        // Verify new messages
        if(!this->GetIncomingQueue()->isEmpty()){
            comm::messaging::HAMSTERMessage * msg = this->GetIncomingQueue()->popMessage();
            this->parseMessage(msg);
            delete msg;
        }
        switch(this->getState()){
            case CSU_STATE::INITIAL:
                // Initialize module list
                this->setState(CSU_STATE::WAITING_MODULES);
                break;
            case CSU_STATE::WAITING_MODULES:
                // Stay in this state until all critical modules are authenticated
                if(areAllCriticalModulesAuthenticated() == true){
                    if(this->getCommInfo()->formationKnown() == true){
                        // The unit knows its peers
                        this->setState(CSU_STATE::WAITING_PEERS);
                    }
                    else{
                        // The unit has to discover a central unit
                    }
                }
                break;
            case CSU_STATE::WAITING_PEERS:
                // Stay in this state until all peers are authenticated
                if(this->getCommInfo()->areAllPeersAuthenticated() == true){
//                    this->GetUnit()->initializationFinished();
                    this->setState(CSU_STATE::EXECUTING);
                }
                break;

            case CSU_STATE::EXECUTING:
//                    for(;false;);
                break;
            case CSU_STATE::EMERGENCY:;
//                    for(;false;);
                break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
    }while(this->isFinalized() == false);
}

void SuperCSU::parseMessage(hamster::comm::messaging::HAMSTERMessage* msg){
    comm::messaging::HAMSTERMessage * response;
    comm::HAMSTERPeer * peer;
    utils::Uuid * received_id;
    char * message_buffer;
    int message_size;
    logDebugMessage("Message Received in SuperCSU: ", msg);
    switch(msg->getCode()){
        case comm::messaging::HAMSTER_MESSAGE_CODE::REQ_ENTITY_ACCESS:
            // If known formation, the peer will be already in peer list.
            if(this->getCommInfo()->formationKnown() == true){
                // Extract ID from list
                received_id = new utils::Uuid(std::string(msg->extractStringFromPayload()));
                peer = this->getCommInfo()->getPeer(*received_id);
                delete received_id;
                if(peer != NULL){
                    peer->SetAuthorized(true);
                    response = new comm::messaging::HAMSTERMessage(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
                            comm::messaging::HAMSTER_MESSAGE_CODE::ENTITY_ACC_GRANTED);
                    response->setRecipient(peer);
                    this->sendMessage(*response);
                    delete response;
                }
            }
            break;
        case comm::messaging::HAMSTER_MESSAGE_CODE::REQ_PEER_CONN_INFO:
            // Extract ID from message
            received_id = new utils::Uuid(std::string(msg->extractStringFromPayload()));
            peer = this->getCommInfo()->getPeer(*received_id);
            delete received_id;
            if(peer != NULL){
                // Verify if peer is authenticated
                if((peer->isConnected() && peer->isAuthorized()) == true){
                    // Notify peer on new connection
                    response = new comm::messaging::HAMSTERMessage(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
                                   comm::messaging::HAMSTER_MESSAGE_CODE::NOT_NEW_PEER_CONNECTION);
                    response->addToPayload((char*) msg->getRecipient()->GetID().toString().c_str());
                    message_size = msg->getRecipient()->GetAddress()->pushInPayload(&message_buffer);
                    if(response->copyToPayload(message_buffer,message_size) != HAMSTER_RETURN::RETURN_OK){
                        logErrorMessage("Unable to buid message ",response->getCode());
                        delete message_buffer;
                        delete response;
                        return;
                    }else{
                        response->setRecipient(peer);
                    }
                }else{
                // Peer not authorized
                    response = new comm::messaging::HAMSTERMessage(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
                                   comm::messaging::HAMSTER_MESSAGE_CODE::RET_PEER_NOT_AUTHORIZED);
                    response->setRecipient(msg->getRecipient());
                }
            }else{
                response = new comm::messaging::HAMSTERMessage(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
                           comm::messaging::HAMSTER_MESSAGE_CODE::RET_PEER_UNKNOWN);
                response->setRecipient(msg->getRecipient());
            }
            this->sendMessage(*response);
            delete response;
            break;
        // Responses to NOT_NEW_PEER_CONNECTION:
        case comm::messaging::HAMSTER_MESSAGE_CODE::RET_NEW_PEER_REFUSED:
        case comm::messaging::HAMSTER_MESSAGE_CODE::RET_NEW_PEER_ADDED:
            // Extract ID so I know to whom I have to send this response
            received_id = new utils::Uuid(std::string(msg->extractStringFromPayload()));
            peer = this->getCommInfo()->getPeer(*received_id);
            // Build response
            if(msg->getCode() == comm::messaging::HAMSTER_MESSAGE_CODE::RET_NEW_PEER_ADDED){
                // Build response
                response = new comm::messaging::HAMSTERMessage(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
                                   comm::messaging::HAMSTER_MESSAGE_CODE::RET_PEER_CONN_INFO);
                // Put ID
                response->addToPayload((char *) msg->getRecipient()->GetID().toString().c_str());
                // Put address
                response->pushMessageField(static_cast<comm::messaging::MessageField *>(msg->getRecipient()->GetAddress()));
            }else{
                response = new comm::messaging::HAMSTERMessage(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
                                   comm::messaging::HAMSTER_MESSAGE_CODE::RET_PEER_NOT_AVAILABLE);
                response->addToPayload((char *) received_id->toString().c_str());
            }
            response->setRecipient(peer);
            this->sendMessage(*response);
            delete response;
            break;
        default:
            logErrorMessage("Could not parse message in SuperCSU. Message code = ",
                    (int) msg->getCode(), ", ID = ",this->GetUnit()->getID().toString());
            break;
    }
}
            
} /* namespace csu */
} /* namespace sphere */
} /* namespace hamster */