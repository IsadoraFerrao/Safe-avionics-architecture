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
 * \file   HAMSTERSuperEntity.cc
 * \author: Mariana Rodrigues   rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#include "HAMSTERSuperEntity.h"
#include "SuperSPHERE.h"
#include "NCIEntity.h"
#include "NPManager.h"
#include "NIMBLE.h"
#include "CommInterface.h"
#include "INETSocketAddressInfo.h"

namespace hamster{
//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
HAMSTERSuperEntity::HAMSTERSuperEntity(char * config_file_name) : HAMSTEREntity(config_file_name) {
    
    bool centralized,known_formation;
    int integer_attribute, num_elements;
    TiXmlDocument config_file(config_file_name);
    
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
        TiXmlElement * unit_element = options->NextSiblingElement("UNIT");    // 'Unit' element
        if(known_formation == true){
            // 2. Read System elements
            TiXmlElement * system_elements = unit_element->FirstChildElement("interfaces"); // Interfaces
            system_elements = system_elements->NextSiblingElement("Elements"); // Elements
            system_elements->Attribute("Total",&num_elements);
            TiXmlElement * element = system_elements->FirstChildElement("Element");
            for (int i = 0; i < num_elements; i++) {
                utils::Uuid id;
                id.fromString(element->Attribute("ID"));
                element->Attribute("Interface",&integer_attribute);
                comm::interface::CommInterface * element_interface = this->getInterface(integer_attribute);
                comm::interface::AddressInfo * element_address;
                switch(element_interface->getTechnology()){
                    case comm::interface::COMM_INTERFACE_TECH::WIFI:
//                        super_address = new WifiAddressInfo();
                        break;
                    case comm::interface::COMM_INTERFACE_TECH::ETHERNET:
                        break;
                    case comm::interface::COMM_INTERFACE_TECH::SOCKET:
                        element->Attribute("Port",&integer_attribute);
                        element_address = new comm::interface::inet_socket::INETSocketAddressInfo((char *) element->Attribute("IPAddress"),integer_attribute);
                        break;
                    default:
                        break;
                }
                // Add element to list
                this->AddPeer(new comm::HAMSTERPeer(element_interface,element_address,id));
                element = element->NextSiblingElement();
            }
        }else{
            // Centralized, unknown formation.
        }
        // Create entity platforms
        this->setSPHEREPlatform(new sphere::SuperSPHERE(this,this->getCommunicationInfo()));
       // this->setNCIPlatform(new nci::NCIEntity(this,this->getCommunicationInfo()));
        this->setNPPlatform(new navigation_phases::NPManager(this,this->getCommunicationInfo()));
        this->setNIMBLEPlatform(new nimble::NIMBLE(this,this->getCommunicationInfo()));
        logDebugMessage("New HAMSTERSuperEntity. ID = ", this->getID().toString());
    }
    // \todo Consertar aqui
//    logDebugMessage("New HAMSTERSuperEntity. ID = ",id);
}
HAMSTERSuperEntity::~HAMSTERSuperEntity() {}

//-----------------------------------------------------------------------------
// HAMSTERNode Methods
//-----------------------------------------------------------------------------
void HAMSTERSuperEntity::initialize(void){
    HAMSTEREntity::initialize();
//    this->customInitialization();
    logDebugMessage("SuperEntity Initialization. Unit ID = ",this->getID().toString());
}
void HAMSTERSuperEntity::execute(void){
    // Wait for platforms to get to executing
    this->customInitialization();
    while(this->startCustomExecution() == false){
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
    }
//           this->customInitialization();
//    std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
    do{
        this->customExecution();
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS*10));
    }while(this->terminate == false);
};
void HAMSTERSuperEntity::nodeTermination(void){};

} /* namespace hamster */