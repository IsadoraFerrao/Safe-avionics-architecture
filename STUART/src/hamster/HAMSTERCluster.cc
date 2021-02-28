/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HAMSTERCluster.cc
 * Author: Mariana
 * 
 * Created on 26 de Março de 2018, 19:18
 */

#include "HAMSTERCluster.h"
#include "NCICluster.h"

namespace hamster{

HAMSTERCluster::HAMSTERCluster(char * config_file_name):HAMSTERObject(config_file_name) {
    //this->setNCIPlatform(new nci::NCICluster(this,this->getCommunicationInfo()));
}

HAMSTERCluster::~HAMSTERCluster() {
}

} /* namespace hamster */