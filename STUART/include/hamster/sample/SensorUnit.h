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

/* 
 * \anchor SensorUnit
 * \class hamster::sample::SensorUnit SensorUnit.h
 * \brief Sample class for representing an Sensor Unit wihtin an Unmanned Vehicle.
 * \details This class inherits from a HAMSTERModule, meaning it has only one
 * component. Methods turnComponentON and turnComponentOFF can be changed so that
 * a real hardware action is taken.
 * 
 * \file      SensorUnit.h
 * \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */


#ifndef SENSORUNIT_H
#define SENSORUNIT_H

#include "HAMSTERCluster.h"


namespace hamster{
namespace sample{
    
class SensorUnit : public HAMSTERCluster{

public:

//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
    SensorUnit(char * config_file_name);
    virtual ~SensorUnit();

//-----------------------------------------------------------------------------
// Overloaded HAMSTERPlatform methods
//-----------------------------------------------------------------------------
    void customInitialization(void);
    void customExecution(void);
    void customTermination(void);
    void processMessage(utils::Uuid& peer_id, char * message);
    
//-----------------------------------------------------------------------------
// Overloaded HAMSTERModule methods
//-----------------------------------------------------------------------------  
    void turnComponentON(HAMSTER_FUNCTIONAL_CODE component_code);
    void turnComponentOFF(HAMSTER_FUNCTIONAL_CODE component_code);

};

} /* namespace sample */
} /* namespace hamster */


#endif /* SENSORUNIT_H */

