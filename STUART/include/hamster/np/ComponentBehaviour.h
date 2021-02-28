/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ComponentBehaviour.h
 * Author: Mariana
 *
 * Created on 4 de Abril de 2018, 08:55
 */

#ifndef COMPONENTBEHAVIOUR_H
#define COMPONENTBEHAVIOUR_H

#include "HAMSTER.h"
#include "MessageField.h"
#include "HAMSTER_COMPONENT_STATE.h"

namespace hamster{
    namespace navigation_phases{

class ComponentBehaviour : public comm::messaging::MessageField{
public:
    ComponentBehaviour();
    virtual ~ComponentBehaviour();
    
    HAMSTER_COMPONENT_STATE getState() const;
    uint8_t getComponentNumber() const;
    void setState(HAMSTER_COMPONENT_STATE state);
    
    
    int pushInPayload(char ** buffer);
    int pullFromPayload(char * buffer);
    
private:
    uint8_t component_number;
    HAMSTER_COMPONENT_STATE component_state;
};

    } /* namespace navigation_phases */
} /* namespace hamster */

#endif /* COMPONENTBEHAVIOUR_H */

