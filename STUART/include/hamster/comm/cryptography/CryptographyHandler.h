/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CryptographyHandler.h
 * Author: Mariana
 *
 * Created on 18 de Maio de 2018, 11:18
 */

#ifndef CRYPTOGRAPHYHANDLER_H
#define CRYPTOGRAPHYHANDLER_H

#include "HAMSTER.h"
#include "MessageField.h"
#include "CRYPTOGRAPHY_ALGORITMS.h"
#include "CryptographyAlgorithm.h"

namespace hamster{
namespace comm{
    namespace messaging{class HAMSTERMessage;}
namespace cryptography{
    
class CryptographyHandler{
public:
    CryptographyHandler(CryptographyAlgorithm * alg, CRYPTOGRAPHY_TYPE type);
//    CryptographyHandler();
    CryptographyHandler(const CryptographyHandler& orig);
    virtual ~CryptographyHandler();
    
// -----------------------------------------------------------------------------
// Cryptography handler methods
// -----------------------------------------------------------------------------
    virtual void initialize() = 0;
    virtual messaging::HAMSTERMessage * encryptMessage(messaging::HAMSTERMessage *) = 0;
    virtual messaging::HAMSTERMessage * decryptMessage(messaging::HAMSTERMessage *) = 0;
//    virtual KeyInfo * getKeyInfo() = 0;
    
// -----------------------------------------------------------------------------
// Get methods
// -----------------------------------------------------------------------------
    CryptographyAlgorithm * getAlgorithm() const ;
    CRYPTOGRAPHY_TYPE getType() const ;
    
private:
    CryptographyAlgorithm * crypt_algorithm;
    CRYPTOGRAPHY_TYPE crypt_type;

};

} /* namespace cryptography */
} /* namespace comm */
} /* namespace hamster */



#endif /* CRYPTOGRAPHYHANDLER_H */

