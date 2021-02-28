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
 * \file   HAMSTEREntity.cc
 * \author: Mariana Rodrigues   rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#include "HAMSTEREntity.h"
#include "NCI.h"
#include "NCIEntity.h"
#include "NPManager.h"
#include "NIMBLE.h"
#include "CommBroker.h"
#include "INETSocketAddressInfo.h"
#include "HAMSTERObject.h"
#include <cstring>
#include <type_traits>
#include <iostream>

namespace hamster {
//------------------------------------------------------------------------------
// Constructor/Destructor
//------------------------------------------------------------------------------
HAMSTEREntity::HAMSTEREntity(char * config_file_name): Unit(config_file_name){

    bool centralized,known_formation;
    int integer_attribute, num_objects, port_number;
    TiXmlDocument config_file;
    
    // Load configuration file
    if(config_file.LoadFile(config_file_name) != true){
        utils::Uuid * temp_id = new utils::Uuid();
        this->getID().fromString(temp_id->toString());
        logErrorMessage("Error in loading configuration file in unit. Error description:",
                config_file.ErrorDesc(),"Random ID ",this->getID().toString()," created.");
    }else{
        // Read configuration file
        // 1. Read options
        TiXmlElement * options = config_file.FirstChildElement("OPTIONS");
        options->QueryBoolAttribute("CENTRALIZED",&centralized);
        options->QueryBoolAttribute("KNOWN_FORMATION",&known_formation);
        TiXmlElement * unit_element = options->NextSiblingElement();    // 'Unit' element
        unit_element->Attribute("UnitType",&integer_attribute);
        HAMSTER_UNIT_TYPE temp_type = integer2UnitType(integer_attribute);

        // Read objects
        TiXmlElement * objects_element = unit_element->FirstChildElement("Objects");
        // Get the number of objects
        objects_element->Attribute("NumObjects",&num_objects);
        this->number_of_objects = num_objects;
        TiXmlElement * object_element = objects_element->FirstChildElement("Object");
        for(int i = 0; i < num_objects; i++){
            utils::Uuid id;
            id.fromString(object_element->Attribute("ID"));
            TiXmlElement * interface_element = object_element->FirstChildElement("Interface");
            interface_element->Attribute("Number",&integer_attribute);
            comm::interface::CommInterface * object_interface = this->getInterface(integer_attribute);
            comm::interface::AddressInfo * object_address;
            switch(object_interface->getTechnology()){
                case comm::interface::COMM_INTERFACE_TECH::WIFI:
//                        super_address = new WifiAddressInfo();
                    break;
                case comm::interface::COMM_INTERFACE_TECH::ETHERNET:
                    break;
                case comm::interface::COMM_INTERFACE_TECH::SOCKET:
                    interface_element->Attribute("Port",&integer_attribute);
                    object_address = new comm::interface::inet_socket::INETSocketAddressInfo((char *) interface_element->Attribute("IPAddress"),integer_attribute);
                    break;
                default:
                    break;
            }
            // Add object to peer list in communication info and to objects list
            comm::HAMSTERPeer * object_peer_info = new comm::HAMSTERPeer(object_interface,object_address,id);
            //>>> JINT - Secret Key
            unsigned char hash_result[32];
            unsigned long outlen;
            int result = hash_memory(find_hash("sha256"),(const unsigned char *) id.toString().c_str(),id.toString().size(),hash_result,&outlen);
            if(result != CRYPT_OK){
                logErrorMessage("Could not hash, error code  = ",(int) result);
            }else{
                object_peer_info->SetSecret(hash_result);
            }
            this->AddPeer(object_peer_info);
            object_element->Attribute("UnitType",&integer_attribute);
            HAMSTERObjectDescriptor * obj_descriptor = new HAMSTERObjectDescriptor(id,hamster::integer2UnitType(integer_attribute));
            if(hamster::integer2UnitType(integer_attribute) == HAMSTER_UNIT_TYPE::CLUSTER){
                // Read the number of components
                object_element->Attribute("NumComponents",&integer_attribute);
            }
            else{
                // HAMSTER Modules have a single component
                integer_attribute = 1;
            }
            // Read components
            obj_descriptor->setNumComponents((uint8_t) integer_attribute);
            HAMSTERUVComponent * obj_components = obj_descriptor->getComponents();
            TiXmlElement * component_element = object_element->FirstChildElement("Component");
            obj_descriptor->setClassification(HAMSTERUVComponent::COMPONENT_CLASSIFICATION::MISSION_SPECIFIC);
            for(int j = 0 ; j < integer_attribute; j++){
                obj_components[i].readFromXMLElement(component_element);
                if(obj_components[i].getClassification() == HAMSTERUVComponent::COMPONENT_CLASSIFICATION::REQUIRED_FOR_OPERATION){
                    obj_descriptor->setClassification(HAMSTERUVComponent::COMPONENT_CLASSIFICATION::REQUIRED_FOR_OPERATION);
                }
                component_element = component_element->NextSiblingElement("Component");
            }
            obj_descriptor->setUnitCommunicationInfo(object_peer_info);
            // Add object
            this->addObject(obj_descriptor);
            // Next in list
            object_element = object_element->NextSiblingElement();
        }

        if(temp_type == HAMSTER_UNIT_TYPE::ENTITY){
            // Read Entity data. Not applicable for SuperEntity.
            if(centralized == true){
                // Anything specific?
            }else if(known_formation == true){
                // Read entity's HAMSTER Peers
            }else{
                // Decentralized, unknown formation.
            }
            // Create entity platforms
            this->setSPHEREPlatform(new sphere::CentralSPHERE(this,this->getCommunicationInfo()));
            //this->setNCIPlatform(new nci::NCIEntity(this,this->getCommunicationInfo()));
            this->setNPPlatform(new navigation_phases::NPManager(this,this->getCommunicationInfo()));
            this->setNIMBLEPlatform(new nimble::NIMBLE(this,this->getCommunicationInfo()));
            logDebugMessage("New HAMSTEREntity. ID = ", this->getID().toString());
        }
    }
}
HAMSTEREntity::~HAMSTEREntity() {
}
//------------------------------------------------------------------------------
// HAMSTER Node methods
//------------------------------------------------------------------------------
void HAMSTEREntity::initialize(void){
    // Initialize unit
    Unit::initialize();
    // Initialize user application
    logDebugMessage("Entity Initialization. ID = ",this->getID().toString());
};
void HAMSTEREntity::execute(void){
    // Wait for platforms to get to executing
    while(this->startCustomExecution() == false){
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS*2));
    this->customInitialization();
    do{
        this->customExecution();
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
    }while(this->terminate == false);
};
//-----------------------------------------------------------------------------
// Object list Methods
//-----------------------------------------------------------------------------
HAMSTER_RETURN HAMSTEREntity::addObject(HAMSTERObjectDescriptor * description){
    std::pair<utils::Uuid,HAMSTERObjectDescriptor *> toinsert(description->getUnitID(),description);
    std::pair<std::map<utils::Uuid,HAMSTERObjectDescriptor *>::iterator,bool> ret = this->entity_objects.insert(toinsert);
    
//    ret = this->peer_list.insert(std::pair<utils::Uuid,comm::HAMSTERPeer *>(peer->GetID(),peer));
    if(ret.second == false){
//        logWarningMessage("Duplicated Peer (ID = ",peer->GetID().toString(),
//                ") inserted in peer list of Unit ID = ",this->getID().toString());
        return RETURN_NOK;
    }
    return RETURN_OK;
}

bool HAMSTEREntity::objectExists(utils::Uuid id){
    std::map<utils::Uuid,HAMSTERObjectDescriptor *>::iterator it;
    it = this->entity_objects.find(id);
    return (it != this->entity_objects.end());
}

comm::HAMSTERPeer * HAMSTEREntity::getPeerFromID(utils::Uuid id){
    std::map<utils::Uuid,HAMSTERObjectDescriptor *>::iterator it;
    it = this->entity_objects.find(id);
    if(it != this->entity_objects.end()){
        return it->second->getUnitCommunicationInfo();
    }
    return NULL;
}

void HAMSTEREntity::putMessageInBroker(comm::messaging::HAMSTERMessage * msg){
    this->getCommunicationBbroker()->parseMessage(msg);
}

bool HAMSTEREntity::areAllRequiredObjectsAuthenticated(){
    // Iterate over the object map using c++11 range based for loop
    for (std::pair<utils::Uuid,HAMSTERObjectDescriptor *> element : this->entity_objects) {
        if((element.second->isRequired() == true) && (element.second->getUnitCommunicationInfo()->isAuthorized() == false)){
            return false;
        }
    }
    return true;
}

bool HAMSTEREntity::areAllObjectsConnected(){
    // Iterate over the object map using c++11 range based for loop
    for (std::pair<utils::Uuid,HAMSTERObjectDescriptor *> element : this->entity_objects) {
        if(element.second->getUnitCommunicationInfo()->isConnected() == false){
            return false;
        }
    }
    return true;
}

void HAMSTEREntity::parseMessage(comm::messaging::HAMSTERMessage * msg){
    switch(msg->getCode()){
        case comm::messaging::HAMSTER_MESSAGE_CODE::HAMSTER_SETUP_FINISHED:
            this->initializationFinished();
            break;
    }
}

void HAMSTEREntity::nodeTermination(void){};
std::ostream& HAMSTEREntity::printNode(std::ostream& stream) const{
    return hamster::Unit::printNode(stream);
    // HAMSTER Entity specific data may be inserted.
}


} /* namespace hamster */