/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HAMSTERObjectDescriptor.cc
 * Author: Mariana
 * 
 * Created on 27 de Março de 2018, 14:15
 */

#include "HAMSTERObjectDescriptor.h"
#include "HAMSTERUnitDescriptor.h"

namespace hamster{ 
    
HAMSTERObjectDescriptor::HAMSTERObjectDescriptor(utils::Uuid id, HAMSTER_UNIT_TYPE type):HAMSTERUnitDescriptor(id,type) {
}

HAMSTERObjectDescriptor::~HAMSTERObjectDescriptor() {
}

HAMSTERUVComponent * HAMSTERObjectDescriptor::getComponent(uint8_t number) const {
    for (int i = 0; i < num_components; i++) {
        if(components[i].getNumber() == number){
            return &(components[i]);
        }
    }
    return NULL;
}

HAMSTERUVComponent * HAMSTERObjectDescriptor::getComponents(){
    return this->components;
}

uint8_t HAMSTERObjectDescriptor::getNumComponents() const {
    return num_components;
}

void HAMSTERObjectDescriptor::setClassification(HAMSTERUVComponent::COMPONENT_CLASSIFICATION obj_class){
    this->object_classification = obj_class;
}

bool HAMSTERObjectDescriptor::isRequired() const{
    return (this->object_classification == HAMSTERUVComponent::COMPONENT_CLASSIFICATION::REQUIRED_FOR_OPERATION);
}

void HAMSTERObjectDescriptor::setNumComponents(uint8_t num_components) {
    this->num_components = num_components;
    if(components == NULL){
        components = new HAMSTERUVComponent[num_components];
    }
}

} /* namespace hamster */

