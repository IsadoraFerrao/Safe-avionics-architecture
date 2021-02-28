/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NavigationPhase.cc
 * Author: Mariana
 * 
 * Created on 31 de Março de 2018, 18:42
 */

#include "NavigationPhase.h"
#include <cstring>

namespace hamster{
    namespace navigation_phases{
        
NavigationPhase::NavigationPhase(){
}
    
NavigationPhase::NavigationPhase(uint8_t num){
    this->component_behaviour.setNumber(num);
}

NavigationPhase::NavigationPhase(NavigationPhase &other):
        component_behaviour(other.component_behaviour),
        trigger_to_next_phase(other.trigger_to_next_phase){
//    size_t desc_size = strlen(other.description);
//    this->description = new char[desc_size];
//    strncpy(this->description,other.description,desc_size);
//    this->description[desc_size] = '\0';
}

NavigationPhase::NavigationPhase(uint8_t num, HAMSTER_COMPONENT_STATE main_component_state, 
        HAMSTER_COMPONENT_STATE mission_component_state){
    this->component_behaviour.setNumber(num);
    this->component_behaviour.setMainComponentState(main_component_state);
    this->component_behaviour.setMissionComponentState(mission_component_state);
}

NavigationPhase::~NavigationPhase() {
//    if(this->description != NULL){
//        delete this->description;
//    }
    logVerboseMessage("Navigation Phase destructor.");
}

bool (*NavigationPhase::getTriggerToNextPhase(void))(void) const{
    return this->trigger_to_next_phase;
}

bool NavigationPhase::verifyTrigger(void){
    return this->trigger_to_next_phase();
}

PhaseBehaviour * NavigationPhase::getComponentBehaviour() {
    return &component_behaviour;
}
//
void NavigationPhase::setDescription(char* desc) {
    if(this->description != NULL){
        delete description;
    }
    size_t desc_size = strlen(desc);
    this->description = new char[desc_size];
    strncpy(this->description,desc,desc_size);
    this->description[desc_size] = '\0';
}

void NavigationPhase::setTriggerToNextPhase(bool(*trigger_func)(void)) {
    this->trigger_to_next_phase = trigger_func;
}

void NavigationPhase::setComponentBehaviour(PhaseBehaviour component_behaviour) {
    this->component_behaviour = component_behaviour;
}

int NavigationPhase::pushInPayload(char ** buffer){
    return this->component_behaviour.pushInPayload((buffer));
}

int NavigationPhase::pullFromPayload(char * buffer){
    return this->component_behaviour.pullFromPayload(buffer);    
}


} /* namespace navigation_phases */
} /* namespace hamster */