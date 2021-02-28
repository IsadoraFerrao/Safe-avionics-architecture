/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LocalCSU.cpp
 * Author: Mariana
 * 
 * Created on 29 de Março de 2018, 10:06
 */

#include "LocalCSU.h"
#include "CommBroker.h"
#include "HAMSTERMessage.h"
#include "CommInterface.h"
#include "AddressInfo.h"

namespace hamster{
namespace sphere{
namespace csu {
    
LocalCSU::LocalCSU(Unit * unit, HAMSTERUnitCommInfo * info):CSU(unit,info) {
}


LocalCSU::~LocalCSU() {
}

void LocalCSU::executionLoop(void){
    logDebugMessage("CSU execution loop");
    comm::messaging::HAMSTERMessage * message;
    comm::HAMSTERPeer * unit;
    
    logVerboseMessage("CSU State = INITIAL");

    for(;;){
        // Verify new messages
        if(!this->GetIncomingQueue()->isEmpty()){
            comm::messaging::HAMSTERMessage * msg = this->GetIncomingQueue()->popMessage();
            this->parseMessage(msg);
            delete msg;
        }
        switch(this->getState()){
            case CSU_STATE::INITIAL:
                // Initialize module list
                this->setState(CSU_STATE::CONNECTING_CENTRAL_UNIT);
                break;
            case CSU_STATE::CONNECTING_CENTRAL_UNIT:
                // Get central unit and try to connect to it.
                unit = this->getCommInfo()->getCentralUnit();
                unit->GetInterface()->connectToPeer(unit);
                this->setState(CSU_STATE::WAITING_CENTRAL_UNIT);
                break;
            case CSU_STATE::WAITING_CENTRAL_UNIT:
                if(this->getCommInfo()->getCentralUnit()->isConnected()){
#ifndef NO_AUTHENTICATION
                    this->setState(CSU_STATE::REQUESTINTG_AUTHORIZATION);
#else
                    this->setState(CSU_STATE::EXECUTING);
#endif
                }
                break;
            case CSU_STATE::REQUESTINTG_AUTHORIZATION:
                message = new comm::messaging::HAMSTERMessage(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,comm::messaging::HAMSTER_MESSAGE_CODE::REQ_MODULE_ACCESS);
                message->addToPayload((char *) this->GetUnit()->getID().toString().c_str());
                message->setRecipient(this->getCommInfo()->getCentralUnit());
                // \todo completar aqui!
                this->sendMessage(*message);
                this->setState(CSU_STATE::WAITING_ACCESS_GRANTED);
                delete message;
                break;
            case CSU_STATE::WAITING_ACCESS_GRANTED:
                // Does nothing, this state is handled by ParseMessage() method.
                //for(;false;);
                break;
            case CSU_STATE::EXECUTING:
//                    for(;false;);
                break;
            case CSU_STATE::EMERGENCY:;
//                    for(;false;);
                break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
    }

}


void LocalCSU::parseMessage(hamster::comm::messaging::HAMSTERMessage* msg){
    comm::messaging::MessageLock * msg_lock;
    utils::Uuid * id;
    comm::interface::AddressInfo * peer_address;
    comm::HAMSTERPeer * peer;
    comm::messaging::HAMSTERMessage * response;
    
    logDebugMessage("Message Received in Local CSU: ", msg->getCode());
    switch(msg->getCode()){
        case comm::messaging::HAMSTER_MESSAGE_CODE::MODULE_ACC_GRANTED:
        if(this->getState() == CSU_STATE::WAITING_ACCESS_GRANTED){
            this->getCommInfo()->getCentralUnit()->SetAuthorized(true);
            this->setState(CSU_STATE::EXECUTING);
            logDebugMessage("Local CSU State = NORMAL_EXECUTION");
        }
        break;
//        case comm::messaging::HAMSTER_MESSAGE_CODE::NOT_NEW_PEER_CONNECTION:
//            // 1. Extract ID
//            id = new utils::Uuid(std::string(msg->extractStringFromPayload()));
//            // 2. Extract Adrress
//            peer_address = comm::interface::AddressInfo::buildAddressInfo(msg->getRecipient()->GetInterface()->getTechnology());
//            msg->pullMessageField(static_cast<comm::messaging::MessageField *>(peer_address));
//            // 3. Add Peer in list
//            peer = new comm::HAMSTERPeer(msg->getRecipient()->GetInterface(),peer_address,*id);
//            if(this->getCommInfo()->AddPeer(peer) != RETURN_OK){
//                // Error in adding peer.
//                response = new comm::messaging::HAMSTERMessage(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
//                                                               comm::messaging::HAMSTER_MESSAGE_CODE::RET_NEW_PEER_REFUSED);
//            }else{
//                // Peer found
//                response = new comm::messaging::HAMSTERMessage(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
//                                                               comm::messaging::HAMSTER_MESSAGE_CODE::RET_NEW_PEER_ADDED);
//            }
//            // Put ID so central unit knows of whom I'm talking about
//            response->addToPayload((char *) id->toString().c_str());
//            response->setRecipient(msg->getRecipient());
//            // Send message
//            this->sendMessage(*response);
//            delete id;
//            delete response;
//            break;
//        // Responses to comm::messaging::HAMSTER_MESSAGE_CODE::REQ_PEER_CONN_INFO
//        case comm::messaging::HAMSTER_MESSAGE_CODE::RET_PEER_CONN_INFO:
//        case comm::messaging::HAMSTER_MESSAGE_CODE::RET_PEER_UNKNOWN:
//        case comm::messaging::HAMSTER_MESSAGE_CODE::RET_PEER_NOT_AUTHORIZED:
//            // Verify waiting thread
//            logDebugMessage("Answer to REQ_PEER_CONN_INFO received: ",msg->getCode());
//            // Verify if there is a thread waiting for this response from this peer.
//            msg_lock = this->getMessageWatch(comm::messaging::HAMSTER_MESSAGE_CODE::REQ_PEER_CONN_INFO,msg->getRecipient()->GetID());
//            if(msg_lock == NULL){
//                // Message arrived without being expected
//                logWarningMessage("Message ",msg->getCode()," arrived at Central CSU without being expected. Discard.");
//            }else{
//                // Message expected!
//                // Set response
//                msg_lock->setResponse(new comm::messaging::HAMSTERMessage(*msg));
//                // Release lock
//                msg_lock->getMessage_lock()->notify_all();
//                // Remove watch
//                if(this->removeMessageWatch(msg_lock->getKey()) == false){
//                    logErrorMessage("Could not remove message watch.");
//                }
//            }
//            break;
        default:
            logErrorMessage("Could not parse message in CSU. Message code = ",
                    (int) msg->getCode(), ", ID = ",this->GetUnit()->getID().toString());
            break;
    }

}

} /* namespace csu */
} /* namespace sphere */
} /* namespace hamster */