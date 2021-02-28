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
 * \file   HAMSTERObject.cc
 * \author: Mariana Rodrigues   rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#include "HAMSTERObject.h"
#include "LocalSPHERE.h"
#include "NPAgent.h"

namespace hamster {
    

    
//-----------------------------------------------------------------------------
// Constructor/Destructor
//-----------------------------------------------------------------------------
    HAMSTERObject::HAMSTERObject(char * config_file_name): Unit(config_file_name){
        int integer_attribute;
        const char * string_attribute;
        TiXmlDocument config_file;

        // Load configuration file
        if(config_file.LoadFile(config_file_name) != true){
            utils::Uuid * temp_id = new utils::Uuid();
            this->getID().fromString(temp_id->toString());
            logErrorMessage("Error in loading configuration file in unit. Error description:",
                    config_file.ErrorDesc(),"Random ID ",this->getID().toString()," created.");
        }else{
            // Read Components
            TiXmlElement * unit_element = config_file.FirstChildElement("UNIT");
            TiXmlElement * components_element = unit_element->FirstChildElement("Components");
            components_element->Attribute("NumComponents",&integer_attribute);
            num_components = integer_attribute & 0xFF;
            my_components = new HAMSTERUVComponent[num_components];
            TiXmlElement * component_element = components_element->FirstChildElement("Component");
            for(int i = 0; i < num_components; i++){
                my_components[i].readFromXMLElement(component_element);
                component_element = component_element->NextSiblingElement();
            }
        }
        // Create Platforms --- NCI platform is created in Cluster or Module.
        this->setNPPlatform(new hamster::navigation_phases::NPAgent(this,this->getCommunicationInfo()));;
        this->setSPHEREPlatform(new hamster::sphere::LocalSPHERE(this,this->getCommunicationInfo()));
    }

    HAMSTERObject::~HAMSTERObject() {
    }
    
//------------------------------------------------------------------------------
// HAMSTER Node methods
//------------------------------------------------------------------------------
void HAMSTERObject::initialize(void){
    // Initialize unit
    Unit::initialize();
    // Initialize user application
    logDebugMessage("Object Initialization. ID = ",this->getID().toString());
};
void HAMSTERObject::execute(void){
    // Wait for platforms to get to executing
    while(this->startCustomExecution() == false){
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
    }
    this->customInitialization();
    do{
        this->customExecution();
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
    }while(this->terminate == false);
};

void HAMSTERObject::nodeTermination(void){};

void HAMSTERObject::applyPhaseBehaviour(navigation_phases::PhaseBehaviour phase){
    for (int i = 0; i < this->num_components; i++) {
        if(my_components[i].getClassification() == HAMSTERUVComponent::COMPONENT_CLASSIFICATION::MISSION_SPECIFIC){
            this->setComponentState(my_components[i].getNumber(),phase.getMissionComponentState());
        }else{
            this->setComponentState(my_components[i].getNumber(),phase.getMainComponentState());
        }
    }
}
    
void HAMSTERObject::setComponentState(uint8_t number, HAMSTER_COMPONENT_STATE state){
    for(int i = 0; i < this->num_components; i++){
        if(my_components[i].getNumber() == number){
            HAMSTER_FUNCTIONAL_CODE component_code = my_components[i].getCode();
            if(state == HAMSTER_COMPONENT_STATE::COMPONENT_ON){
                this->turnComponentON(component_code);
                logEventMessage("Component ",component_code," turned ON.");
            }else{
                this->turnComponentOFF(component_code);
                logEventMessage("Component ",component_code," turned OFF.");
            }
            my_components[i].setState(state);
            return;
        }
    }
    logErrorMessage("Component number ",number," not found");
}

//-----------------------------------------------------------------------------
// HAMSTER Node methods
//-----------------------------------------------------------------------------
    std::ostream& HAMSTERObject::printNode(std::ostream& stream) const{
        hamster::Unit::printNode(stream);
        // HAMSTER Entity specific data may be inserted.
        return stream;
    }

} /* namespace hamster */