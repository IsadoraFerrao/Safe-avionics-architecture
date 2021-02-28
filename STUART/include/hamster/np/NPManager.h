/*
 * Copyright (C) 2018     Critical Embedded System Laboratory (LSEC)
 * 
 * This program is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * See the GNU Lesser General Public License for more details.
 * <http://www.gnu.org/licenses/>
 */

/*! 
 * \anchor NPManager
 * \class hamster::NPManager NPManager.h
 * \brief 
 * \details 
 * 
 * \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 *
 */

#ifndef NPMANAGER_H
#define NPMANAGER_H

#include "NPUnit.h"
#include "Mission.h"
#include "HAMSTERUnitDescriptor.h"

namespace hamster{
namespace navigation_phases{
    
    enum class NP_MANAGER_STATE{
        INITIAL,
        AWAITING_MODULES,
        AWAITING_MISSION,
        RECEIVING_MISSION,
        MISSION_CONFIGURATION,
        MISSION_DISTRIBUTION,
        AWAITING_DISTRIBUTION_END,
        MISSION_START,
        MISSION_OPERATION,
        MISSION_TERMINATION,
        TERMINATION
    };
    
inline std::ostream& operator<<(std::ostream& stream, const NP_MANAGER_STATE& state) {
    switch(state){
        case NP_MANAGER_STATE::INITIAL:
            stream << "INITIAL";
            break;
        case NP_MANAGER_STATE::AWAITING_MODULES:
            stream << "AWAITING_MODULES";
            break;
        case NP_MANAGER_STATE::AWAITING_MISSION:
            stream << "AWAITING_MISSION";
            break;
        case NP_MANAGER_STATE::RECEIVING_MISSION:
            stream << "RECEIVING_MISSION";
            break;
        case NP_MANAGER_STATE::MISSION_CONFIGURATION:
            stream << "MISSION_CONFIGURATION";
            break;
        case NP_MANAGER_STATE::MISSION_DISTRIBUTION:
            stream << "MISSION_DISTRIBUTION";
            break;
        case NP_MANAGER_STATE::AWAITING_DISTRIBUTION_END:
            stream << "AWAITING_DISTRIBUTION_END";
            break;
        case NP_MANAGER_STATE::MISSION_START:
            stream << "MISSION_START";
            break;
        case NP_MANAGER_STATE::MISSION_OPERATION:
            stream << "MISSION_OPERATION";
            break;
        case NP_MANAGER_STATE::MISSION_TERMINATION:
            stream << "MISSION_TERMINATION";
            break;
        case NP_MANAGER_STATE::TERMINATION:
            stream << "TERMINATION";
            break;
        default:
            stream << "UNKNOWN";
            break;
    }
    return stream;
}

class NPManager : public NPUnit {

public:

//-----------------------------------------------------------------------------
// Constructor / Destructor
//----------------------------------------------------------------------------- 
    NPManager(Unit * unit,HAMSTERUnitCommInfo * info);
    virtual ~NPManager();

//-----------------------------------------------------------------------------
// HAMSTERPlatform methods
//-----------------------------------------------------------------------------
    void executionLoop(void);
    void platformTermination(void);
    void parseMessage(hamster::comm::messaging::HAMSTERMessage * msg);
    
    void setMission(Mission my_mission);
    
protected:
//-----------------------------------------------------------------------------
// Get/Set methods
//-----------------------------------------------------------------------------
    NP_MANAGER_STATE getCurrentState() const;
    Mission * const getMission();
  
    void setCurrentState(NP_MANAGER_STATE state);

private:
    
    /* Send:
     * 1. Number of phases,
     * 2. For each phase:
     * 2.1 Phase number
     * 2.2 Main components state,
     * 2.3 Required component state,
     * 2.4 Emergency state
     */
    HAMSTER_RETURN sendMissionToAgent(HAMSTERUnitDescriptor * agent);
    HAMSTER_RETURN sendPhaseNumberToAgent(HAMSTERUnitDescriptor * agent);
    HAMSTER_RETURN sendPhaseBehaviourToAgent(HAMSTERUnitDescriptor * agent);
    void nextPhase();
    
    Mission entity_mission;
    NP_MANAGER_STATE current_state = NP_MANAGER_STATE::INITIAL;
    
    
    std::ostream& printPlatform(std::ostream& stream) const{return stream;}
   

};

    } /* namespace navigation_phases */
} /* namespace hamster */
#endif /* NPMANAGER_H */

