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
 * \anchor CentralCSU
 * \class hamster::sphere::csu::CentralCSU CentralCSU.h
 * \brief CSU implementation in \ref HAMSTEREntity "HAMSTER entities".
 * \details Central CSU implements the SPHERE functionality in HAMSTER Entities,
 * and has to perform different tasks depending on the \ref scenarios 
 * "operation scenario".
 * 
 * First of all, central CSU must authenticate all UAV modules before communicating
 * with the outside world. Once all \ref HAMSTERObject "HAMSTER Objects" are 
 * authenticated, central CSU is ready to open its communication channel with
 * the outside world. Central CSU will take different actions depending on the 
 * operation scenario. 
 * 
 * If the system is run in a \e centralized architecture, Central CSU
 * will have to authenticate itself with the system Super Entity. In a \e known
 * \e formation scenario, Central CSU will have the SuperEntity connection info
 * in advance. In an \e unknown \e formation, it must identify a SuperEntity and
 * perform a mutual authentication with it.
 * 
 * If the sistem is run in a \e decentralized architecture, Central CSU will not
 * concern itself with a Super Entity. In a \e known \e formation scenario, 
 * Central CSU will have in advance a list of Entity peers it must perform an
 * mutual authentication. In an \e unknown \e formation scenario, Central CSU 
 * must perform mutual identification and authentication with unkown peers.
 * 
 *  \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 *  \copyright GNU Lesser General Public License.
 */

#ifndef CENTRALCSU_H
#define CENTRALCSU_H

#include "FlightData.h"
#include "CSU.h"
#include "UAVJINT.h"
#include "Station.h"
#include "MQTTClient.h"
#include "UAV.h"
#include "CSVReader.h"
#include "UAVJINT.h"

namespace hamster{
namespace sphere{
namespace csu{
    

class CentralCSU: public CSU{
    
public:
    
//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
    CentralCSU(Unit * unit, HAMSTERUnitCommInfo * info);
    virtual ~CentralCSU();
    
//-----------------------------------------------------------------------------
// HAMSTERNode method
//-----------------------------------------------------------------------------
    virtual void executionLoop(void);
    virtual void platformTermination(void){};
    // objeto 
    virtual void parseMessage(hamster::comm::messaging::HAMSTERMessage* msg);
    HAMSTER_RETURN requestConnectionToCentralUnit(utils::Uuid& peer_id);
    
protected:
    bool areAllCriticalModulesAuthenticated() const {
        return all_critical_modules_authenticated;
    }

    /*!
     * \fn virtual std::ostream& hamster::HAMSTERNode::printNode(std::ostream& stream) const
     * \brief Outputs the information of the HAMSTERNode to the output stream.
     * \details Pure virtual method which inserts the details of a HAMSTER Node
     * in an output stream to be used in operator << overload.
     * \attention All concrete child classes must provide an implementation for
     * this method.
     */
    std::ostream& printPlatform(std::ostream& stream) const{return stream;}
    
    // \todo Set to false
    bool all_critical_modules_authenticated = true;
    
private:
   // int altitude_m = 0;
    int camera = 0;
};
    




} /* namespace csu */
} /* namespace sphere */
} /* namespace hamster */
#endif /* CENTRALCSU_H */

