/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NavigationPhase.h
 * Author: Mariana
 *
 * Created on 31 de Março de 2018, 18:42
 */

#ifndef NAVIGATIONPHASE_H
#define NAVIGATIONPHASE_H

#include "HAMSTER.h"
#include "MessageField.h"
#include "HAMSTER_COMPONENT_STATE.h"
#include "PhaseBehaviour.h"

namespace hamster{
namespace navigation_phases{

class NavigationPhase : public comm::messaging::MessageField{
public:
    NavigationPhase();
    NavigationPhase(uint8_t num);
    NavigationPhase(NavigationPhase &other);
    NavigationPhase(uint8_t num, HAMSTER_COMPONENT_STATE main_component_state, HAMSTER_COMPONENT_STATE mission_component_state);
    virtual ~NavigationPhase();
    
    inline NavigationPhase& operator=(const NavigationPhase& other){
        this->component_behaviour = other.component_behaviour;
        this->trigger_to_next_phase = other.trigger_to_next_phase;
//        if(this->description != NULL){
//            delete this->description;
//            this->description = NULL;
//        }
//        size_t desc_size = strlen(other.description);
//        this->description = new char[desc_size];
//        strncpy(this->description,other.description,desc_size);
//        this->description[desc_size] = '\0';
        return *this;
    }
    
    char * getDescription() const;
    bool (*getTriggerToNextPhase(void))(void) const;
    bool verifyTrigger(void);
    PhaseBehaviour * getComponentBehaviour();

    void setDescription(char* desc);
    void setTriggerToNextPhase(bool(*trigger_func)(void));
    void setComponentBehaviour(PhaseBehaviour component_behaviour);
    
    int pushInPayload(char ** buffer);
    int pullFromPayload(char * buffer);
    
private:
    PhaseBehaviour component_behaviour;
    char * description = NULL;
    bool (* trigger_to_next_phase)(void) = NULL;

};

} /* namespace navigation_phases */
} /* namespace hamster */

#endif /* NAVIGATIONPHASE_H */

