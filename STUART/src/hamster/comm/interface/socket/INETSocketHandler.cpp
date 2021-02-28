/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   INETSocketHandler.cpp
 * Author: Mariana
 * 
 * Created on 8 de Janeiro de 2018, 16:32
 */

#include "INETSocketHandler.h"
#include <iostream>

namespace hamster{
namespace comm{
namespace interface{
namespace inet_socket{

// Constructor / Destructor
INETSocketHandler::INETSocketHandler(int descriptor,INETSocketInterface * interface):ConnectionHandler(interface),socket_descriptor(descriptor) {
}
INETSocketHandler::~INETSocketHandler() {
}

// Connection Handler Methods
HAMSTER_RETURN INETSocketHandler::sendMessage(messaging::HAMSTERMessage * message){
    message->printPayload();
    size_t bytes_sent = send(this->socket_descriptor, message->getMessagePayload(), 
            message->getMessageSize(),0);
    if(bytes_sent == message->getMessageSize()){
        return RETURN_OK;
    }
    return RETURN_NOK;
}
messaging::HAMSTERMessage * const INETSocketHandler::receiveMessage(){
    char * buffer = new char[MAX_BUFFER_SIZE];
    messaging::HAMSTERMessage * msg;
    
    ssize_t received_byes = recv(this->socket_descriptor, buffer, MAX_BUFFER_SIZE, 0);
    if (received_byes < 0) {
        // Error in receive
        logErrorMessage("Could not receive from socket. Error number = ",errno,"Unit ID = ",
                this->getInterface()->GetUnit()->getID().toString(),
                "\t Communication interface type = ",this->getInterface()->getType());
        this->closeHandler();
        return NULL;
    }else if(received_byes == 0){
        // Socket was shutdown from the other side.
        this->closeHandler();
    }else{
        std::cout << "MESSAGE BUFFER:" << std::endl;
        for (int i = 0; i < received_byes; i++) {
            std::cout << buffer[i];
        }
        std::cout  << std::endl;
        for (int i = 0; i < received_byes; i++) {
            printf("%02x",(uint8_t) buffer[i]);
        }
        std::cout  << std::endl;
        msg = new messaging::HAMSTERMessage(messaging::HAMSTER_MESSAGE_DIRECTION::INTERNAL,buffer,received_byes);
        // Set Peer if it exists
        msg->setRecipient(this->getMyPeer());
        return msg;
    }
    return nullptr;
}
HAMSTER_RETURN INETSocketHandler::closeConnection(){
    int ret = ::close(this->socket_descriptor);
    
    return ret>=0?HAMSTER_RETURN::RETURN_OK:HAMSTER_RETURN::RETURN_NOK;
}

} /* namespace socket */
} /* namespace interface */
} /* namespace comm */
} /* namespace hamster */