/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   INETSocketInterface.cpp
 * Author: Mariana
 * 
 * Created on 25 de Dezembro de 2017, 11:36
 */

#include "INETSocketInterface.h"
#include "INETSocketAcceptor.h"
#include "INETSocketConnector.h"

namespace hamster{
namespace comm{
namespace interface{
namespace inet_socket{

INETSocketInterface::INETSocketInterface(uint8_t number,Unit * unit, HAMSTERUnitCommInfo * info,
        COMM_INTERFACE_TYPE type,INETSocketAddressInfo * acc_info,
        int max_acc_connections)
:CommInterface(number,unit,info,type,COMM_INTERFACE_TECH::SOCKET,(AddressInfo *) acc_info) {
    this->setAcceptor(new INETSocketAcceptor(this,acc_info,max_acc_connections));
    this->setConnector(new INETSocketConnector(this));
}

INETSocketInterface::~INETSocketInterface() {
}

void INETSocketInterface::platformTermination(void){
    this->getAcceptor()->getThread()->join();
}
} /* namespace socket */
} /* namespace interface */
} /* namespace comm */
} /* namespace hamster */