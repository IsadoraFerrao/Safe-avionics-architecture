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
 * \anchor Unit
 * \class hamster::Unit Unit.h
 * \brief Class that represents any HAMSTER-enabled component.
 * \details The HAMSTER Unit is the base class of any HAMSTER-enabled component,
 * providing the necessary structure for the unmanned vehicle to be integrated
 * into a HAMSTER-enabled system.
 * 
 * HAMSTER Units are further specialized into \ref HAMSTEREntity "entities", 
 * comprising the unmanned vehicled as a whole, or \ref HAMSTERObject "objects",
 * which which handle the internal sensors/actuators of an entity.  HAMSTER 
 * Objects are further specialized into Modules and Clusters. A HAMSTER Module 
 * is a unit which handles a single sensor/actuator of the unmanned vehicle, 
 * like the GPS sensor; a HAMSTER Cluster is a unit which handles a set of 
 * sensor/actuators with one common communication interface.
 * 
 * \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 *
 */

#ifndef UNIT_H
#define UNIT_H

#include "HAMSTER.h"
#include "HAMSTERNode.h"
#include "HAMSTER_UNIT_TYPE.h"
#include "Uuid.h"
#include <cstdint>


namespace hamster {
    
namespace comm{ namespace messaging{class HAMSTERMessage;}}
class HAMSTERUnitCommInfo;
namespace comm{class CommBroker; class HAMSTERPeer; namespace interface{class CommInterface;}}
namespace navigation_phases{class NPUnit;}    
//namespace nci{class NCI;}
namespace nimble{class NIMBLE;}
namespace sphere{class SPHERE;}
namespace sample{namespace registration{class FarashRegistraton;}}

class Unit : public HAMSTERNode {
    
//-----------------------------------------------------------------------------
// Friend classes
//-----------------------------------------------------------------------------
    friend class comm::CommBroker;
    
//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
public:
    Unit(char * config_file_name);
    virtual ~Unit();

    void load(){    
        this->initialize();
        this->execute();
        this->nodeTermination();
    }
    
    /*! 
     * \fn void HAMSTERPlatform::parseMessage()
     * \brief Method of message parsing.
     * \details Pure virtual method which perform the necessary steps to 
     * parse possible messages received by the platform.
     * \attention All concrete child classes must provide an implementation 
     * for this method.
     */
    virtual void parseMessage(hamster::comm::messaging::HAMSTERMessage * msg) = 0;
    
//-----------------------------------------------------------------------------    
// HAMSTERNode Methods
//-----------------------------------------------------------------------------
    virtual void initialize(void);
    virtual comm::messaging::HAMSTERMessage * getIDMessage(comm::HAMSTERPeer * peer); //>>> JINT
    virtual void processMessage(utils::Uuid& peer_id, char * message) = 0;
    
//-----------------------------------------------------------------------------    
// Public GET operators
//-----------------------------------------------------------------------------
    utils::Uuid getID() const;
    HAMSTER_UNIT_TYPE getType() const;
    
        virtual void initializationFinished(){
        this->initialization_finished = true;
    }
        
        sample::registration::FarashRegistraton* getReg() const {
            return reg;
        }

    
protected:
//-----------------------------------------------------------------------------
// HAMSTER Node methods
//-----------------------------------------------------------------------------
   
    bool startCustomExecution();

    
//-----------------------------------------------------------------------------
// SET operators
//-----------------------------------------------------------------------------
    //void setNCIPlatform(nci::NCI* nci_platform);
    void setNIMBLEPlatform(nimble::NIMBLE* nimble_platform);
    void setNPPlatform(navigation_phases::NPUnit* np_platform);
    void setSPHEREPlatform(sphere::SPHERE* sphere_platform);
    void setType(HAMSTER_UNIT_TYPE type);
//-----------------------------------------------------------------------------
// GET platforms methods
//-----------------------------------------------------------------------------
    comm::CommBroker* getCommunicationBbroker() const;
    sphere::SPHERE* getSPHEREPlatform() const;
    //nci::NCI* getNCIPlatform() const;
    nimble::NIMBLE* getNIMBLEPlatform() const;
    navigation_phases::NPUnit* getNPPlatform() const ;
    comm::interface::CommInterface * getInterface(int number);
        HAMSTERUnitCommInfo* getCommunicationInfo() const {
            return communication_info;
        }
        


    HAMSTER_RETURN AddPeer(comm::HAMSTERPeer * peer);
    
    /*!
     * \fn std::ostream& hamster::HAMSTERUnit::printNode(std::ostream& stream) const
     * \brief Outputs basic information for HAMSTER Units (type and ID).
     * \details This function is called by child classes to output basic node data.
     * \note Child classes, when overloading this method, can invoke base class
     * method (\c hamster::HAMSTERUnit::printNode()) and add specific data to
     * stream afterwards.
     */
    virtual std::ostream& printNode(std::ostream& stream) const;
    
    
        bool start_execution_received = false;

private:
//-----------------------------------------------------------------------------
// HAMSTER Unit Attributes
//-----------------------------------------------------------------------------
    /*!< \brief Type of HAMSTER Unit. Read-only attribute to be initialized 
     *   by concrete classes. */
    HAMSTER_UNIT_TYPE type;

    /*!< \brief Unit ID number. Initialized in class constructor, and cannot
     *    be modified afterwards.
     */
    utils::Uuid ID;
    
    /*!< \brief Communication info of the HAMSTER unit, including communication
     *   interfaces and system configurations.
     */
    
    HAMSTERUnitCommInfo * communication_info;
    
    bool initialization_finished = false;
    
//-----------------------------------------------------------------------------
// HAMSTER Platforms
//-----------------------------------------------------------------------------
    /*!< \brief Points to the Navigation Phaes platform. The type of platform 
     * (Agent or Manager) will be dependent on the unit type.
     */
    navigation_phases::NPUnit * np_platform = NULL;
    /*!< \brief Points to the NCI platform. The type of platform (Entity, module
     * or cluster) will be dependent on the unit type.
     */
   // nci::NCI * nci_platform = NULL;
    /*!< \brief Points to the NIMBLE platform. Available only in HAMSTER Entities.
     */
    nimble::NIMBLE * nimble_platform = NULL;
    /*!< \brief Points to the sphere platform. The type of platform 
     * (Central, Local, Super) will be dependent on the unit type.
     */
    sphere::SPHERE * sphere_platform = NULL;
    /*!< \brief Points to the communication broker, responsible for parsing all
     * HAMSTER Messages and provide inter-thread communication between HAMSTER
     * platforms.
     */
    comm::CommBroker * communication_broker = NULL;
    
    sample::registration::FarashRegistraton * reg;
    
//-----------------------------------------------------------------------------
// Implementation-only declaration
//-----------------------------------------------------------------------------
    void setType(int type_code);

};

} /* namespace hamster */
#endif /* UNIT_H */

