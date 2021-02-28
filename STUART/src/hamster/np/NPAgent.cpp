/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NPAgent.cpp
 * Author: Mariana
 * 
 * Created on 30 de Março de 2018, 12:51
 */

#include "NPAgent.h"
#include "HAMSTERObject.h"

namespace hamster{
    namespace navigation_phases{

NPAgent::NPAgent(Unit * unit,HAMSTERUnitCommInfo * info):NPUnit(unit,info) {
}


NPAgent::~NPAgent() {
}

void NPAgent::executionLoop(void){
    logDetailedMessage("NPAgent executionLoop() started.");
    comm::messaging::HAMSTERMessage * message;
    comm::HAMSTERPeer * unit;

    do{
        // Verify new messages
        if(!this->GetIncomingQueue()->isEmpty()){
            comm::messaging::HAMSTERMessage * msg = this->GetIncomingQueue()->popMessage();
            this->parseMessage(msg);
            delete msg;
        }
        switch(this->getCurrentState()){
            case NP_AGENT_STATE::INITIAL:
                // Do something
                this->setCurrentState(NP_AGENT_STATE::AWAITING_MISSION);
                break;
            case NP_AGENT_STATE::AWAITING_MISSION:
                if(this->missionWasReceived() == true){
                    this->setCurrentState(NP_AGENT_STATE::MISSION_START);
//                    this->setupFinished();
                }
                break;
            case NP_AGENT_STATE::MISSION_START:
                break;
            case NP_AGENT_STATE::MISSION_OPERATION:
                break;
            case NP_AGENT_STATE::MISSION_TERMINATION:
                this->setCurrentState(NP_AGENT_STATE::TERMINATION);
                break;
            case NP_AGENT_STATE::TERMINATION:
                logEventMessage("Mission finished.");
                this->terminate();
                break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
    }while(this->isFinalized() == false);
    logDetailedMessage("NPAgent executionLoop() finished.");
}


void NPAgent::parseMessage(hamster::comm::messaging::HAMSTERMessage * msg){
    comm::messaging::HAMSTERMessage * response;
    comm::HAMSTERPeer * peer;
    utils::Uuid * received_id;
    char * message_buffer;
    int message_size;
    uint8_t integer_argument;
    PhaseBehaviour * behaviour;
    logDebugMessage("Message Received in NPAgent: ", msg->getCode());
    
    switch(msg->getCode()){
        case comm::messaging::HAMSTER_MESSAGE_CODE::MISSION_CONFIGURATION:
//            logEventMessage("Message MISSION_CONFIGURATION received.");
            //     * 1. Number of phases,
            //     * 2. For each phase:
            //     * 2.1 Phase number
            //     * 2.2 Main components state,
            //     * 2.3 Required component state,
            msg->extractInt8FromPayload(&(this->number_phases));
            this->mission_behaviour = new PhaseBehaviour[this->number_phases];
            for (int i = 0; i < this->number_phases; i++) {
                msg->pullMessageField(&(mission_behaviour[i]));
            }
            this->missionReceived();
            // Send response
            response = new comm::messaging::HAMSTERMessage(
                    comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
                    comm::messaging::HAMSTER_MESSAGE_CODE::MISSION_CONFIGURATION_ACK);
            response->setRecipient(msg->getRecipient());
            this->sendMessage(*response);
            break;
        case comm::messaging::HAMSTER_MESSAGE_CODE::CURRENT_PHASE:
            if(this->getCurrentState() == NP_AGENT_STATE::MISSION_START){
                this->setCurrentState(NP_AGENT_STATE::MISSION_OPERATION);
            }
            msg->extractInt8FromPayload(&integer_argument);
            this->setCurrentPhaseNumber(integer_argument);
            behaviour = this->getCurrentPhaseBehaviour();
            static_cast<HAMSTERObject *>(this->GetUnit())->applyPhaseBehaviour(*behaviour);
            break;
        case comm::messaging::HAMSTER_MESSAGE_CODE::CURRENT_BEHAVIOUR:
            this->setCurrentState(NP_AGENT_STATE::MISSION_OPERATION);
            behaviour = new PhaseBehaviour();
            msg->pullMessageField(behaviour);
            static_cast<HAMSTERObject *>(this->GetUnit())->applyPhaseBehaviour(*behaviour);
            delete behaviour;
            break;
        case comm::messaging::HAMSTER_MESSAGE_CODE::TERMINATE_MISSION:
            if(this->getCurrentState() == NP_AGENT_STATE::MISSION_OPERATION){
                this->setCurrentState(NP_AGENT_STATE::MISSION_TERMINATION);
                response = new comm::messaging::HAMSTERMessage(
                        comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
                        comm::messaging::HAMSTER_MESSAGE_CODE::TERMINATE_MISSION_ACK);
                response->setRecipient(msg->getRecipient());
                sendMessage(*response);
                delete response;
            }else{
                logWarningMessage("Message TERMINATE_MISSION received outside state MISSION_OPERATION in NPAgent. Message Ignored.");
            }
        default:
            logWarningMessage("Unrecognized message in NPAgent.");
            break;
    }
}

NP_AGENT_STATE NPAgent::getCurrentState() const {
    return current_state;
}

void NPAgent::setCurrentState(NP_AGENT_STATE current_state) {
    this->current_state = current_state;
    logVerboseMessage("NP Agent current state = ",current_state);
}

PhaseBehaviour * const NPAgent::getCurrentPhaseBehaviour(void){
    for (int i = 0; i < this->number_phases; i++) {
        if(this->mission_behaviour[i].getNumber() == this->getCurrentPhaseNumber()){
            return &(this->mission_behaviour[i]);
        }
    }
    logErrorMessage("Received phase number not valid.");
    return NULL;
}

    } /* namespace navigation_phases */
} /* namespace hamster */