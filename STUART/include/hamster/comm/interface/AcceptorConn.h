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
 *  \anchor AcceptorConn
 *  \class hamster::comm::interface::AcceptorConn AcceptorConn.h
 *  \brief Makes the unit available for establishing connections in the 
 *  interface.
 *  \details This class opens a connection in the network in which the interface
 *  is inserted, making the unit ready to receive connection requests from other
 *  HAMSTER units.
 * 
 *  \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 *  \copyright GNU Lesser General Public License.
 * 
 *  \endif
 */

#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "CommInterface.h"
#include "ConnectionHandler.h"

namespace hamster{
namespace comm{
namespace interface{

class AcceptorConn {
public:

// Constructor / Destructor
    AcceptorConn(CommInterface * interface);
    virtual ~AcceptorConn();
    
// AcceptorConn methods
    /*! \fn hamster::comm::interface::AcceptorConn::open()
     *  \brief Opens a connection so that the AcceptorConn can receive connection
     *  requests.
     */
    virtual HAMSTER_RETURN open();
    /*! \fn hamster::comm::interface::AcceptorConn::close()
     *  \brief Closes the connection.
     */
    virtual HAMSTER_RETURN close();
    /*! \fn hamster::comm::interface::AcceptorConn::isOpen()
     *  \brief Returns the state of the connection.
     */
    bool isOpen();
    /*! \fn hamster::comm::interface::AcceptorConn::loadAcceptorConnThread()
     *  \brief Initializes the thread with the acceptor main loop.
     */
    static void acceptorThread(AcceptorConn * acc);
    
// Public GET Methods
    std::thread * getThread() const {
        return acceptor_thread;
    }
    
protected:
    CommInterface* getCommInterface() const {
        return my_interface;
    }
    void setAcceptorThread(std::thread * thread) {
        this->acceptor_thread = thread;
    }
    HAMSTER_RETURN addNewConnection(ConnectionHandler * handler);

    void waitIDMessage(ConnectionHandler * handler,AddressInfo * info){
        handler->setConnection_thread(new std::thread(AcceptorConn::waitPeerIdentification,this,handler,info));
    }
    
    static void waitPeerIdentification (AcceptorConn * acc, ConnectionHandler * handler, AddressInfo * info);
    
private:
    /*! \fn hamster::comm::interface::AcceptorConn::threadLoop()
     *  \brief Method called by loadAcceptorConnThread method that effectly runs
     *  within the thread. Must be overloaded by all child classes.
     */
    virtual void threadLoop(void) = 0;
    /*!< \brief The interface which the acceptor belongs to. */
    CommInterface * my_interface;
    /*!< \brief Control variable to indicate if the connection is opened or not. */
    bool isAccOpen = false;
    /*!< \brief Thread in which the acceptor runs. */
    std::thread * acceptor_thread = NULL;
    bool finalize = false;
};

} /* namespace interface */
} /* namespace comm */
} /* namespace hamster */

#endif /* ACCEPTOR_H */

