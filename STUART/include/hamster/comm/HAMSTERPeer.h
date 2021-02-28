/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HAMSTERPeer.h
 * Author: Mariana
 *
 * Created on 10 de Janeiro de 2018, 15:05
 */

#ifndef HAMSTERPEER_H
#define HAMSTERPEER_H

#include "HAMSTER.h"
#include "Uuid.h"
#include "CryptographyHandler.h"
#include "KeyInfo.h"

namespace hamster{
namespace comm{
    
namespace interface{
    class CommInterface;
    class ConnectionHandler;
    class AddressInfo;
}

class HAMSTERPeer {
public:
    HAMSTERPeer(interface::CommInterface * inter, interface::AddressInfo * info, utils::Uuid& id);
    virtual ~HAMSTERPeer();
    

    utils::Uuid GetID() const {
        return ID;
    }

    interface::CommInterface* GetInterface() const {
        return peer_interface;
    }

    interface::AddressInfo* GetAddress() const {
        return peer_address;
    }
    
    interface::ConnectionHandler * getRecHandler() const{
        return rx_handler;
    }
    
    interface::ConnectionHandler * getSenHandler() const{
        return tx_handler;
    }
    
    bool isAuthorized() const {
        return authorized;
    }
    
    bool isConnected() const {
        return connected;
    }
    
    void SetAuthorized(bool authorized) {
        this->authorized = authorized;
    }

    void SetConnected(bool connected) {
        this->connected = connected;
    }

    void SetRecHandler(interface::ConnectionHandler* handler) {
        this->rx_handler = handler;
    }
    
    void SetSenHanlder(interface::ConnectionHandler * handler){
        this->tx_handler = handler;
    }
    
    void SetPeerAddressInfo(interface::AddressInfo* info) {
        this->peer_address = info;
    }
    
    HAMSTER_RETURN disconnect();
    HAMSTER_RETURN resetPeerData();
    
    cryptography::KeyInfo* GetKeyInfo() const {
        return peer_key_info;
    }
    
    void SetKeyInfo(cryptography::KeyInfo* peer_key_info) {
        this->peer_key_info = peer_key_info;
    }
    
    cryptography::CryptographyHandler* GetPeer_crypto_handler() const {
        return peer_crypto_handler;
    }

    void SetPeer_crypto_handler(cryptography::CryptographyHandler* peer_crypto_handler) {
        this->peer_crypto_handler = peer_crypto_handler;
    }

            const unsigned char * GetSecret() const {
                return secret;
            }

            void SetSecret(unsigned char * secret) {
                for (int i = 0; i < 32; i++) {
                    this->secret[i] = secret[i];

                }
               
            }



private:
    utils::Uuid ID;
    interface::CommInterface * peer_interface = NULL;
    interface::AddressInfo * peer_address = NULL;
    interface::ConnectionHandler * tx_handler = NULL;
    interface::ConnectionHandler * rx_handler = NULL;
    cryptography::KeyInfo * peer_key_info = NULL;
    cryptography::CryptographyHandler * peer_crypto_handler = NULL;
    unsigned char secret[32];
    
    bool authorized = false;
    bool connected = false;
    
    // \todo Insetir: chave pública e privada??
};

} /* namespace comm */
} /* namespace hamster */


#endif /* HAMSTERPEER_H */

