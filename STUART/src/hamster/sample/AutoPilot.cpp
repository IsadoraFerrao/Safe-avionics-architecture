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
 * \file      Autopilot.cpp
 * \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#include "Autopilot.h"

namespace hamster{
namespace sample{
    
//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
Autopilot::Autopilot(char * config_file_name):HAMSTERModule(config_file_name) {}
Autopilot::~Autopilot() {}

//-----------------------------------------------------------------------------
// Overloaded HAMSTERPlatform methods
//-----------------------------------------------------------------------------
void Autopilot::customInitialization(void){
    logDetailedMessage("Autopilot customInitialization() method");
}
void Autopilot::customExecution(void){
    logDetailedMessage("Autopilot customExecution() method.");
}
void Autopilot::customTermination(void){
    logDetailedMessage("Autopilot customTermination() method.");
}
void Autopilot::processMessage(utils::Uuid& peer_id, char * message){
    logDetailedMessage("Autopilot processMessage(message) method.");
}
//-----------------------------------------------------------------------------
// Overloaded HAMSTERModule methods
//-----------------------------------------------------------------------------
void Autopilot::turnComponentON(HAMSTER_FUNCTIONAL_CODE component_code){
    logDetailedMessage("Autopilot turnComponentON(code) method.");
    // Do hardware stuff here.
}
void Autopilot::turnComponentOFF(HAMSTER_FUNCTIONAL_CODE component_code){
    logDetailedMessage("Autopilot turnComponentOFF(code) method.");
    // Do hardware stuff here
}

} /* namespace sample */
} /* namespace hamster */