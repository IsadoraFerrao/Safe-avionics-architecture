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
 * \file   CentralSPHERE.cc
 * \author: Mariana Rodrigues   rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#include "CentralSPHERE.h"
#include "CentralCSU.h"
#include "CentralSEMU.h"
#include "CentralSMU.h"
#include "CentralNCI.h"



namespace hamster{
namespace sphere{
    
//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
CentralSPHERE::CentralSPHERE(Unit * unit, HAMSTERUnitCommInfo * info):SPHERE(unit,info) {
    this->SetCSUModule(new csu::CentralCSU(unit,info));
    this->SetSEMUModule(new semu::CentralSEMU(unit,info));
    this->SetSMUUModule(new smu::CentralSMU(unit,info));
    this->SetNCIModule(new NCI::CentralNCI(unit,info));
    logDebugMessage("New CentralSPHERE. Entity ID = ", unit->getID());
}
CentralSPHERE::~CentralSPHERE() {
}
//-----------------------------------------------------------------------------
// HAMSTERPlatform methods
//-----------------------------------------------------------------------------
void CentralSPHERE::executionLoop(void){};
void CentralSPHERE::platformTermination(void){};
void CentralSPHERE::parseMessage(hamster::comm::messaging::HAMSTERMessage * msg){};


} /* namespace sphere */
} /* namespace hamster */