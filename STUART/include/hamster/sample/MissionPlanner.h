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
 * \anchor MissionPlanner
 * \class MissionPlanner MissionPlanner.h
 * \brief Class that represents a Ground Control Station (GCS) that sends the
 *        mission phases to its components.
 * \details The GCS is a \ref HAMSTERSuperEntity "HAMSTER Super Entity" that 
 * demonstrate the Mission Configuration of \ref NP "Navigation Phases" platform. 
 * The mission to be configured is detailed in the table below.
 * 
 * Number | Phase             | Active  Objects
 * :----: |:------------------|:---------------
 *    1   | Initialization    | All
 *    2   | Cruising          | Main only
 *    3   | Mission execution | All
 *    4   | Return to base    | Main only
 *    5   | Finalization      | All
 *    E   | Emergency         | Main + RGB Camera
 * 
 * \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 *
 */

#ifndef MISSIONPLANNER_H
#define MISSIONPLANNER_H

#include "HAMSTERSuperEntity.h"

namespace hamster{
namespace sample{
        
class MissionPlanner : public HAMSTERSuperEntity{
public:
    MissionPlanner(char * config_file_name);
    virtual ~MissionPlanner();
    void customInitialization(void);
    void customExecution(void);
    void customTermination(void);
    void processMessage(utils::Uuid& peer_id, char * message);
            
private:

};

} /* namespace sample */
} /* namespace hamster */

#endif /* MISSIONPLANNER_H */

