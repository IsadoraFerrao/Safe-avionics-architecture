/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PhaseBehaviour.h
 * Author: Mariana
 *
 * Created on 1 de Abril de 2018, 10:02
 */

// ENVIADA QUANDO O MÓDULO NÃO FOI AUTORIZADO.

#ifndef PHASEBEHAVIOUR_H
#define PHASEBEHAVIOUR_H

#include "HAMSTER.h"
#include "HAMSTER_COMPONENT_STATE.h"
#include "MessageField.h"

namespace hamster{
    class HAMSTERUVComponent;
    namespace navigation_phases{

class PhaseBehaviour : public comm::messaging::MessageField{
public:
    PhaseBehaviour();
    PhaseBehaviour(PhaseBehaviour& other);
    PhaseBehaviour(uint8_t num);
    PhaseBehaviour(uint8_t num, HAMSTER_COMPONENT_STATE main_component_state, HAMSTER_COMPONENT_STATE mission_component_state);
    virtual ~PhaseBehaviour();
    
    HAMSTER_COMPONENT_STATE getMainComponentState() const;
    HAMSTER_COMPONENT_STATE getMissionComponentState() const;
    uint8_t getNumber() const;
    
    inline PhaseBehaviour& operator=(const PhaseBehaviour& other){
        this->phase_number = other.phase_number;
        this->required_component_state = other.required_component_state;
        this->missionspecific_component_state = other.missionspecific_component_state;
        return *this;
    }
    
    void setMissionComponentState(HAMSTER_COMPONENT_STATE component_state);
    void setNumber(uint8_t number) ;
    void setMainComponentState(HAMSTER_COMPONENT_STATE component_state);
    
    int pushInPayload(char ** buffer);
    int pullFromPayload(char * buffer);

protected:
    uint8_t phase_number;
    HAMSTER_COMPONENT_STATE required_component_state = HAMSTER_COMPONENT_STATE::COMPONENT_ON;
    HAMSTER_COMPONENT_STATE missionspecific_component_state = HAMSTER_COMPONENT_STATE::COMPONENT_OFF;
};

    } /* namespace navigation_phases */
} /* namespace hamster */

#endif /* PHASEBEHAVIOUR_H */

