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
 * \file      RGBCamera.cpp
 * \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#include "RGBCamera.h"

namespace hamster{
namespace sample{

//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
RGBCamera::RGBCamera(char * config_file_name) : HAMSTERModule(config_file_name){}
RGBCamera::~RGBCamera() {}

//-----------------------------------------------------------------------------
// Overloaded HAMSTERPlatform methods
//-----------------------------------------------------------------------------
void RGBCamera::customInitialization(void){
    logDetailedMessage("RGBCamera customInitialization() method");
}
void RGBCamera::customExecution(void){
    logDetailedMessage("RGBCamera customExecution() method.");
}
void RGBCamera::customTermination(void){
    logDetailedMessage("RGBCamera customTermination() method.");
}
void RGBCamera::processMessage(utils::Uuid& peer_id, char * message){
    logDetailedMessage("RGBCamera processMessage(message) method.");
}
//-----------------------------------------------------------------------------
// Overloaded HAMSTERModule methods
//-----------------------------------------------------------------------------
void RGBCamera::turnComponentON(HAMSTER_FUNCTIONAL_CODE component_code){
    logDetailedMessage("RGBCamera turnComponentON(code) method.");
    // Do hardware stuff here.
}
void RGBCamera::turnComponentOFF(HAMSTER_FUNCTIONAL_CODE component_code){
    logDetailedMessage("RGBCamera turnComponentOFF(code) method.");
    // Do hardware stuff here
}

} /* namespace sample */
} /* namespace hamster */

