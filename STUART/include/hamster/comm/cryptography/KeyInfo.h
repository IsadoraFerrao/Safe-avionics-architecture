/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   KeyInfo.h
 * Author: Mariana
 *
 * Created on 5 de Setembro de 2018, 16:15
 */

#ifndef KEYINFO_H
#define KEYINFO_H

#include "MessageField.h"

namespace hamster{
namespace comm{
namespace cryptography{

class KeyInfo : public messaging::MessageField{
public:
    KeyInfo();
    KeyInfo(const KeyInfo& orig);
    virtual ~KeyInfo();
    virtual void printKey(){};
private:

};

} /* namespace cryptography */
} /* namespace comm */
} /* namespace hamster */

#endif /* KEYINFO_H */

