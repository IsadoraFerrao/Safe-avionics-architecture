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
 * \anchor HAMSTERObject
 * \class hamster::HAMSTERObject HAMSTERObject.h
 * \brief Class that represents the internal sensors/actuators of a \ref 
 * HAMSTEREntity "HAMSTER Entity".
 * \details HAMSTER Objects are further specialized into \ref HAMSTERModule 
 * "Modules" and \ref HAMSTERCluster "Clusters". A HAMSTER Module is a unit 
 * which handles a single sensor/actuator of the unmanned vehicle, like the 
 * GPS sensor; a HAMSTER Cluster is a unit which handles a set of 
 * sensor/actuators with one common communication interface.
 * 
 * \if DESIGN_MODEL
 * This class provides an abstraction to HAMSTER modules and clusters so they
 * can be addressed equaly by its entity.
 * \endif
 * 
 * \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 *
 */

#ifndef HAMSTEROBJECT_H
#define HAMSTEROBJECT_H

#include "Unit.h"
#include "HAMSTER_FUNCTIONAL_CODE.h"
#include "HAMSTERUVComponent.h"
#include "np/PhaseBehaviour.h"

namespace hamster {
    
   
class HAMSTEREntity;

class HAMSTERObject : public Unit {
public:
    HAMSTERObject(char * config_file_name);
    virtual ~HAMSTERObject();
    
//------------------------------------------------------------------------------
// HAMSTER Node methods
//------------------------------------------------------------------------------
    void initialize(void);
    void execute(void);
    void nodeTermination(void);
    void applyPhaseBehaviour(navigation_phases::PhaseBehaviour phase);

//-----------------------------------------------------------------------------
// User methods to be overloaded by application
//-----------------------------------------------------------------------------
    virtual void customInitialization(void) = 0;
    virtual void customExecution(void) = 0;
    virtual void customTermination(void) = 0;
    virtual void parseMessage(comm::messaging::HAMSTERMessage * msg){};
    virtual void processMessage(utils::Uuid& peer_id, char * message) = 0;
    virtual void turnComponentON(HAMSTER_FUNCTIONAL_CODE component_code) = 0;
    virtual void turnComponentOFF(HAMSTER_FUNCTIONAL_CODE component_code) = 0;
    
protected:
    void setComponentState(uint8_t number, HAMSTER_COMPONENT_STATE state);
    void printComponents(){
        std::cout << "Components:" << std::endl;
        for (int i = 0; i < num_components; i++) {
            std::cout << "Number: " << (int) my_components[i].getNumber() << std::endl;
            std::cout << "Code: " << my_components[i].getCode() << std::endl;
        }

    }
private:
    uint8_t num_components;
    HAMSTERUVComponent * my_components;
    
//-----------------------------------------------------------------------------
// HAMSTER Node methods
//-----------------------------------------------------------------------------
    std::ostream& printNode(std::ostream& stream) const;
};

}
#endif /* HAMSTEROBJECT_H */

