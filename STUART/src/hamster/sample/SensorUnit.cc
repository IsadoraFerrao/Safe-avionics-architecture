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
 * \file      SensorUnit.cc
 * \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#include "SensorUnit.h"

namespace hamster{
namespace sample{
    
//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
SensorUnit::SensorUnit(char * config_file_name):HAMSTERCluster(config_file_name) {}
SensorUnit::~SensorUnit() {}

//-----------------------------------------------------------------------------
// Overloaded HAMSTERPlatform methods
//-----------------------------------------------------------------------------
void SensorUnit::customInitialization(void){
    logDetailedMessage("SensorUnit customInitialization() method");
}
void SensorUnit::customExecution(void){
    logDetailedMessage("SensorUnit customExecution() method.");
}
void SensorUnit::customTermination(void){
    logDetailedMessage("SensorUnit customTermination() method.");
}
void SensorUnit::processMessage(utils::Uuid& peer_id, char * message){
    logDetailedMessage("SensorUnit processMessage(message) method.");
}
//-----------------------------------------------------------------------------
// Overloaded HAMSTERModule methods
//-----------------------------------------------------------------------------
void SensorUnit::turnComponentON(HAMSTER_FUNCTIONAL_CODE component_code){
    logDetailedMessage("SensorUnit turnComponentON(code) method.");
    // Do hardware stuff here.
}
void SensorUnit::turnComponentOFF(HAMSTER_FUNCTIONAL_CODE component_code){
    logDetailedMessage("SensorUnit turnComponentOFF(code) method.");
    // Do hardware stuff here
}

} /* namespace sample */
} /* namespace hamster */