/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HAMSTERComponent.cc
 * Author: Mariana
 * 
 * Created on 26 de Março de 2018, 13:27
 */

#include "HAMSTERUVComponent.h"

namespace hamster{

HAMSTERUVComponent::HAMSTERUVComponent(){

}
    
HAMSTERUVComponent::HAMSTERUVComponent(uint8_t number, HAMSTER_FUNCTIONAL_CODE code, COMPONENT_CLASSIFICATION classification):
                    component_number(number),component_code(code),component_classification(classification),component_state(HAMSTER_COMPONENT_STATE::COMPONENT_ON){
}

HAMSTERUVComponent::~HAMSTERUVComponent() {
}

HAMSTERUVComponent::COMPONENT_CLASSIFICATION HAMSTERUVComponent::getClassification() const {
    return component_classification;
}

void HAMSTERUVComponent::setClassification(COMPONENT_CLASSIFICATION classification) {
    this->component_classification = classification;
}

HAMSTER_FUNCTIONAL_CODE HAMSTERUVComponent::getCode() const {
    return component_code;
}

void HAMSTERUVComponent::setCode(HAMSTER_FUNCTIONAL_CODE code) {
    this->component_code = code;
}

uint8_t HAMSTERUVComponent::getNumber() const {
    return component_number;
}

void HAMSTERUVComponent::setNumber(uint8_t component_number) {
    this->component_number = component_number;
}

void HAMSTERUVComponent::setState(HAMSTER_COMPONENT_STATE state) {
    this->component_state = state;
}

HAMSTER_COMPONENT_STATE HAMSTERUVComponent::getComponent_state() const {
    return component_state;
}


void HAMSTERUVComponent::readFromXMLElement(TiXmlElement * xml_element){
    int number;
    // Read data from element
    xml_element->Attribute("FunctionalCode",&number);
    component_code = integer2FunctionalCode(number);
    xml_element->Attribute("Classification",&number);
    component_classification = integer2ComponentClassification(number);
    xml_element->Attribute("Number",&number);
    component_number = number & 0xFF;
    component_state = HAMSTER_COMPONENT_STATE::COMPONENT_ON;
    if(xml_element->Attribute("EmergencyState",&number) != 0){
        emergency_state = integer2ComponentState(number);
    }
}

} /* namespace hamster */
