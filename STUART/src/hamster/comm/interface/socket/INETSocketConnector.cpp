/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   INETSocketConnector.cpp
 * Author: Mariana
 * 
 * Created on 9 de Janeiro de 2018, 13:14
 */

#include "INETSocketConnector.h"
#include "INETSocketHandler.h"

namespace hamster{
namespace comm{
namespace interface{
namespace inet_socket{

// Constructor / Destructor
INETSocketConnector::INETSocketConnector(CommInterface * interface):Connector(interface) {
}
INETSocketConnector::~INETSocketConnector() {
}

// Connector methods
ConnectionHandler *  INETSocketConnector::connectTo(AddressInfo * info){
    INETSocketAddressInfo * socket_info = (INETSocketAddressInfo *) info;
    INETSocketHandler * handler;
    int socket_descriptor = socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in server_address = socket_info->GetAddress();
    
    
    if (socket_descriptor == -1) {
        logErrorMessage("Could not create socket in connector. Error number = ",errno,"Unit ID = ",
                this->getCommInterface()->GetUnit()->getID().toString(),
                "\t Communication interface type = ",this->getCommInterface()->getType());
        return NULL;
    }
    // Connects to server
    if (connect(socket_descriptor, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        logErrorMessage("Could not connect to specified server. Error no = ", errno,
                " Unit ID = ",this->getCommInterface()->GetUnit()->getID().toString(),
                "\t Communication interface type = ",this->getCommInterface()->getType());
        return NULL;
    }
    // Connection successful    
    handler = new INETSocketHandler(socket_descriptor,static_cast<INETSocketInterface *>(this->getCommInterface()));
    return handler;
}

} /* namespace inet_socket */
} /* namespace interface */
} /* namespace comm */
} /* namespace hamster */