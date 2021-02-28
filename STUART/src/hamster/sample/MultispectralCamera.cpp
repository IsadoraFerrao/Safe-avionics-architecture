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
 * \file      MultispectralCamera.cpp
 * \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#include "MultispectralCamera.h"

namespace hamster{
namespace sample{
    
//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
MultispectralCamera::MultispectralCamera(char * config_file_name):HAMSTERModule(config_file_name) {}
MultispectralCamera::~MultispectralCamera() {}

//-----------------------------------------------------------------------------
// Overloaded HAMSTERPlatform methods
//-----------------------------------------------------------------------------
void MultispectralCamera::customInitialization(void){
    logDetailedMessage("MultispectralCamera customInitialization() method");
}
void MultispectralCamera::customExecution(void){
    logDetailedMessage("MultispectralCamera customExecution() method.");
}
void MultispectralCamera::customTermination(void){
    logDetailedMessage("MultispectralCamera customTermination() method.");
}
void MultispectralCamera::processMessage(utils::Uuid& peer_id, char * message){
    logDetailedMessage("MultispectralCamera processMessage(message) method.");
}
//-----------------------------------------------------------------------------
// Overloaded HAMSTERModule methods
//-----------------------------------------------------------------------------
void MultispectralCamera::turnComponentON(HAMSTER_FUNCTIONAL_CODE component_code){
    logDetailedMessage("MultispectralCamera turnComponentON(code) method.");
    // Do hardware stuff here.
}
void MultispectralCamera::turnComponentOFF(HAMSTER_FUNCTIONAL_CODE component_code){
    logDetailedMessage("MultispectralCamera turnComponentOFF(code) method.");
    // Do hardware stuff here
}

} /* namespace sample */
} /* namespace hamster */