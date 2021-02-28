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

#include "SPHERE.h"
#include "CSU.h"
#include "SEMU.h"
#include "SMU.h"
#include "NCI.h"

namespace hamster{
    
namespace sphere{

//-----------------------------------------------------------------------------
// Constructor / Destructor
//----------------------------------------------------------------------------- 
SPHERE::SPHERE(Unit * unit,HAMSTERUnitCommInfo * info):HAMSTERPlatform(unit,info){
};
SPHERE::~SPHERE(){
};
    
//-----------------------------------------------------------------------------
// HAMSTER Platform Methods
//----------------------------------------------------------------------------- 

void SPHERE::platformInitialization(void){
    this->csu_module->platformInitialization();
    this->smu_module->platformInitialization();
    this->NCI_module->platformInitialization();
    this->semu_module->platformInitialization();
    std::cout << "EXECUTANDO SPHERE" << std::endl;
}
void SPHERE::platformLoop(void){
    this->csu_module->platformLoop();
    this->NCI_module->platformLoop();
//    this->semu_module->platformLoop();
//    this->smu_module->platformLoop();
}
 bool SPHERE::setupFinished(){
     return this->csu_module->setupFinished();
     return this->NCI_module->setupFinished();
 }

//-----------------------------------------------------------------------------
// SET methods for modules
//-----------------------------------------------------------------------------
void SPHERE::SetCSUModule(csu::CSU* csu_module) {
    this->csu_module = csu_module;
}
void SPHERE::SetSEMUModule(semu::SEMU* semu_module) {
    this->semu_module = semu_module;
}
void SPHERE::SetSMUUModule(smu::SMU* smu_module) {
    this->smu_module = smu_module;
}

void SPHERE::SetNCIModule(NCI::NCI* NCI_module) {
    this->NCI_module = NCI_module;
}

void SPHERE::receberDados(sample::FlightData dados){
    this->getCSUModule()->receberDados(dados);
}

void SPHERE::receberDadosSaude(sample::FlightData dadosSaude){
    this->getSMUModule()->receberDadosSaude(dadosSaude);
} 

    

void SPHERE::get_Security(sample::FlightData *data_history, int flightData_ID){
    this->getCSUModule()->get_Security(data_history, flightData_ID);
}

    

} /* namespace sphere */
} /* namespace hamster */