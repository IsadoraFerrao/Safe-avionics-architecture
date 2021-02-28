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
 * \file    CommBroker.cc
 * \author: Mariana Rodrigues   rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#include "CommBroker.h"
#include "Unit.h"
#include "NCI.h"
#include "NIMBLE.h"
#include "NPUnit.h"
#include "SPHERE.h"
#include "CommInterface.h"


namespace hamster{
namespace comm{

CommBroker::CommBroker(Unit * unit,HAMSTERUnitCommInfo * info):HAMSTERPlatform(unit,info){
    logDebugMessage("CommBroker created. Unit ID = ", unit->getID());
}

CommBroker::~CommBroker() {
}

//-----------------------------------------------------------------------------
// HAMSTERPlatform methods
//-----------------------------------------------------------------------------
void CommBroker::platformInitialization(void){
    HAMSTERQueue * my_incoming = new HAMSTERQueue();
    
    // Initialize own incoming queue
    this->SetIncomingQueue(my_incoming);
    // Set CSU queues
    this->GetUnit()->getSPHEREPlatform()->csu_module->SetOutgoingQueue(my_incoming);
    this->csu_queue = this->GetUnit()->getSPHEREPlatform()->csu_module->GetIncomingQueue();
    // Set SMU queues
    this->GetUnit()->getSPHEREPlatform()->smu_module->SetOutgoingQueue(my_incoming);
    this->smu_queue = this->GetUnit()->getSPHEREPlatform()->smu_module->GetIncomingQueue();
    // Set SEMU queues
    this->GetUnit()->getSPHEREPlatform()->NCI_module->SetOutgoingQueue(my_incoming);
    this->NCI_queue = this->GetUnit()->getSPHEREPlatform()->NCI_module->GetIncomingQueue();
    // Set SEMU queues
    this->GetUnit()->getSPHEREPlatform()->semu_module->SetOutgoingQueue(my_incoming);
    this->semu_queue = this->GetUnit()->getSPHEREPlatform()->semu_module->GetIncomingQueue();
    // Set NCI queues
   // this->GetUnit()->getNCIPlatform()->SetOutgoingQueue(my_incoming);
    //this->nci_queue = this->GetUnit()->nci_platform->GetIncomingQueue();
    // Set NP queues
    this->GetUnit()->getNPPlatform()->SetOutgoingQueue(my_incoming);
    this->np_queue = this->GetUnit()->getNPPlatform()->GetIncomingQueue();
    // Set NIMBLE queues
    if(this->GetUnit()->getNIMBLEPlatform() != NULL){
        this->GetUnit()->getNIMBLEPlatform()->SetOutgoingQueue(my_incoming);
        this->nimble_queue = this->GetUnit()->nimble_platform->GetIncomingQueue();
    }
    // Set Interfaces queues
    this->interface_queues = new HAMSTERQueue*[this->my_unit_comm_info->getNumInterfaces()]; 
    for (int i = 0; i < this->my_unit_comm_info->getNumInterfaces(); i++) {
        comm::interface::CommInterface * interface = this->my_unit_comm_info->getInterface(i+1);
        interface->SetOutgoingQueue(my_incoming);
        this->interface_queues[i] = interface->GetIncomingQueue();
    }
    logDebugMessage("CommBroker initialization.");
}

void CommBroker::executionLoop(void){
    logDebugMessage("CommBroker Loop init.");
    do{
//        logDebugMessage("CommBroker Loop");
        if(!this->GetIncomingQueue()->isEmpty()){
            comm::messaging::HAMSTERMessage * msg = this->GetIncomingQueue()->popMessage();
            this->parseMessage(msg);
            delete msg;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
    }while(this->finalize == false);
}

void CommBroker::platformTermination(void){
    logDebugMessage("CommBroker termination.");
}

void CommBroker::parseMessage(hamster::comm::messaging::HAMSTERMessage * msg){
    logDebugMessage("CommBroker parse message. Code = ",msg->getCode());
    uint8_t message_header;
      
    // Verify if the message is internal or external
    if(msg->getDirection() == messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL){
        // External message --- redirect it to the proper interface
        msg->getRecipient()->GetInterface()->incoming_queue->pushMessage(*msg);
        logDebugMessage("CommBroker push external message");
    }else{
        // Internal message
        logDebugMessage("CommBroker received internal message");
        // Get index to point to header
        msg->rewind();
        // Verify if is a user message
        if(msg->getCode() == messaging::HAMSTER_MESSAGE_CODE::HAMSTER_USER_MSGS){
            logDebugMessage("CommBroker --- Internal user message");
            utils::Uuid id(msg->getRecipient()->GetID());
            this->GetUnit()->processMessage(id,msg->getUserMessage());
        }else{ //HAMSTER internals --- Get header to route
            message_header = ((messaging::HAMSTERMessage *)msg)->getHeader();
            // Is it unit message?
            if((message_header == messaging::HAMSTER_MESSAGE_MASKS::UNIT_MASK)){
                this->GetUnit()->parseMessage(msg);
            }
            // Is it broadcast?
            if((message_header == messaging::HAMSTER_MESSAGE_MASKS::PLATFORM_MASK)){
                // Redirect message to all platforms
                this->csu_queue->pushMessage(*msg);
                this->smu_queue->pushMessage(*msg);
                this->NCI_queue->pushMessage(*msg);
                this->semu_queue->pushMessage(*msg);
               
                if(this->GetUnit()->getNIMBLEPlatform() != NULL){
                    this->nimble_queue->pushMessage(*msg);
                }
                this->np_queue->pushMessage(*msg);
            }else{
                // Redirect message to correct platform
                switch(message_header & messaging::HAMSTER_MESSAGE_MASKS::PLATFORM_MASK){
                    case messaging::HAMSTER_MESSAGE_MASKS::CSU_MASK:
                        this->csu_queue->pushMessage(*msg);
                        break;
                        
                    case messaging::HAMSTER_MESSAGE_MASKS::SMU_MASK:
                        this->smu_queue->pushMessage(*msg);
                        break;
                        this->NCI_queue->pushMessage(*msg);
                        break;
                    case messaging::HAMSTER_MESSAGE_MASKS::SEMU_MASK:
                        this->semu_queue->pushMessage(*msg);
                        break;
                    
                    case messaging::HAMSTER_MESSAGE_MASKS::NIMBLE_MASK:
                        if(this->GetUnit()->getNIMBLEPlatform() != NULL){
                            this->nimble_queue->pushMessage(*msg);
                        }else{
                            logErrorMessage("NIMBLE message with code ",
                                    (uint32_t) msg->getCode()," arrived at HAMSTER Object ID = ",
                                    this->GetUnit()->getID());
                        }
                        break;
                    case messaging::HAMSTER_MESSAGE_MASKS::NP_MASK:
                        this->np_queue->pushMessage(*msg);
                        break;
                    default:
                        logErrorMessage("Message with wrong direction code received. Code = ",
                            (uint32_t) msg->getCode(),", Unit ID = ",this->GetUnit()->getID());
                        break;
                }
            }
        }
    }
                logDebugMessage("CommBroker leavinfParse");
                
                
}

std::ostream& CommBroker::printPlatform(std::ostream& stream) const{
    stream << "Communication broker." << std::endl;
    stream << "Unit:" << this->GetUnit();
    return stream;
}

} /* namespace comm */
} /* namespace hamster */