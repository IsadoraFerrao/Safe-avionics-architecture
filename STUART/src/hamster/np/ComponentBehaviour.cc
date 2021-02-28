/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ComponentBehaviour.cc
 * Author: Mariana
 * 
 * Created on 4 de Abril de 2018, 08:55
 */

#include "ComponentBehaviour.h"

namespace hamster{
    namespace navigation_phases{

ComponentBehaviour::ComponentBehaviour() {
}

ComponentBehaviour::~ComponentBehaviour() {
}

HAMSTER_COMPONENT_STATE ComponentBehaviour::getState() const {
    return component_state;
}

void ComponentBehaviour::setState(HAMSTER_COMPONENT_STATE state) {
    this->component_state = state;
}

int ComponentBehaviour::pushInPayload(char ** buffer){
    return 0;
}

int ComponentBehaviour::pullFromPayload(char * buffer){
    return 0;
}

} /* namespace navigation_phases */
} /* namespace hamster */