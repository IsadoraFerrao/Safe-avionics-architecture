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
 * \if DESIGN_MODEL
 * 
 *  \anchor Connector
 *  \class hamster::comm::interface::Connector Connector.h
 *  \brief Connects to another HAMSTER Unit's acceptor in order to establish a 
 *  peer-to-peer connection.
 *  \details This class connects to another HAMSTER Unit's acceptor, creating a 
 *  \ref ConnectionHandler "Connection Handler" trhough which the unit can send
 *  and receive messages.
 * 
 *  \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 *  \copyright GNU Lesser General Public License.
 * 
 *  \endif
 */

#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "HAMSTER.h"
#include "ConnectionHandler.h"
#include "HAMSTERPeer.h"
#include "AddressInfo.h"


namespace hamster{
namespace comm{
namespace interface{

class Connector {
public:

// Constructor / Destructor
    Connector(CommInterface * interface);
    virtual ~Connector();
    
// Connector methods
    /*!
     * \fn hamster::comm::interface::Connector::connectTo()
     * \brief Attempts to connect to another HAMSTER Unit' acceptor. If the 
     * connection is successfull, a ConnectionHandler is returned; otherwise, a
     * NULL pointer is returned.
     */
    virtual ConnectionHandler * connectTo(AddressInfo * info) = 0;
    
protected:
    CommInterface* getCommInterface() const {
        return my_interface;
    }
    
private:
    /*!< \brief The interface which the acceptor belongs to. */
    CommInterface * my_interface;

};

} /* namespace interface */
} /* namespace comm */
} /* namespace hamster */

#endif /* CONNECTOR_H */

