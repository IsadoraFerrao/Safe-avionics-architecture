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
 *  \anchor CommInterface
 *  \class hamster::comm::interface::CommInterface CommInterface.h
 *  \brief Represents a network interface of a HAMSTER Unit.
 *  \details This class is used to manage a network interface, and is unique for
 *  each network the HAMSTER Unit is inserted. If a unit has more than one 
 *  interface, more than one instance needs to be initialized. The interface has
 *  three auxiliary classes: Acceptor, Connector and ConnectionHandler. 
 * 
 *  The Acceptor enables the unit to accept peers from the same network. It will
 *  answer connection requests from other units' connectors. In a client-server
 *  architecture, for instance, the Acceptor would be the server.
 * 
 *  The Connector is responsible for connecting to a Acceptor in order to 
 *  establish a peer-to-peer connection with another unit. 
 * 
 *  Once the connection request is accepted, a ConnectionHandler object must be
 *  created on both sides of the connection and associated to the respective 
 *  peer. This is done by updating table HAMSTERPeerInformation within the 
 *  \ref Unit "HAMSTER Unit".
 * 
 *  \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 *  \copyright GNU Lesser General Public License.
 * 
 *  \endif
 */

#ifndef COMMINTERFACE_H
#define COMMINTERFACE_H


#include "Unit.h"
#include "HAMSTERPlatform.h"
#include "HAMSTERPeer.h"
#include "CommBroker.h"
#include <list>
#include <string>


namespace hamster{
namespace comm{
namespace interface{
    
class AcceptorConn;
class Connector;
class ConnectionHandler;
class AddressInfo;

//-----------------------------------------------------------------------------
// Communication Interface Technology
//-----------------------------------------------------------------------------
/*! 
 * \anchor COMM_INTERFACE_TECH
 * \enum COMM_INTERFACE_TECH
 * \brief Describes the available technologies for Interfaces supported by 
 * HAMSTER Architecture.
 * \details New techonologies can be added as the architecture expands. 
 */
enum class COMM_INTERFACE_TECH : uint8_t{
    WIFI = 1,       /*!< The interface follows a IEEE 802.11 standard. */
    ETHERNET = 2,   /*!< The interface follows a IEEE 802.3 standard. */
    SOCKET = 3      /*!< Generic socket interface. */
};

inline std::ostream& operator<<(std::ostream& stream, const COMM_INTERFACE_TECH& tech) {
    switch (tech) {
        case COMM_INTERFACE_TECH::WIFI:
            stream << "WIFI";
            break;
        case COMM_INTERFACE_TECH::ETHERNET:
            stream << "Ethernet";
            break;
        case COMM_INTERFACE_TECH::SOCKET:
            stream << "Socket";
            break;
        default:
            break;
    }
    return stream;
}

//-----------------------------------------------------------------------------
// Communication Interface Type
//-----------------------------------------------------------------------------
/*! 
 * \anchor COMM_INTERFACE_TYPE
 * \enum COMM_INTERFACE_TYPE
 * \brief Determines if the communication is internal (between an entity and its
 * clusters and modules) or external (between entities). If necessary, new types
 * can be used.
 */
enum class COMM_INTERFACE_TYPE : uint8_t {
    UNKNOWN = 0,
    ENTITY_MODULE = 1,    /*!< The interface is between an entity and its modules.*/
    ENTITY_ENTITY = 2     /*!< The interface is between entities. */
};

inline std::ostream& operator<<(std::ostream& stream, const COMM_INTERFACE_TYPE& type) {
    switch (type) {
        case COMM_INTERFACE_TYPE::ENTITY_MODULE:
            stream << "ENTITY_MODULE";
            break;
        case COMM_INTERFACE_TYPE::ENTITY_ENTITY:
            stream << "ENTITY_ENTITY";
            break;
        default:
            break;
    }
    return stream;
}

inline COMM_INTERFACE_TYPE& operator<<(COMM_INTERFACE_TYPE& type, const int value){
    switch(value){
        case 1:
            type = COMM_INTERFACE_TYPE::ENTITY_MODULE;
            break;
        case 2:
            type = COMM_INTERFACE_TYPE::ENTITY_ENTITY;
            break;
        default:
            type = COMM_INTERFACE_TYPE::UNKNOWN;
            break;
    }
    return type;
}


class CommInterface : public HAMSTERPlatform {
    
    friend class CommBroker;
    friend class AcceptorConn;
    friend class Connector;
    friend class ConnectionHandler;
    
public:
// Constructor/Destructor
    CommInterface(uint8_t number, Unit * unit, HAMSTERUnitCommInfo * info, COMM_INTERFACE_TYPE t,COMM_INTERFACE_TECH tech, AddressInfo * acceptor_info);
    virtual ~CommInterface();
    
    void platformInitialization();
    void dados();
    void parseMessage(hamster::comm::messaging::HAMSTERMessage* msg);

// Interface Methods
    /*!
     * \fn hamster::comm::interface::CommInterface::getInterfaceNumber
     * \brief Get the integer identifier of the interface.
     */
    uint8_t getInterfaceNumber();
    /*!
     * \fn hamster::comm::interface::CommInterface::loadAcceptor
     * \brief Starts the Acceptor of the interface.
     */
    virtual HAMSTER_RETURN loadAcceptor();
    /*!
     * \fn hamster::comm::interface::CommInterface::isAcceptorOpen
     * \brief Informs whether the acceptor is opened or not.
     * acceptor.
     */
    bool isAcceptorOpen();
    /*!
     * \fn hamster::comm::interface::CommInterface::connectToPeer
     * \brief Connects with the acceptor of another HAMSTER Unit.
     */
    virtual HAMSTER_RETURN connectToPeer(HAMSTERPeer * peer);
    /*!
     * \fn hamster::comm::interface::CommInterface::closeConnection
     * \brief Closes all connections and acceptor of the interface.
     */
    virtual HAMSTER_RETURN closeInterface();
    /*!
     * \fn hamster::comm::interface::CommInterface::numIncomingConnections
     * \brief Returns the number of incoming connections of this interface.
     */
    int numIncomingConnections();
    /*!
     * \fn hamster::comm::interface::CommInterface::numOutgoingConnections
     * \brief Returns the number of incoming connections of this interface.
     */
    int numOutgoingConnections();
    
// Public GET Methods
    COMM_INTERFACE_TYPE getType() const;
    COMM_INTERFACE_TECH getTechnology() const;


protected:
// Interface Methods
    /*!
     * \fn hamster::comm::interface::CommInterface::addNewIncoming
     * \brief Inserts a new connection in the interface incoming connection list.
     */
    HAMSTER_RETURN addNewIncoming(ConnectionHandler * handler);
    /*!
     * \fn hamster::comm::interface::CommInterface::addNewOutgoing
     * \brief Inserts a new connection in the interface outgoing connection list.
     */
    HAMSTER_RETURN addNewOutgoing(ConnectionHandler * handler);
     /*!
     * \fn hamster::comm::interface::CommInterface::removeIncoming
     * \brief Removes a connection in the interface incoming connection list.
     */
    HAMSTER_RETURN removeIncoming(ConnectionHandler * handler);
    /*!
     * \fn hamster::comm::interface::CommInterface::removeOutgoing
     * \brief Removes a connection in the interface outgoing connection list.
     */
    HAMSTER_RETURN removeOutgoing(ConnectionHandler * handler);
    
    HAMSTER_RETURN sendMessageToPeer(messaging::HAMSTERMessage * msg, HAMSTERPeer * peer);
    
    
// SET methods
    void setType(COMM_INTERFACE_TYPE type);
    void setAcceptor(AcceptorConn * acc);
    void setConnector(Connector * con);
// GET methods
    AcceptorConn* getAcceptor() const;

    void executionLoop(void);
    
private:
    /*!< \brief integer identifier of the interface */
    uint8_t interface_number;
    /*!< \brief The technology of the interface, given by COMM_INTERFACE_TECH. */
    COMM_INTERFACE_TECH technology;
    /*!< \brief The type of the interface, given by COMM_INTERFACE_TYPE. */
    COMM_INTERFACE_TYPE type;
    /*!< \brief Makes the unit available for establishing connections in the 
     *   interface. */
    AcceptorConn * acceptor;
    /*!< \brief Stores the address info of acceptor. */
    AddressInfo * acceptor_address;
    /*!< \brief Connects the HAMSTER Unit to other HAMSTER units. */
    Connector * connector;
    /*!< \brief List of all incoming connections of the interface. */
    std::list<ConnectionHandler *> incoming_connections;
    /*!< \brief List of all outgoing connections of the interface. */
    std::list<ConnectionHandler *> outgoing_connections;
};

} /* namespace interface */
} /* namespace comm */
} /* namespace hamster */

#endif /* COMMINTERFACE_H */

