/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ECCRelicHandler.cc
 * Author: Mariana
 * 
 * Created on 18 de Maio de 2018, 15:55
 */

#include "ECCRelicHandler.h"
#include "../ECCRelic.h"
#include "HAMSTERMessage.h"


namespace hamster{
namespace comm{
namespace cryptography{
            
ECCRelicHandler::ECCRelicHandler(ECCRelicKeyInfo * key_info):CryptographyHandler((CryptographyAlgorithm *) new ECCRelic(),CRYPTOGRAPHY_TYPE::ASYMMETRICAL) {
     try {
         this->my_keys = dynamic_cast<ECCRelicKeyInfo *>(key_info);
     } catch(const std::bad_cast& e){
        //logErrorMessage("KeyInfo provided is not of correct cast. Message:",e.what());
    }
}

ECCRelicHandler::ECCRelicHandler(const ECCRelicHandler& orig):
    CryptographyHandler(new ECCRelic(),CRYPTOGRAPHY_TYPE::ASYMMETRICAL){
    my_keys = orig.my_keys;
}

ECCRelicHandler::~ECCRelicHandler() {
}

void ECCRelicHandler::initialize(){
    //logVerboseMessage("Initialize function in ECCRelic Handler");
//    // Initialize keys
//    bn_t n;
//    
//    //Private key
//    bn_new(n);
//    bn_new(this->privKey);
//    ep_curve_get_ord(n);
//    bn_rand(this->privKey,BN_POS, bn_bits(n));
//
//    //Public key
//    ep_null(this->myPublicKey);
//    ep_new(this->myPublicKey);
//    ep_mul_gen(this->myPublicKey, privKey);
}

messaging::HAMSTERMessage * ECCRelicHandler::encryptMessage(messaging::HAMSTERMessage * msg){
    messaging::HAMSTERMessage * crypted_message;
    char * crypted_text;
    int size;
    size = this->getAlgorithm()->encrypt(&crypted_text,msg->getMessagePayload(),msg->getMessageSize(), (KeyInfo *)this->my_keys,msg->getRecipient()->GetKeyInfo());
    crypted_message = new messaging::HAMSTERMessage(msg->getDirection(),crypted_text,msg->getCode(),size,msg->getRecipient());
    logVerboseMessage("EncryptMessage - crypted message built");
    msg->destroyBuffer();
    logVerboseMessage("EncryptMessage - buffer destroyed");
//    delete msg;
    return crypted_message;
}
messaging::HAMSTERMessage * ECCRelicHandler::decryptMessage(messaging::HAMSTERMessage * msg){
    messaging::HAMSTERMessage * decrypted_message;
    char * plain_text;
    int size;
    size = this->getAlgorithm()->decrypt(msg->getMessagePayload(),&plain_text,msg->getMessageSize(),(KeyInfo *)this->my_keys,msg->getRecipient()->GetKeyInfo());
    decrypted_message = new messaging::HAMSTERMessage(msg->getDirection(),plain_text,msg->getCode(),size,msg->getRecipient());
    decrypted_message->extractCode();
    decrypted_message->printPayload();
    msg->destroyBuffer();
//    delete msg;
    return decrypted_message;
}




} /* namespace cryptography */
} /* namespace comm */
} /* namespace hamster */