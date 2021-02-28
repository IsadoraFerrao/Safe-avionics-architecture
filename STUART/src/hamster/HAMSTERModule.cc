/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HAMSTERModule.cc
 * Author: Mariana
 * 
 * Created on 8 de Março de 2018, 15:35
 */

#include "HAMSTERModule.h"
#include "NCIModule.h"

namespace hamster{

HAMSTERModule::HAMSTERModule(char * config_file_name):HAMSTERObject(config_file_name) {
    //this->setNCIPlatform(new hamster::nci::NCIModule(this,this->getCommunicationInfo()));
}

HAMSTERModule::~HAMSTERModule() {
}

} /* namespace hamster */