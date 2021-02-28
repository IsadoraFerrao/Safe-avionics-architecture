/*
 * Copyright (C) 2017     Critical Embedded System Laboratory (LSEC)
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
 * \anchor CentralSPHERE
 * \class hamster::sphere::CentralSPHERE CentralSPHERE.h
 * \brief SPHERE functionality implementation in \ref HAMSTEREntity "HAMSTER 
 * entities".
 * \details Central SPHERE implements the SPHERE functionality in HAMSTER Entities.
 * A Central SPHERE is composed by a \ref CentralCSU "Central CSU", a \ref 
 * CentralSMU "Central SMU" and a \ref CentralSEMU "Central SEMU".
 * 
 *  \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 *  \copyright GNU Lesser General Public License.
 */

#ifndef CENTRALSPHERE_H
#define CENTRALSPHERE_H

#include "SPHERE.h"


namespace hamster{
namespace sphere{
    
class CentralSPHERE : public SPHERE{
public:
//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
    CentralSPHERE(Unit * unit, HAMSTERUnitCommInfo * info);
    virtual ~CentralSPHERE();
    
//-----------------------------------------------------------------------------
// HAMSTERPlatform methods
//-----------------------------------------------------------------------------
//    virtual void platformInitialization();
    virtual void executionLoop(void);
    virtual void platformTermination(void);
    void parseMessage(hamster::comm::messaging::HAMSTERMessage * msg);
    
private:    
    std::ostream& printPlatform(std::ostream& stream) const{return stream;}
};

} /* namespace sphere */
} /* namespace hamster */

#endif /* CENTRALSPHERE_H */

