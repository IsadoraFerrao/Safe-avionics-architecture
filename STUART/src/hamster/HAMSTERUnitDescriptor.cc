/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HAMSTERUnitDescriptor.cc
 * Author: Mariana
 * 
 * Created on 27 de Março de 2018, 13:34
 */

#include "HAMSTERUnitDescriptor.h"

namespace hamster{

HAMSTERUnitDescriptor::HAMSTERUnitDescriptor(utils::Uuid id, HAMSTER_UNIT_TYPE type):unit_ID(id),unit_type(type) {
}

HAMSTERUnitDescriptor::~HAMSTERUnitDescriptor() {
}

utils::Uuid HAMSTERUnitDescriptor::getUnitID() const {
    return unit_ID;
}

HAMSTER_UNIT_TYPE HAMSTERUnitDescriptor::getUnitType() const {
    return unit_type;
}

comm::HAMSTERPeer* HAMSTERUnitDescriptor::getUnitCommunicationInfo() const {
    return unit_comm_info;
}

void HAMSTERUnitDescriptor::setUnitID(utils::Uuid iD) {
    this->unit_ID = unit_ID;
}

void HAMSTERUnitDescriptor::setUnitType(HAMSTER_UNIT_TYPE type) {
    this->unit_type = unit_type;
}

void HAMSTERUnitDescriptor::setUnitCommunicationInfo(comm::HAMSTERPeer * comm_info){
    this->unit_comm_info = comm_info;
}

} /* namespace hamster */

