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
 * \file   HAMSTERUnit.cc
 * \author: Mariana Rodrigues   rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#include "Unit.h"
#include "CommBroker.h"
//#include "CommInterface.h"
#include "HAMSTEREntity.h"
#include "FarashRegistraton.h"
#include <utility>

namespace hamster {

// Constructor/Destructor
Unit::Unit(char * config_file_name) {
    int integer_attribute;
    const char * string_attribute;
    TiXmlDocument config_file;
    
    // Load configuration file
    if(config_file.LoadFile(config_file_name) != true){
        utils::Uuid * temp_id = new utils::Uuid();
        this->ID.fromString(temp_id->toString());
        logErrorMessage("Error in loading configuration file in unit. Error description:",
                config_file.ErrorDesc(),"Random ID ",this->ID.toString()," created.");
    }else{
        // Read configuration file
        // 1. Read options
        TiXmlElement * options = config_file.FirstChildElement("OPTIONS");
        // 2. Read unit
        TiXmlElement * unit = options->NextSiblingElement();
        //  2.1 Unit Type
        unit->Attribute("UnitType",&integer_attribute);
        this->setType(hamster::integer2UnitType(integer_attribute));
        //  2.2 Unit ID
        string_attribute = unit->Attribute("ID");
        this->ID.fromString(string_attribute);
        //  2.3 Communication info
        this->communication_info = new HAMSTERUnitCommInfo(config_file_name,this);
        // Create unity platforms
        this->communication_broker = new comm::CommBroker(this,this->communication_info);
    }
    this->reg = new sample::registration::FarashRegistraton(this->ID);
}
Unit::~Unit() {
}
//-----------------------------------------------------------------------------    
// HAMSTERNode Methods
//-----------------------------------------------------------------------------
void Unit::initialize(void){
    // Step 1 - Initialize HAMSTER Platforms
    this->sphere_platform->platformInitialization();
//    if(this->nimble_platform != NULL){      // HAMSTER Entity or SuperEntity
//        this->nimble_platform->platformInitialization();
//    }
//    this->np_platform->platformInitialization();
//    this->nci_platform->platformInitialization();
    
    // Step 2 - Initialize all communication interfaces
    this->communication_info->initializeInterfaces();
    // Initialize Cryptography Algorithms
    this->communication_info->initializeCryptography();
    
    // Step 3 - Initialize communication broker
    this->communication_broker->platformInitialization();
    

    
    // Step 4 - Load threads of all platforms
    this->sphere_platform->platformLoop();
//    if(this->nimble_platform != NULL){      // HAMSTER Entity or SuperEntity
//        this->nimble_platform->platformLoop();
//    }
//    this->np_platform->platformLoop();
//    this->nci_platform->platformLoop();
    this->communication_info->loadInterfaceLoop();
    this->communication_broker->platformLoop();
    

}
comm::messaging::HAMSTERMessage * Unit::getIDMessage(comm::HAMSTERPeer * peer){//>>>>ID MEssage
    comm::messaging::HAMSTERMessage * id_message = 
            new comm::messaging::HAMSTERMessage(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
            comm::messaging::HAMSTER_MESSAGE_CODE::HAMSTER_UNIT_ID);
    std::vector<unsigned char> my_reg;
    if(this->getType() == HAMSTER_UNIT_TYPE::SUPER_ENTITY){
        utils::Uuid pid = peer->GetID();
        my_reg = reg->issueRegistration(&pid);
    }else{
        my_reg = reg->issueRegistration(NULL);
    }
    id_message->copyToPayload((char *) my_reg.data(),my_reg.size());

//    id_message->pushMessageField(this->getCommunicationInfo()->getMyKey());
    std::cout << "Message Paylod: " << std::endl;
    id_message->printPayload();
    return id_message;
}

 bool Unit::startCustomExecution(){
    return (this->sphere_platform->setupFinished());
//     return true;
}
//-----------------------------------------------------------------------------
// GET Operators
//-----------------------------------------------------------------------------
hamster::utils::Uuid Unit::getID() const {
    return ID;
}
hamster::HAMSTER_UNIT_TYPE Unit::getType() const {
    return type;
}
 comm::CommBroker* Unit::getCommunicationBbroker() const{
    return this->communication_broker;
}
sphere::SPHERE* Unit::getSPHEREPlatform() const {
    return sphere_platform;
}
//nci::NCI* Unit::getNCIPlatform() const {
//    return nci_platform;
//}
nimble::NIMBLE* Unit::getNIMBLEPlatform() const {
    return nimble_platform;
}
navigation_phases::NPUnit* Unit::getNPPlatform() const {
    return np_platform;
}
comm::interface::CommInterface * Unit::getInterface(int index){
    return this->communication_info->getInterface(index);
}
//-----------------------------------------------------------------------------
// SET Operators
//-----------------------------------------------------------------------------
void Unit::setType(hamster::HAMSTER_UNIT_TYPE type) {
    this->type = type;
}
    
// void HAMSTERUnit::setCommunicationBroker(comm::CommBroker* communication_broker) {
//    this->communication_broker = communication_broker;
//}

//void Unit::setNCIPlatform(nci::NCI* nci_platform) {
//    this->nci_platform = nci_platform;
//}

void Unit::setNIMBLEPlatform(nimble::NIMBLE* nimble_platform) {
    this->nimble_platform = nimble_platform;
}

void Unit::setNPPlatform(navigation_phases::NPUnit* np_platform) {
    this->np_platform = np_platform;
}

void Unit::setSPHEREPlatform(sphere::SPHERE* sphere_platform) {
    this->sphere_platform = sphere_platform;
}

//-----------------------------------------------------------------------------
// Ohter Methods
//-----------------------------------------------------------------------------
std::ostream& Unit::printNode(std::ostream& stream) const{
    stream << "\tType: " << this->getType() << std::endl;
    stream << "\tID: " << this->getID() << std::endl;
    return stream;
}
HAMSTER_RETURN Unit::AddPeer(comm::HAMSTERPeer * peer){
    return this->communication_info->AddPeer(peer);
}

} /* namespace hamster */