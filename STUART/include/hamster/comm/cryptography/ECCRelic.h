/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ECCRelic.h
 * Author: Mariana
 *
 * Created on 10 de Setembro de 2018, 19:43
 */

#ifndef ECCRELIC_H
#define ECCRELIC_H

#include "ECCRelicKeyInfo.h"
#include "CryptographyAlgorithm.h"

namespace hamster{
namespace comm{
namespace cryptography{
    
#define MESSAGESIZE 32

class ECCRelic : public CryptographyAlgorithm{
public:
    ECCRelic();
    virtual ~ECCRelic();
    
    virtual void initializeKeys(KeyInfo * key_info);
    virtual int encrypt(char ** criptext, char * plaintext, int plaintext_size, KeyInfo * my_key_info, KeyInfo * peer_key_info);
    virtual int decrypt(char * criptext, char ** plaintext, int crypttext_size, KeyInfo * my_key_info, KeyInfo * peer_key_info);
private:
    int write_ep(unsigned char *out, ep_t source);
    int read_ep(unsigned char *in, ep_t destination);
};

} /* namespace cryptography */
} /* namespace comm */
} /* namespace hamster */


#endif /* ECCRELIC_H */

