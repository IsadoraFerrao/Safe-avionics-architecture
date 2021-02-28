/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ECCRelicHandler.h
 * Author: Mariana
 *
 * Created on 18 de Maio de 2018, 15:55
 */

#ifndef ECCRELICHANDLER_H
#define ECCRELICHANDLER_H

#include "CryptographyHandler.h"
#include "MessageField.h"
#include "relic.h"
#include "ECCRelicKeyInfo.h"

namespace hamster{
namespace comm{
namespace cryptography{
    
class ECCRelicHandler : public CryptographyHandler{
public:
    ECCRelicHandler(ECCRelicKeyInfo * key_info);
    ECCRelicHandler(const ECCRelicHandler& orig);
    virtual ~ECCRelicHandler();
    
// -----------------------------------------------------------------------------
// CryptographyHandler methods
// -----------------------------------------------------------------------------
    virtual void initialize();
    virtual messaging::HAMSTERMessage * encryptMessage(messaging::HAMSTERMessage *);
    virtual messaging::HAMSTERMessage * decryptMessage(messaging::HAMSTERMessage *);
    ECCRelicKeyInfo * getKeyInfo(){
        return my_keys;
    }


private:
    ECCRelicKeyInfo * my_keys = NULL;
};


} /* namespace cryptography */
} /* namespace comm */
} /* namespace hamster */

#endif /* ECCRELICHANDLER_H */

