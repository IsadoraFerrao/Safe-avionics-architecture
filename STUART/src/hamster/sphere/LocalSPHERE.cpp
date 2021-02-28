/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LocalSPHERE.cpp
 * Author: Mariana
 * 
 * Created on 30 de Março de 2018, 10:53
 */

#include "LocalSPHERE.h"
#include "LocalCSU.h"
#include "LocalSEMU.h"
#include "LocalSMU.h"
#include "LocalNCI.h"

namespace hamster{
namespace sphere{
    
LocalSPHERE::LocalSPHERE(Unit * unit, HAMSTERUnitCommInfo * info):SPHERE(unit,info) {
    logDetailedMessage("LocalSPHERE constructor.");
    this->SetCSUModule(new csu::LocalCSU(unit,info));
    this->SetSEMUModule(new semu::LocalSEMU(unit,info));
    this->SetSMUUModule(new smu::LocalSMU(unit,info));
    this->SetNCIModule(new NCI::LocalNCI(unit,info));
    logDebugMessage("New LocalSPHERE. Entity ID = ", unit->getID());
}


LocalSPHERE::~LocalSPHERE() {
}

//-----------------------------------------------------------------------------
// HAMSTERPlatform methods
//-----------------------------------------------------------------------------
void LocalSPHERE::executionLoop(void){};
void LocalSPHERE::platformTermination(void){};
void LocalSPHERE::parseMessage(hamster::comm::messaging::HAMSTERMessage * msg){};

} /* namespace sphere */
} /* namespace hamster */