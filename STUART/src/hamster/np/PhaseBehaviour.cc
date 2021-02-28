/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PhaseBehaviour.cc
 * Author: Mariana
 * 
 * Created on 1 de Abril de 2018, 10:02
 */

#include "PhaseBehaviour.h"
#include "HAMSTERMessage.h"


namespace hamster{
    namespace navigation_phases{
    
PhaseBehaviour::PhaseBehaviour() {
}

PhaseBehaviour::PhaseBehaviour(PhaseBehaviour& other):
        phase_number(other.phase_number),
        required_component_state(other.required_component_state),
        missionspecific_component_state(other.missionspecific_component_state){
}
PhaseBehaviour::PhaseBehaviour(uint8_t num):phase_number(num){
    
}
PhaseBehaviour::PhaseBehaviour(uint8_t num, HAMSTER_COMPONENT_STATE main_component_state, 
        HAMSTER_COMPONENT_STATE mission_component_state):
        phase_number(num),
        required_component_state(main_component_state),
        missionspecific_component_state(mission_component_state){
    
}

PhaseBehaviour::~PhaseBehaviour() {
}

int PhaseBehaviour::pushInPayload(char ** buffer){
    int used_bytes = 0;
    // Serialize phase number
    used_bytes += comm::messaging::HAMSTERMessage::pushInt8IntoPayload(buffer,this->phase_number);
    char * ptr = (*buffer) + used_bytes;
    used_bytes += comm::messaging::HAMSTERMessage::pushInt8IntoPayload(&ptr,
            required_component_state == HAMSTER_COMPONENT_STATE::COMPONENT_ON? 1 : 0);
    ptr = (*buffer) + used_bytes;
    used_bytes += comm::messaging::HAMSTERMessage::pushInt8IntoPayload(&ptr,
            missionspecific_component_state == HAMSTER_COMPONENT_STATE::COMPONENT_ON? 1 : 0);
    return used_bytes;
}

int PhaseBehaviour::pullFromPayload(char * buffer){
    int used_bytes = 0;
    int ret_int = 0;
    uint8_t aux_variable;
    ret_int = comm::messaging::HAMSTERMessage::pullInt8FromPalyload(buffer,&(this->phase_number));
    used_bytes += ret_int;
    ret_int = comm::messaging::HAMSTERMessage::pullInt8FromPalyload(&(buffer[used_bytes]),&aux_variable);
    used_bytes += ret_int;
    this->required_component_state = aux_variable == 1? HAMSTER_COMPONENT_STATE::COMPONENT_ON : HAMSTER_COMPONENT_STATE::COMPONENT_OFF;
    ret_int = comm::messaging::HAMSTERMessage::pullInt8FromPalyload(&(buffer[used_bytes]),&aux_variable);
    used_bytes += ret_int;
    this->missionspecific_component_state = aux_variable == 1? HAMSTER_COMPONENT_STATE::COMPONENT_ON : HAMSTER_COMPONENT_STATE::COMPONENT_OFF;
    return used_bytes;
}

HAMSTER_COMPONENT_STATE PhaseBehaviour::getMainComponentState() const{
    return this->required_component_state;
}
HAMSTER_COMPONENT_STATE PhaseBehaviour::getMissionComponentState() const{
    return this->missionspecific_component_state;
}
uint8_t PhaseBehaviour::getNumber() const{
    return this->phase_number;
}

void PhaseBehaviour::setMissionComponentState(HAMSTER_COMPONENT_STATE component_state){
    this->missionspecific_component_state = component_state;
}
void PhaseBehaviour::setNumber(uint8_t number){
    this->phase_number = number;
}
void PhaseBehaviour::setMainComponentState(HAMSTER_COMPONENT_STATE component_state){
    this->required_component_state = component_state;
}
    
} /* namespace navigation_phases */
} /* namespace hamster */