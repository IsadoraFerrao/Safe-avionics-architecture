/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NPAgent.h
 * Author: Mariana
 *
 * Created on 30 de Março de 2018, 12:51
 */

#ifndef NPAGENT_H
#define NPAGENT_H

#include "NPUnit.h"
#include "PhaseBehaviour.h"

namespace hamster{
namespace navigation_phases{
    
    enum class NP_AGENT_STATE{
        INITIAL,
        AWAITING_MISSION,
        RECEIVING_MISSION,
        MISSION_START,
        MISSION_OPERATION,
        MISSION_TERMINATION,
        TERMINATION
    };
    
inline std::ostream& operator<<(std::ostream& stream, const NP_AGENT_STATE& state) {
    switch(state){
        case NP_AGENT_STATE::INITIAL:
            stream << "INITIAL";
            break;
        case NP_AGENT_STATE::AWAITING_MISSION:
            stream << "AWAITING_MISSION";
            break;
        case NP_AGENT_STATE::RECEIVING_MISSION:
            stream << "RECEIVING_MISSION";
            break;
        case NP_AGENT_STATE::MISSION_START:
            stream << "MISSION_START";
            break;
        case NP_AGENT_STATE::MISSION_OPERATION:
            stream << "MISSION_OPERATION";
            break;
        case NP_AGENT_STATE::MISSION_TERMINATION:
            stream << "MISSION_TERMINATION";
            break;
        case NP_AGENT_STATE::TERMINATION:
            stream << "TERMINATION";
            break;
        default:
            stream << "UNKNOWN";
            break;
    }
    return stream;
}
    
class NPAgent : public NPUnit{
public:
    NPAgent(Unit * unit,HAMSTERUnitCommInfo * info);
    virtual ~NPAgent();
//-----------------------------------------------------------------------------
// HAMSTERPlatform methods
//-----------------------------------------------------------------------------
    void executionLoop(void);
    virtual void platformTermination(void){};
    void parseMessage(hamster::comm::messaging::HAMSTERMessage * msg);
    PhaseBehaviour * const getCurrentPhaseBehaviour(void);
    
protected:
    NP_AGENT_STATE getCurrentState() const;
    void setCurrentState(NP_AGENT_STATE current_state);
    uint8_t getNumberPhases() const {
        return number_phases;
    }

    
private:
    uint8_t number_phases;
    PhaseBehaviour * mission_behaviour;
    PhaseBehaviour emergency_behaviour;
    NP_AGENT_STATE current_state = NP_AGENT_STATE::INITIAL;
    
    std::ostream& printPlatform(std::ostream& stream) const{return stream;}

};

} /* namespace navigation_phases */
} /* namespace hamster */
#endif /* NPAGENT_H */

