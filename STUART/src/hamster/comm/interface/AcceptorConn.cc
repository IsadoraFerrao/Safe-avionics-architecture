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

/* 
 * \file    Acceptor.cc
 * \author: Mariana Rodrigues   rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#include "AcceptorConn.h"
#include "ConnectionHandler.h"
#include "Connector.h"
#include "FarashRegistraton.h"

namespace hamster{
namespace comm{
namespace interface{
    
// Constructor / Destructor
AcceptorConn::AcceptorConn(CommInterface * interface):my_interface(interface){
}
AcceptorConn::~AcceptorConn(){
}

// Acceptor methods
HAMSTER_RETURN AcceptorConn::open(){
    this->isAccOpen = true;
    return HAMSTER_RETURN::RETURN_OK;
}
HAMSTER_RETURN AcceptorConn::close(){
    this->isAccOpen = false;
    return HAMSTER_RETURN::RETURN_OK;
}
bool AcceptorConn::isOpen(){
    return this->isAccOpen;
}
 void AcceptorConn::acceptorThread(AcceptorConn * acc){
     acc->threadLoop();
 }
HAMSTER_RETURN AcceptorConn::addNewConnection(ConnectionHandler * handler){
    HAMSTER_RETURN ret =  this->my_interface->addNewIncoming(handler);
    if(ret != RETURN_OK){
        //\todo Colocar error codes aqui.
        logErrorMessage("Could not add client to Incoming List. (Error code ",
                ret,"). Unit ID = ",this->getCommInterface()->GetUnit()->getID().toString());
    }
    return ret;
}

void AcceptorConn::waitPeerIdentification (AcceptorConn * acc, ConnectionHandler * handler, AddressInfo * client_info){
    logDebugMessage("WaitPeerIdentification.");
            
    bool id_received = false;
    
    do{
        // Wait for new message
        messaging::HAMSTERMessage * msg = handler->receiveMessage();
        // Verify if the message has an identification
        if(msg->getCode() == messaging::HAMSTER_MESSAGE_CODE::HAMSTER_UNIT_ID){
            logDebugMessage("HAMSTER_UNIT_ID received.");
            std::array<unsigned char, 32> secret;
            utils::Uuid peer_id;
            // Extract data
            unsigned char message_data [msg->getMessageSize()-12];
            memcpy(message_data,msg->getMessagePayload()+12,msg->getMessageSize()-12);
            if(acc->my_interface->GetUnit()->getReg()->verifyRegistration(acc->my_interface->GetUnit()->getType(),
                    message_data,&peer_id,&secret) == true){
                    // Verify if ID is already on peer list
                    HAMSTERPeer * peer = acc->my_interface->getCommInfo()->getPeer(peer_id);
                    if(peer == NULL){
                        // Peer not in list
                        logDebugMessage("New PEER.");
                        /* \FIXME Quando o UAV conecta em outro UAV, ele usa o client_info
                         * para construir o peer, então não manda a conexão para a porta
                         * que o UAV está ouvindo.
                         */
                        peer = new HAMSTERPeer(acc->my_interface,client_info,peer_id);
                        acc->my_interface->getCommInfo()->AddPeer(peer);
                    }
                    // Set receiving handler
                    peer->SetRecHandler(handler);
                    // Verify if the peer was already connected
                    if(peer->getSenHandler() == NULL){
                        // Not connected yet
                        logDebugMessage("Peer not connected yet --- connect.");
                        if(acc->my_interface->connectToPeer(peer) == RETURN_NOK){
                            // What to do?
                            //\todo Tratar erro de falha de conexão.
                        }
                    }else{
                        // This is a return connection. (I have already connected to it).
                        logDebugMessage("Peer already connected. Just initialize.");
                        //                delete peer->GetAddress();
                        //                peer->SetPeerAddressInfo(client_info);
                    }
                    // Client is now fully connected
                    peer->SetConnected(true);
                    peer->SetSecret(secret.data());
                    std::cout << "Key received:" << secret.data();
                    std::cout << std::endl;
                    
                    handler->setConnection_thread(new std::thread(ConnectionHandler::waitForMessage,handler));
                    id_received = true;
            }else{
                logErrorMessage("registration failed");
            }
        }else{
            logDebugMessage("Message other than HAMSTER_UNIT_ID received.");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
    }while((acc->finalize == false)&&(id_received == false));
}


} /* namespace interface */
} /* namespace comm */
} /* namespace hamster */