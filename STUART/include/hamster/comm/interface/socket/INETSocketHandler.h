/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   INETSocketHandler.h
 * Author: Mariana
 *
 * Created on 8 de Janeiro de 2018, 16:32
 */

#ifndef INETSOCKETHANDLER_H
#define INETSOCKETHANDLER_H

#include "ConnectionHandler.h"
#include "INETSocketInterface.h"

namespace hamster{
namespace comm{
namespace interface{
namespace inet_socket{

class INETSocketHandler : public ConnectionHandler {
public:
// Constructor / Destructor
    INETSocketHandler(int descriptor,INETSocketInterface * interface);
    virtual ~INETSocketHandler();
    
// Connection Handler Methods
    virtual HAMSTER_RETURN sendMessage(messaging::HAMSTERMessage * message);
    virtual messaging::HAMSTERMessage * const receiveMessage();   
    virtual HAMSTER_RETURN closeConnection();

private:    
    int socket_descriptor;
    std::thread * supervision_thread;
    
};

} /* namespace socket */
} /* namespace interface */
} /* namespace comm */
} /* namespace hamster */

#endif /* INETSOCKETHANDLER_H */

