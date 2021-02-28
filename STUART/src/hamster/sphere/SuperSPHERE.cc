/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SuperSPHERE.cc
 * Author: Mariana
 * 
 * Created on 6 de Dezembro de 2017, 11:36
 */

#include "SuperSPHERE.h"
#include "SuperCSU.h"
#include "CentralSEMU.h"
#include "CentralSMU.h"
#include "CentralNCI.h"


namespace hamster{
namespace sphere{

//-----------------------------------------------------------------------------
// Constructor / Destructor
//----------------------------------------------------------------------------- 
SuperSPHERE::SuperSPHERE(Unit * unit,HAMSTERUnitCommInfo * info) : SPHERE(unit,info) {
    try{
        // \todo mudar para SuperCSU
        this->SetCSUModule(new csu::SuperCSU(unit,info));
        this->SetSEMUModule(new semu::CentralSEMU(unit,info));
        this->SetSMUUModule(new smu::CentralSMU(unit,info));
        this->SetNCIModule(new NCI::CentralNCI(unit,info));
        logDebugMessage("New SuperSPHERE. Entity ID = ", unit->getID()); 
    }
    catch (const std::exception& e){
        logErrorMessage("Cloud not create SPHERE platforms. ",e.what());
    }
}
SuperSPHERE::~SuperSPHERE() {
}

//-----------------------------------------------------------------------------
// HAMSTERPlatform methods
//-----------------------------------------------------------------------------
void SuperSPHERE::executionLoop(void){};
void SuperSPHERE::platformTermination(void){};
void SuperSPHERE::parseMessage(hamster::comm::messaging::HAMSTERMessage * msg){};

} /* namespace sphere */
} /* namespace hamster */