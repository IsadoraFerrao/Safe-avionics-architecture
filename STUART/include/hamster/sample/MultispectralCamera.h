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
 * \anchor MultispectralCamera
 * \class hamster::sample::MultispectralCamera MultispectralCamera.h
 * \brief Sample class for representing an Multispectral Camera wihtin an 
 *        Unmanned Vehicle.
 * \details This class inherits from a HAMSTERModule, meaning it has only one
 * component. Methods turnComponentON and turnComponentOFF can be changed so 
 * that a real hardware action is taken.
 * 
 * \file      MultispectralCamera.h
 * \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#ifndef MULTISPECTRALCAMERA_H
#define MULTISPECTRALCAMERA_H

#include "HAMSTERModule.h"

namespace hamster{
namespace sample{

class MultispectralCamera : public HAMSTERModule{

public:

//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
    MultispectralCamera(char * config_file_name);
    virtual ~MultispectralCamera();

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

#endif /* MULTISPECTRALCAMERA_H */

