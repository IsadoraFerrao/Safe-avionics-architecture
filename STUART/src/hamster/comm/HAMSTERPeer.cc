/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HAMSTERPeer.cpp
 * Author: Mariana
 * 
 * Created on 10 de Janeiro de 2018, 15:05
 */

#include "HAMSTERPeer.h"
#include "ConnectionHandler.h"
#include "Uuid.h"

namespace hamster{
namespace comm{

HAMSTERPeer::HAMSTERPeer(interface::CommInterface * inter, interface::AddressInfo * info, utils::Uuid& id):peer_interface(inter),peer_address(info) {
    this->ID.assign(id.getMostSignificantBits(),id.getLeastSignificantBits());
//    this->peer_key_info = new comm::cryptography::ECCRelicKeyInfo();
}

HAMSTERPeer::~HAMSTERPeer() {
}


// \todo Lidar com cenário decentralizado.
HAMSTER_RETURN HAMSTERPeer::disconnect(){
    HAMSTER_RETURN ret;
    ret = this->tx_handler->closeConnection();
    if(ret == RETURN_OK){
        ret = this->rx_handler->closeConnection();
        if(ret == RETURN_OK){
            this->authorized = false;
            this->connected = false;
            delete tx_handler;
            delete rx_handler;
            this->tx_handler = NULL;
            this->rx_handler = NULL;
        }
    }
    return ret;
}

HAMSTER_RETURN HAMSTERPeer::resetPeerData(){
    HAMSTER_RETURN ret;
    
    this->authorized = false;
    this->connected = false;
    if(this->tx_handler != NULL){
        ret = this->tx_handler->closeConnection();
        if(ret != RETURN_OK){
            return RETURN_NOK;
        }
    }
    if(this->rx_handler != NULL){
        ret = this->rx_handler->closeConnection();
        if(ret != RETURN_OK){
            return RETURN_NOK;
        }
    }
    delete this->tx_handler;
    this->tx_handler = NULL;
    delete this->rx_handler;
    this->rx_handler = NULL;
    return HAMSTER_RETURN::RETURN_OK;   
}

} /* namespace comm */
} /* namespace hamster */
