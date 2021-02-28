/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MessageField.h
 * Author: Mariana
 *
 * Created on 16 de Fevereiro de 2018, 10:10
 */

#ifndef MESSAGEFIELD_H
#define MESSAGEFIELD_H
//\todo Documentação

#include "HAMSTER.h"

namespace hamster{
namespace comm{
namespace messaging{
    
    class HAMSTERMessage;

class MessageField {
public:
    MessageField();
    MessageField(const MessageField& orig);
    virtual ~MessageField();
    
    
    virtual int pushInPayload(char ** buffer) = 0;
    virtual int pullFromPayload(char * buffer) = 0;
    
private:

};

} /* namespace messaging */
} /* namespace comm */
} /* namespace hamster */
#endif /* MESSAGEFIELD_H */

