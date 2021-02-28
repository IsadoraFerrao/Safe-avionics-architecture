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
 * \file   CentralCSU.cc
 * \author: Mariana Rodrigues   rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */
#include "FlightData.h"
#include "CentralCSU.h"
#include "CommBroker.h"
#include "HAMSTERMessage.h"
#include "CommInterface.h"
#include "AddressInfo.h"
#include "HAMSTEREntity.h"
#include <iostream>
#include <cstring>
#include <iterator>
#include <iomanip>
#include "HAMSTER.h"
#include "UAVJINT.h"
#include "Station.h"
#include <cstdlib>



using namespace std;

namespace hamster{
namespace sphere{
namespace csu{

//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
CentralCSU::CentralCSU(Unit * unit, HAMSTERUnitCommInfo * info) : CSU(unit, info){
    logDebugMessage("New CentralCSU. Entity ID = ",unit->getID());
}

CentralCSU::~CentralCSU() {
}

//-----------------------------------------------------------------------------
// HAMSTERNode methods
//-----------------------------------------------------------------------------
//void CentralCSU::printEssentialFlightData(void){
//    
//}


//FlightData CentralCSU::get_my_flight_data(){
 //   return this->my_flight_data;
//}

/*void CentralCSU::extractFromString(std::string line, std::string delimiter){
    int pos, pos_ant;
    int delimiter_size = delimiter.size();
    std::string field;
    
    // Latitude
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%ld",&(latitude_deg));
    printar(latitude_deg);
}*/
//FlightData CentralCSU::printEssentialFlightData(void){
//     std::cout << "\t LAAAATI: " << altitude_m << std::endl;
//}

 
void CentralCSU::executionLoop(void){
    //char file[20];
    logDetailedMessage("CentralCSU executionLoop()");
    
    //UAVJINT_H * my_uav = new UAVJINT_H::FlightData(file);
    //printf("CAMERAAAAAAAAAA: %lf\n\n", my_uav->get_my_flight_data().get_camera_priority());
    //std::cout << "Deu certo?" << get_my_flight_data();
    //logDetailedMessage("CentralCSU ");
    //logDetailedMessage("CentralCSU executionLoop()");
  //  printEssentialFlightData();
    
    comm::messaging::HAMSTERMessage * message;
    comm::HAMSTERPeer * unit;

    for(;;){
        std::cout << "testando..." << std::endl;
        //std::cout << my_uav->show_flightData_history() << std::endl;
//        printEssentialFlightData();
        
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
                    // Connect to the outside world
                    if(this->getCommInfo()->isCentralized() == true){
                        // The unit has a central unit to report to
                        if(this->getCommInfo()->formationKnown() == true){
                            // The unit knows its cental unit
                            this->setState(CSU_STATE::CONNECTING_CENTRAL_UNIT);
                        }
                        else{
                            // The unit has to discover a central unit
                        }
                    }
                    else{
                        // The unit do not have a central unit
                        if(this->getCommInfo()->formationKnown() == true){
                            // The unit knows its peers
                        }
                        else{
                            // The unit has to discover peers
                        }
                    }
                }
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
                message = new comm::messaging::HAMSTERMessage(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,comm::messaging::HAMSTER_MESSAGE_CODE::REQ_ENTITY_ACCESS);
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
            
            case CSU_STATE::EMERGENCY:
                break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
    }
}

void CentralCSU::parseMessage(hamster::comm::messaging::HAMSTERMessage* msg){
    comm::messaging::MessageLock * msg_lock;
    utils::Uuid * id;
    comm::interface::AddressInfo * peer_address;
    comm::HAMSTERPeer * peer;
    comm::messaging::HAMSTERMessage * response;
    
    logDebugMessage("Message Received in CSU: ", msg->getCode());
    switch(msg->getCode()){
        case comm::messaging::HAMSTER_MESSAGE_CODE::REQ_MODULE_ACCESS:
            // Extract ID from list
            id = new utils::Uuid(std::string(msg->extractStringFromPayload()));
            peer = this->getCommInfo()->getPeer(*id);
            delete id;
            if(peer != NULL){
                peer->SetAuthorized(true);
                response = new comm::messaging::HAMSTERMessage(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
                        comm::messaging::HAMSTER_MESSAGE_CODE::MODULE_ACC_GRANTED);
                response->setRecipient(peer);
                this->sendMessage(*response);
                this->all_critical_modules_authenticated = 
                        dynamic_cast<HAMSTEREntity *>(this->GetUnit())->areAllRequiredObjectsAuthenticated();
                delete response;
            }
            break;
        case comm::messaging::HAMSTER_MESSAGE_CODE::ENTITY_ACC_GRANTED:
            if(this->getState() == CSU_STATE::WAITING_ACCESS_GRANTED){
                this->getCommInfo()->getCentralUnit()->SetAuthorized(true);
                this->setState(CSU_STATE::EXECUTING);
                logDebugMessage("CSU State = NORMAL_EXECUTION");
            }
            break;
        case comm::messaging::HAMSTER_MESSAGE_CODE::NOT_NEW_PEER_CONNECTION:
            // 1. Extract ID
            id = new utils::Uuid(std::string(msg->extractStringFromPayload()));
            // 2. Extract Adrress
            peer_address = comm::interface::AddressInfo::buildAddressInfo(msg->getRecipient()->GetInterface()->getTechnology());
            msg->pullMessageField(static_cast<comm::messaging::MessageField *>(peer_address));
            // 3. Add Peer in list
            peer = new comm::HAMSTERPeer(msg->getRecipient()->GetInterface(),peer_address,*id);
            if(this->getCommInfo()->AddPeer(peer) != RETURN_OK){
                // Error in adding peer.
                response = new comm::messaging::HAMSTERMessage(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
                                                               comm::messaging::HAMSTER_MESSAGE_CODE::RET_NEW_PEER_REFUSED);
            }else{
                // Peer found
                response = new comm::messaging::HAMSTERMessage(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
                                                               comm::messaging::HAMSTER_MESSAGE_CODE::RET_NEW_PEER_ADDED);
            }
            // Put ID so central unit knows of whom I'm talking about
            response->addToPayload((char *) id->toString().c_str());
            response->setRecipient(msg->getRecipient());
            // Send message
            this->sendMessage(*response);
            delete id;
            delete response;
            break;
        // Responses to comm::messaging::HAMSTER_MESSAGE_CODE::REQ_PEER_CONN_INFO
        case comm::messaging::HAMSTER_MESSAGE_CODE::RET_PEER_CONN_INFO:
        case comm::messaging::HAMSTER_MESSAGE_CODE::RET_PEER_UNKNOWN:
        case comm::messaging::HAMSTER_MESSAGE_CODE::RET_PEER_NOT_AUTHORIZED:
            // Verify waiting thread
            logDebugMessage("Answer to REQ_PEER_CONN_INFO received: ",msg->getCode());
            // Verify if there is a thread waiting for this response from this peer.
            msg_lock = this->getMessageWatch(comm::messaging::HAMSTER_MESSAGE_CODE::REQ_PEER_CONN_INFO,msg->getRecipient()->GetID());
            if(msg_lock == NULL){
                // Message arrived without being expected
                logWarningMessage("Message ",msg->getCode()," arrived at Central CSU without being expected. Discard.");
            }else{
                // Message expected!
                // Set response
                msg_lock->setResponse(new comm::messaging::HAMSTERMessage(*msg));
                // Release lock
                msg_lock->getMessage_lock()->notify_all();
                // Remove watch
                if(this->removeMessageWatch(msg_lock->getKey()) == false){
                    logErrorMessage("Could not remove message watch.");
                }
            }
            break;
        default:
            logErrorMessage("Could not parse message in CSU. Message code = ",
                    (int) msg->getCode(), ", ID = ",this->GetUnit()->getID().toString());
            break;
    }
}

HAMSTER_RETURN CentralCSU::requestConnectionToCentralUnit(utils::Uuid& peer_id){
    comm::HAMSTERPeer * peer = NULL;
    utils::Uuid * id = NULL;
    // Create message
    comm::messaging::HAMSTERMessage msg(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,comm::messaging::HAMSTER_MESSAGE_CODE::REQ_PEER_CONN_INFO);
    msg.setRecipient(this->getCommInfo()->getCentralUnit());
    if(msg.addToPayload((char*) peer_id.toString().c_str()) != HAMSTER_RETURN::RETURN_OK){
        return HAMSTER_RETURN::RETURN_NOK;
    }
    comm::messaging::HAMSTERMessage * response = this->sendMessaageAndWaitResponse(msg);

    // Verify response
    switch(response->getCode()){
        case comm::messaging::HAMSTER_MESSAGE_CODE::RET_PEER_CONN_INFO:
            logDebugMessage("Peer Info received.");
            // Get ID from message
            id = new utils::Uuid(response->extractStringFromPayload());
            if(!(*id == peer_id)){
                logErrorMessage("RET_PEER_CONN_INFO arrived with wrong ID.");
                return HAMSTER_RETURN::UNKNOWN_PEER;
            }
            // Get AddressInfo from message
            comm::interface::AddressInfo * address;
            address = comm::interface::AddressInfo::buildAddressInfo(
                    response->getRecipient()->GetInterface()->getTechnology());
            response->pullMessageField(address);
            // Build Peer and add it to the list
            peer = new comm::HAMSTERPeer(response->getRecipient()->GetInterface(),
                    address,peer_id);
            this->getCommInfo()->AddPeer(peer);
            // Connect to peer
            return peer->GetInterface()->connectToPeer(peer);
            // \FIXME Como esperar a conexão do outro lado? Colocar timeout aqui
//            while(peer->isConnected() != true || peer->isAuthorized() != true){
//                std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS/3));
//            }
            break;
        case comm::messaging::HAMSTER_MESSAGE_CODE::RET_PEER_NOT_AUTHORIZED:
            return HAMSTER_RETURN::PEER_NOT_AUTH;
            break;
        case comm::messaging::HAMSTER_MESSAGE_CODE::RET_PEER_UNKNOWN:
            return HAMSTER_RETURN::UNKNOWN_PEER;
            break;
        default:
            logErrorMessage("Wrong message code released lock in requestConnectionToCentralUnit(). ",
                    "Message sent: ",msg.getCode(),", received ",response->getCode());
            break;
    }
    return HAMSTER_RETURN::RETURN_NOK;
}


} /* namespace csu */
} /* namespace sphere */
}/* namespace hamster */