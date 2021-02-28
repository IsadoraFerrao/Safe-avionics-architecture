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
 * \anchor HAMSTEREntity
 * \class hamster::HAMSTEREntity HAMSTEREntity.h
 * \brief Class that represents any HAMSTER-enabled vehicle or control station. 
 * \details A HAMSTER Entity represents an unmanned vehicle or control station 
 * in a HAMSTER-enabled system.
 * 
 * The class can be specialized to different types of vehicles (aerial, ground
 * or water vehicles) in order to attend specific demands of each segment.
 * 
 * Each HAMSTER Entity can be composed of HAMSTER objects, which represent the 
 * internal components of each vehicle/station.
 * 
 * \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 *
 */

#ifndef HAMSTERENTITY_H
#define HAMSTERENTITY_H

#include "Unit.h"
#include "HAMSTERObject.h"
#include "CentralSPHERE.h"
#include "HAMSTERPeer.h"
#include "HAMSTERObjectDescriptor.h"
#include "HAMSTERMessage.h"

//class hamster::HAMSTERObject;

namespace hamster {

class HAMSTEREntity : public Unit{
public:
//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
    HAMSTEREntity(char * config_file_name);
    virtual ~HAMSTEREntity();
    
//-----------------------------------------------------------------------------
// User methods to be overloaded by application
//-----------------------------------------------------------------------------
    virtual void customInitialization(void) = 0;
    virtual void customExecution(void) = 0;
    virtual void customTermination(void) = 0;
    virtual void processMessage(utils::Uuid& peer_id, char * message) = 0;
    
    /*! \fn hamster::HAMSTEREntity::areAllModulesAuthenticated
     *  \brief Verify if all required objects have authenticated.
     */
    bool areAllRequiredObjectsAuthenticated();    
    
    bool areAllObjectsConnected();
    
    HAMSTERObjectDescriptor ** getEntityObjects(uint8_t * number_objects) const {
        HAMSTERObjectDescriptor ** objects = new HAMSTERObjectDescriptor*[this->number_of_objects];
        (*number_objects) = number_of_objects;
        uint8_t index = 0;
        // Iterate over the object map using c++11 range based for loop
        for (std::pair<utils::Uuid,HAMSTERObjectDescriptor *> element : this->entity_objects) {
            objects[index] = element.second;
            index++;
        }
        return objects;
    }
    
    void parseMessage(hamster::comm::messaging::HAMSTERMessage * msg);
    
protected:
//-----------------------------------------------------------------------------
// Object list Methods
//-----------------------------------------------------------------------------
    /*! \fn hamster::HAMSTEREntity::addObject(comm::HAMSTERPeer * peer)
     *  \brief Add a new object to the object list.
     */
    HAMSTER_RETURN addObject(HAMSTERObjectDescriptor *);
    /*! \fn hamster::HAMSTEREntity::objectExists(utils::Uuid id)
     *  \briefs Indicate if a HAMSTER Object is already on the object list.
     */
    bool objectExists(utils::Uuid id);
    /*! \fn hamster::HAMSTEREntity::getPeerFromID
     *  \brief Returns the communication information of an object based on its ID
     */
    comm::HAMSTERPeer * getPeerFromID(utils::Uuid id);
    
    void putMessageInBroker(comm::messaging::HAMSTERMessage * msg);


//-----------------------------------------------------------------------------
    comm::HAMSTERPeer * getCentralUnit(){
        return this->getCommunicationInfo()->getCentralUnit();
    }
    
    std::ostream& printNode(std::ostream& stream) const;
    

//-----------------------------------------------------------------------------
// HAMSTERNode methods
//-----------------------------------------------------------------------------
    virtual void initialize(void);
    virtual void execute(void);
    virtual void nodeTermination(void);

private:    
//-----------------------------------------------------------------------------
// HAMSTER Communication
//-----------------------------------------------------------------------------
    /*!< \brief Objects that compose the Entity. */
    std::map<utils::Uuid,HAMSTERObjectDescriptor * > entity_objects;
    uint8_t number_of_objects;

};
    
} /* namespace hamster */

#endif /* HAMSTERENTITY_H */

