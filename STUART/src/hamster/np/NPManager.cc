/*
 * Copyright (C) 2018     Critical Embedded System Laboratory (LSEC)
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
 * \file NPManager.cc
 * \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 *
 */

#include "NPManager.h"
#include "Mission.h"
#include "HAMSTEREntity.h"

namespace hamster{
namespace navigation_phases{
    
int phase_sent = 0;

    
//-----------------------------------------------------------------------------
// Constructor / Destructor
//----------------------------------------------------------------------------- 
NPManager::NPManager(Unit * unit,HAMSTERUnitCommInfo * info):NPUnit(unit,info) {}

NPManager::~NPManager() {}

//-----------------------------------------------------------------------------
// HAMSTERPlatform methods
//-----------------------------------------------------------------------------
void NPManager::executionLoop(void){
    logDetailedMessage("NPManager executionLoop() start.");
    uint8_t number_objects;
    comm::messaging::HAMSTERMessage * message;
    HAMSTERObjectDescriptor ** objects;
    comm::HAMSTERPeer * unit;

    do{
        // Verify new messages
        if(!this->GetIncomingQueue()->isEmpty()){
            comm::messaging::HAMSTERMessage * msg = this->GetIncomingQueue()->popMessage();
            this->parseMessage(msg);
            delete msg;
        }
        switch(this->getCurrentState()){
            case NP_MANAGER_STATE::INITIAL:
                // Do something
                this->setCurrentState(NP_MANAGER_STATE::AWAITING_MISSION);
                break;
            case NP_MANAGER_STATE::AWAITING_MODULES:
                // Stay in this state until all modules are connected
                if(dynamic_cast<HAMSTEREntity *>(this->GetUnit())->areAllObjectsConnected() == true){
                    if(this->missionWasReceived() == true){
                        // All modules connected and mission received --- Start mission distribution
                        this->setCurrentState(NP_MANAGER_STATE::MISSION_DISTRIBUTION);
                    }else{
                        // Modules connected but mission not yet received
                        this->setCurrentState(NP_MANAGER_STATE::AWAITING_MISSION);
                    }
                }
                break;
            case NP_MANAGER_STATE::AWAITING_MISSION:
                // Stay in this state until the mission is received
                if(this->missionWasReceived() == true){
                    if(dynamic_cast<HAMSTEREntity *>(this->GetUnit())->areAllObjectsConnected() == true){
                        // Mission received and all objects connected --- Start mission distribution
                        this->setCurrentState(NP_MANAGER_STATE::MISSION_DISTRIBUTION);
                    }else{
                        // Mission received but not all objects connected --- Await connection
                        this->setCurrentState(NP_MANAGER_STATE::AWAITING_MODULES);
                    }
                }else{
                    // Mission not received --- no nothing;
                }
                break;
            case NP_MANAGER_STATE::RECEIVING_MISSION:
                break;
            case NP_MANAGER_STATE::MISSION_DISTRIBUTION:
                if(this->entity_mission.getNumberOfPhases() > 0){
                    objects = dynamic_cast<HAMSTEREntity *>(this->GetUnit())->getEntityObjects(&number_objects);
                    logVerboseMessage("Mission Distribution in NPManager. Number of objects = ",
                            number_objects,". Sending mission to agents...");
                    for (int i = 0; i < number_objects; i++) {
                        // If the object is authorized, send the mission
                        if(objects[i]->getUnitCommunicationInfo()->isAuthorized() == true){
                            this->sendMissionToAgent(objects[i]);
                        }else{
                            // Notify emergency state
                            //\todo notify or not?
                        }
                    }
                    this->setCurrentState(NP_MANAGER_STATE::AWAITING_DISTRIBUTION_END);
                }else{
                    logErrorMessage("Mission in NPManager with number of phases == 0");
                    this->setCurrentState(NP_MANAGER_STATE::TERMINATION);
                }
                break;
            case NP_MANAGER_STATE::AWAITING_DISTRIBUTION_END:
                if(this->getMessagePool()->isAwaitingMessage(comm::messaging::HAMSTER_MESSAGE_CODE::MISSION_CONFIGURATION_ACK) == false){
                    // All answers were received
                    this->setCurrentState(NP_MANAGER_STATE::MISSION_START);
                }
                break;
            case NP_MANAGER_STATE::MISSION_START:
                // Initialize with phase
                this->nextPhase();
                this->setCurrentState(NP_MANAGER_STATE::MISSION_OPERATION);
                break;
            case NP_MANAGER_STATE::MISSION_OPERATION:
                // Check for current phase trigger
                if(this->getMission()->getPhase(this->getCurrentPhaseNumber())->verifyTrigger() == true ){
                    this->nextPhase();
                    if(this->getCurrentPhaseNumber() == this->getMission()->getNumberOfPhases()){
                        this->setCurrentState(NP_MANAGER_STATE::MISSION_TERMINATION);
                    }
                }
                break;
            case NP_MANAGER_STATE::MISSION_TERMINATION:
                if(this->getMission()->getPhase(this->getCurrentPhaseNumber())->verifyTrigger() == true ){
                    // Send TERMINATE_MISSION to Agents.
                    objects = dynamic_cast<HAMSTEREntity *>(this->GetUnit())->getEntityObjects(&number_objects);
                    logVerboseMessage("Sending TERMINATE_MISSION to agents.");
                    message = new comm::messaging::HAMSTERMessage(
                            comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
                            comm::messaging::HAMSTER_MESSAGE_CODE::TERMINATE_MISSION);
                    for (int i = 0; i < number_objects; i++) {
                        // If the object is connected, send the message
                        if(objects[i]->getUnitCommunicationInfo()->isConnected() == true){
                            message->setRecipient(objects[i]->getUnitCommunicationInfo());
                            // Add to pooler
                            this->getMessagePool()->addResponse2Pool(
                                    comm::messaging::HAMSTER_MESSAGE_CODE::TERMINATE_MISSION_ACK,
                                    objects[i]->getUnitID());
                            this->sendMessage(*message);
                        }
                    }
                    delete message;
                    this->setCurrentState(NP_MANAGER_STATE::TERMINATION);
                }
                break;
            case NP_MANAGER_STATE::TERMINATION:
                if(this->getMessagePool()->isAwaitingMessage(comm::messaging::HAMSTER_MESSAGE_CODE::TERMINATE_MISSION_ACK) == false){
                    // All answers were received
                    this->terminate();
                    logVerboseMessage("State Machine in NPManager finished.");
                }
                break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
    }while(this->isFinalized() == false);
    logVerboseMessage("NPManager ExecutionLoop() finished.");
};

void NPManager::platformTermination(void){

}

void NPManager::parseMessage(hamster::comm::messaging::HAMSTERMessage * msg){
    comm::messaging::HAMSTERMessage * response;
    comm::HAMSTERPeer * peer;
    utils::Uuid * received_id;
    char * message_buffer;
    int message_size;
    logDebugMessage("Message Received in NPManager: ", msg->getCode());
    switch(msg->getCode()){
        case comm::messaging::HAMSTER_MESSAGE_CODE::MISSION_CONFIGURATION:
            //\todo tratamento da mensagem quando houver serviços
//            msg->pullMessageField(&(this->entity_mission));
//            this->missionReceived();
//            if(msg->getDirection() == comm::messaging::HAMSTER_MESSAGE_DIRECTION::)
            break;
        case comm::messaging::HAMSTER_MESSAGE_CODE::MISSION_CONFIGURATION_ACK:
            this->getMessagePool()->messageReceived(msg->getCode(),msg->getRecipient()->GetID());
            break;
        case comm::messaging::HAMSTER_MESSAGE_CODE::TERMINATE_MISSION_ACK:
            this->getMessagePool()->messageReceived(msg->getCode(),msg->getRecipient()->GetID());
            break;
    }
}

//-----------------------------------------------------------------------------
// Get/Set methods
//-----------------------------------------------------------------------------
NP_MANAGER_STATE NPManager::getCurrentState() const{
    return current_state;
}
Mission * const NPManager::getMission(){
    return &(this->entity_mission);
}
void NPManager::setCurrentState(NP_MANAGER_STATE state){
    this->current_state = state;
    logVerboseMessage("NPManager state = ",state);
}
void NPManager::setMission(Mission my_mission){
    this->entity_mission = my_mission;
    this->missionReceived();
}


HAMSTER_RETURN NPManager::sendMissionToAgent(HAMSTERUnitDescriptor * agent){
    uint8_t num_phases = this->entity_mission.getNumberOfPhases();
    // Check if mission is valid
    if(num_phases == 0){
        logErrorMessage("Mission in NPManager has 0 phases.");
        return RETURN_NOK;
    }
    comm::messaging::HAMSTERMessage * msg = 
            new comm::messaging::HAMSTERMessage(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
            comm::messaging::HAMSTER_MESSAGE_CODE::MISSION_CONFIGURATION);
    // Put the number of phses
    msg->pushMessageField(&(this->entity_mission));
    msg->setRecipient(agent->getUnitCommunicationInfo());
    
    // Add to pooler
    this->getMessagePool()->addResponse2Pool(
            comm::messaging::HAMSTER_MESSAGE_CODE::MISSION_CONFIGURATION_ACK,
            agent->getUnitID());
    this->sendMessage(*msg);
    return HAMSTER_RETURN::RETURN_OK;
}

HAMSTER_RETURN NPManager::sendPhaseBehaviourToAgent(HAMSTERUnitDescriptor * agent){

    comm::messaging::HAMSTERMessage * msg = 
            new comm::messaging::HAMSTERMessage(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
            comm::messaging::HAMSTER_MESSAGE_CODE::CURRENT_BEHAVIOUR);
    // Put the phase number
    msg->pushMessageField(this->getMission()->getPhase(this->getCurrentPhaseNumber()));
    msg->setRecipient(agent->getUnitCommunicationInfo());
    
    // Add to pooler
    // \todo later
//    this->getMessagePool()->addResponse2Pool(
//            comm::messaging::HAMSTER_MESSAGE_CODE::MISSION_CONFIGURATION_ACK,
//            agent->getUnitID());
    this->sendMessage(*msg);
    return HAMSTER_RETURN::RETURN_OK;
}

HAMSTER_RETURN NPManager::sendPhaseNumberToAgent(HAMSTERUnitDescriptor * agent){
    comm::messaging::HAMSTERMessage * msg = 
            new comm::messaging::HAMSTERMessage(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
            comm::messaging::HAMSTER_MESSAGE_CODE::CURRENT_PHASE);
    // Put the number of phses
    msg->addInt8ToPayload(this->getCurrentPhaseNumber());
    msg->setRecipient(agent->getUnitCommunicationInfo());
    
    // Add to pooler
//    this->getMessagePool()->addResponse2Pool(
//            comm::messaging::HAMSTER_MESSAGE_CODE::MISSION_CONFIGURATION_ACK,
//            agent->getUnitID());
    this->sendMessage(*msg);
    return HAMSTER_RETURN::RETURN_OK;
}

void NPManager::nextPhase(void){
    
    HAMSTERObjectDescriptor ** objects;
    
    this->setCurrentPhaseNumber(this->getCurrentPhaseNumber() + 1);
    
    // Send these to agents
    uint8_t number_objects;
    objects = dynamic_cast<HAMSTEREntity *>(this->GetUnit())->getEntityObjects(&number_objects);
    logVerboseMessage("Mission Distribution in NPManager. Number of objects = ",
            toString(number_objects),". Sending mission to agents...");
    for (int i = 0; i < number_objects; i++) {
        // If the object is authorized, send the phase number
        if(objects[i]->getUnitCommunicationInfo()->isAuthorized() == true){
            this->sendPhaseNumberToAgent(objects[i]);
        }else{
            this->sendPhaseBehaviourToAgent(objects[i]);
        }
    }
}

}
}