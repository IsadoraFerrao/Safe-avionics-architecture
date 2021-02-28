/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LocalCSU.h
 * Author: Mariana
 *
 * Created on 29 de Março de 2018, 10:06
 */

#ifndef LOCALCSU_H
#define LOCALCSU_H

#include "HAMSTER.h"
#include "CSU.h"

namespace hamster{
namespace sphere{
namespace csu {
    

class LocalCSU : public CSU{
public:
//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
    LocalCSU(Unit * unit, HAMSTERUnitCommInfo * info);
    virtual ~LocalCSU();

//-----------------------------------------------------------------------------
// HAMSTERNode methods
//-----------------------------------------------------------------------------
    virtual void executionLoop(void);
    virtual void platformTermination(void){};
    virtual void parseMessage(hamster::comm::messaging::HAMSTERMessage* msg);
    //HAMSTER_RETURN requestConnectionToCentralUnit(utils::Uuid& peer_id);

private:
    /*!
     * \fn virtual std::ostream& hamster::HAMSTERNode::printNode(std::ostream& stream) const
     * \brief Outputs the information of the HAMSTERNode to the output stream.
     * \details Pure virtual method which inserts the details of a HAMSTER Node
     * in an output stream to be used in operator << overload.
     * \attention All concrete child classes must provide an implementation for
     * this method.
     */
    std::ostream& printPlatform(std::ostream& stream) const{return stream;}

};

} /* namespace csu */
} /* namespace sphere */
} /* namespace hamster */

#endif /* LOCALCSU_H */

