/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HAMSTERUnitDescriptor.h
 * Author: Mariana
 *
 * Created on 27 de Março de 2018, 13:34
 */

#ifndef HAMSTERUNITDESCRIPTOR_H
#define HAMSTERUNITDESCRIPTOR_H

#include "Uuid.h"
#include "HAMSTER_UNIT_TYPE.h"
#include "HAMSTERPeer.h"

namespace hamster{

class HAMSTERUnitDescriptor {
public:
    HAMSTERUnitDescriptor(utils::Uuid id, HAMSTER_UNIT_TYPE type);
    virtual ~HAMSTERUnitDescriptor();
    
    utils::Uuid getUnitID() const;
    HAMSTER_UNIT_TYPE getUnitType() const;
    comm::HAMSTERPeer* getUnitCommunicationInfo() const;
    void setUnitCommunicationInfo(comm::HAMSTERPeer * comm_info);

protected:
    void setUnitID(utils::Uuid unit_ID);
    void setUnitType(HAMSTER_UNIT_TYPE unit_type);

private:
    /*!< \brief Unit type. */
    HAMSTER_UNIT_TYPE unit_type;
    /*!< \brief Unit ID number. */
    utils::Uuid unit_ID;
    /*!< Unit Networking information. */
    comm::HAMSTERPeer * unit_comm_info;
};

} /* namespace hamster */

#endif /* HAMSTERUNITDESCRIPTOR_H */

