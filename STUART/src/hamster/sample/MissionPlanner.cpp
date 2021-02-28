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
 * \file   MissionPlanner.cpp
 * \author: Mariana Rodrigues   rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#include "MissionPlanner.h"

namespace hamster{
namespace sample{

MissionPlanner::MissionPlanner(char * config_file_name):HAMSTERSuperEntity(config_file_name) {
}

MissionPlanner::~MissionPlanner() {
}

void MissionPlanner::customInitialization(void){

}

void MissionPlanner::customExecution(void){

}

void MissionPlanner::customTermination(void){
    
}
    
void MissionPlanner::parseMessage(utils::Uuid& peer_id, char * message){
    
}
    
} /* namespace sample */
} /* namespace hamster */