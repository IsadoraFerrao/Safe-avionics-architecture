/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CriptographyAlgorithm.h
 * Author: Mariana
 *
 * Created on 10 de Setembro de 2018, 14:45
 */

#ifndef CRIPTOGRAPHYALGORITHM_H
#define CRIPTOGRAPHYALGORITHM_H

//#include "HAMSTER.h"
#include "KeyInfo.h"
#include "CRYPTOGRAPHY_ALGORITMS.h"


namespace hamster{
namespace comm{
namespace cryptography{
    
class CryptographyAlgorithm {
public:
    CryptographyAlgorithm(CRYPTOGRAPHY_TYPE type);
//    CriptographyAlgorithm(const CriptographyAlgorithm& orig);
    virtual ~CryptographyAlgorithm();
    
    virtual void initializeKeys(KeyInfo * key_info) = 0;
    virtual int encrypt(char ** criptext, char * plaintext, int plaintext_size, KeyInfo * my_key_info, KeyInfo * peer_key_info) = 0;
    virtual int decrypt(char * criptext, char ** plaintext, int crypttext_size, KeyInfo * my_key_info, KeyInfo * peer_key_info) = 0;
private:
    CRYPTOGRAPHY_TYPE cryp_type;

};

} /* namespace cryptography */
} /* namespace comm */
} /* namespace hamster */

#endif /* CRIPTOGRAPHYALGORITHM_H */

