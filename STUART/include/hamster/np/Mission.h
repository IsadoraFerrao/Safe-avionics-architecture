/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mission.h
 * Author: Mariana
 *
 * Created on 31 de Março de 2018, 18:30
 * Serialization:
 * 1. Number of phases
 * 2. For each phase:
 * 
 */

#ifndef MISSION_H
#define MISSION_H

#include "HAMSTER.h"
#include "NavigationPhase.h"

namespace hamster{ 
namespace navigation_phases{

class Mission : public comm::messaging::MessageField{

public:
    Mission();
    Mission(uint8_t num_phases);
    virtual ~Mission();
    
    void setNumberOfPhases(uint8_t num_phases);
    HAMSTER_RETURN addPhase(NavigationPhase new_phase);
    
    uint8_t getNumberOfPhases() const;
    NavigationPhase * const getPhase(uint8_t number) const;
    int pushInPayload(char ** buffer);
    int pullFromPayload(char * buffer);
    
    Mission& operator=(Mission& other);
    
    
private:
    uint8_t number_of_phases = 0;
    NavigationPhase * mission_phases;

};

} /* namespace navigation_phases */
} /* namespace hamster */

#endif /* MISSION_H */

