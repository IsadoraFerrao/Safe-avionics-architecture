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

/* 
 * \file:   Mission.cc
 * \author: rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#include "Mission.h"
#include "PhaseBehaviour.h"
#include "HAMSTERMessage.h"

namespace hamster{ 
namespace navigation_phases{

Mission::Mission() {
    logVerboseMessage("Mission constructor.");
}

Mission::Mission(uint8_t num_phases):number_of_phases(num_phases){
    this->mission_phases = new NavigationPhase[number_of_phases];
}

Mission::~Mission() {
    logVerboseMessage("Mission descructor.");
//    delete mission_phases;
//    this->mission_phases = NULL;
}

//     * 1. Number of phases,
//     * 2. For each phase:
//     * 2.1 Phase number
//     * 2.2 Main components state,
//     * 2.3 Required component state,
//     * 2.4 Emergency state
int Mission::pushInPayload(char ** buffer){
    int used_bytes = 0;
    used_bytes += comm::messaging::HAMSTERMessage::pushInt8IntoPayload(buffer,this->number_of_phases);
    char * temp_ptr = &(*buffer)[used_bytes];
    // Put the information on each phase
    for (int i = 0; i < this->number_of_phases; i++) {
        used_bytes += this->mission_phases[i].getComponentBehaviour()->pushInPayload(&temp_ptr);
        temp_ptr = &(*buffer)[used_bytes];
    }
    return used_bytes;
}

int Mission::pullFromPayload(char * buffer){
    int used_bytes = 0;
    uint8_t num_phases;
    used_bytes += comm::messaging::HAMSTERMessage::pullInt8FromPalyload(buffer,&(num_phases));
    this->setNumberOfPhases(num_phases);

    // Put the information on each phase
    for (int i = 0; i < this->number_of_phases; i++) {
        used_bytes += this->mission_phases[i].getComponentBehaviour()->pullFromPayload(&(buffer[used_bytes]));
    }
    return used_bytes;
}

 Mission& Mission::operator=(Mission& other){
     this->setNumberOfPhases(other.number_of_phases);
     for (int i = 0; i < this->number_of_phases; i++) {
         this->mission_phases[i] = other.mission_phases[i];
     }
     return *this;
 }

HAMSTER_RETURN Mission::addPhase(NavigationPhase new_phase){
    // Check if the vector exists
    if(this->mission_phases == NULL){
        logErrorMessage("Number of phases in the mission not determined.");
        return RETURN_NOK;
    }
    // If exists, check the size
    if(this->number_of_phases < new_phase.getComponentBehaviour()->getNumber()){
        logErrorMessage("Mission phase number higher than the total number of phases.");
        return RETURN_NOK;
    }
    
    // If exists and the size is OK, copy data
    this->mission_phases[new_phase.getComponentBehaviour()->getNumber() - 1] = new_phase;
    return RETURN_OK;
}

void Mission::setNumberOfPhases(uint8_t num_phases){
    this->number_of_phases = num_phases;
    this->mission_phases = new NavigationPhase[num_phases];
}

uint8_t Mission::getNumberOfPhases() const{
    return this->number_of_phases;
}

NavigationPhase * const Mission::getPhase(uint8_t number) const{
    // Check if the vector exists
    if(this->mission_phases == NULL){
        logErrorMessage("Number of phases in the mission not determined.");
        return NULL;
    }
    // If exists, check the size
    if(this->number_of_phases < number){
        logErrorMessage("Mission phase number higher than the total number of phases.");
        return NULL;
    }
    
    // If exists and the size is OK, copy data
    for (int i = 0; i < this->number_of_phases; i++) {
        if(this->mission_phases[i].getComponentBehaviour()->getNumber() == number){
            return &(mission_phases[i]);
        }
    }
    return nullptr;
}

} /* namespace navigation_phases */
} /* namespace hamster */