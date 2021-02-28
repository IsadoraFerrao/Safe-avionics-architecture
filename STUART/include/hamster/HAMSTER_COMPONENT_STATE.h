/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HAMSTER_COMPONENT_STATE.h
 * Author: Mariana
 *
 * Created on 1 de Abril de 2018, 10:15
 */

#ifndef HAMSTER_COMPONENT_STATE_H
#define HAMSTER_COMPONENT_STATE_H

namespace hamster{

/*! 
 *  \anchor HAMSTER_COMPONENT_STATE
 *  \enum HAMSTER_COMPONENT_STATE
 *  \brief Possible states of the component.
 */
enum class HAMSTER_COMPONENT_STATE{
    COMPONENT_ON,
    COMPONENT_OFF
};

inline HAMSTER_COMPONENT_STATE integer2ComponentState(int code){
    return (code == 1? HAMSTER_COMPONENT_STATE::COMPONENT_ON : HAMSTER_COMPONENT_STATE::COMPONENT_OFF);
}

} /* namespace hamster */

#endif /* HAMSTER_COMPONENT_STATE_H */

