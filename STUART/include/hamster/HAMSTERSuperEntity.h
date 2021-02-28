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
 * \anchor HAMSTERSuperEntity
 * \class hamster::HAMSTERSuperEntity HAMSTERSuperEntity.h
 * \brief Class that represents a central HAMSTER unity in a centralized 
 * architecture scenario.
 * \details A HAMSTER Super Entity is a special type of \ref HAMSTEREntity 
 * "HAMSTER Entity" that has a central role in a centralized architecture 
 * operation scenario.
 * 
 * The Super Entity has the responsibility to correctly identify and authenticate
 * the components of the system, and can assume roles as a Certification Authority
 * (CA) and perform cryptographic key distribution tasks if necessary.
 * 
 * In a known formation scenario (\ref scenario1), the Super Entity already has 
 * the information of all \ref HAMSTEREntity "entities" that compose the system.
 * The Super Entity has the responsibility of authenticating all entities of the
 * system before the mission is initialized.
 * 
 * In an unknown formation scenario (\ref scenario2), the Super Entity also has
 * to perform a correct identification of al entities that compose the system.
 * 
 * \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 *
 */

#ifndef HAMSTERSUPERENTITY_H
#define HAMSTERSUPERENTITY_H

#include "HAMSTEREntity.h"
#include "comm/CommBroker.h"

namespace hamster{
    
namespace comm{class CommBroker; namespace interface{class CommInterface;}}
namespace navigation_phases{class NPUnit;}    
namespace nci{class NCI;}
namespace nimble{class NIMBLE;}
namespace sphere{class SPHERE;}
    
class HAMSTERSuperEntity : public HAMSTEREntity {
public:

//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
    HAMSTERSuperEntity(char * config_file_named);
    virtual ~HAMSTERSuperEntity();
    
//-----------------------------------------------------------------------------
// HAMSTER Node methods
//-----------------------------------------------------------------------------
    virtual void initialize(void);
    virtual void execute(void);
    virtual void nodeTermination(void);
    
    virtual void initializationFinished(){
//        std::map<utils::Uuid, comm::HAMSTERPeer*> my_peers = this->getCommunicationInfo()->getPeerList();
//        comm::messaging::HAMSTERMessage * msg = 
//                new comm::messaging::HAMSTERMessage(
//                    comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
//                    comm::messaging::HAMSTER_MESSAGE_CODE::HAMSTER_SETUP_FINISHED);
//        for (std::pair<utils::Uuid, comm::HAMSTERPeer*> peer : my_peers) {
//            msg->setRecipient(peer.second);
//            this->getCommunicationBbroker()->parseMessage(msg);
//        }
        hamster::Unit::initializationFinished();
    }

private:
    bool is_activated = false;
};

} /* namespace hamster */

#endif /* HAMSTERSUPERENTITY_H */

