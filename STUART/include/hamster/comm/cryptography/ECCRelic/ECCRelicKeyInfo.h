/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ECCRelicKeyInfo.h
 * Author: Mariana
 *
 * Created on 5 de Setembro de 2018, 16:34
 */

#ifndef ECCRELICKEYINFO_H
#define ECCRELICKEYINFO_H

#include "KeyInfo.h"
extern "C" {
#include "relic.h"
}

namespace hamster{
namespace comm{
namespace cryptography{

    
class ECCRelicKeyInfo : public KeyInfo{
public:
    ECCRelicKeyInfo();
    ECCRelicKeyInfo(const ECCRelicKeyInfo& orig);
    virtual ~ECCRelicKeyInfo();
    
    virtual int pushInPayload(char ** buffer);
    virtual int pullFromPayload(char * buffer);
    
    ep_t& getPublicKey(){return this->my_public_key;};
    bn_t& getPrivateKey(){return this->my_private_key;};
    
    void printKey() override{
        std::cout << "My public Key: ";
        ep_print(my_public_key);
        std::cout << std::endl;
    }
    
private:
    
    bn_t my_private_key;
    ep_t my_public_key;

};


} /* namespace cryptography */
} /* namespace comm */
} /* namespace hamster */

#endif /* ECCRELICKEYINFO_H */

