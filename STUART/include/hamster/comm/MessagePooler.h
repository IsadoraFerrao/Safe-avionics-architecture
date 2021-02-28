/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MessagePooler.h
 * Author: Mariana
 *
 * Created on 4 de Abril de 2018, 07:42
 */

/* Classe para aguardar resposta de vários destinatários.*/

#ifndef MESSAGEPOOLER_H
#define MESSAGEPOOLER_H

#include "HAMSTER.h"
#include "HAMSTER_MESSAGE_CODE.h"
#include <list>
#include <utility>

namespace hamster{
namespace comm{

class MessagePooler {
public:
    MessagePooler();
    virtual ~MessagePooler();
    
    HAMSTER_RETURN addResponse2Pool(messaging::HAMSTER_MESSAGE_CODE code,utils::Uuid id);
    HAMSTER_RETURN messageReceived(messaging::HAMSTER_MESSAGE_CODE code,utils::Uuid id);
    bool isAwaitingMessage(messaging::HAMSTER_MESSAGE_CODE code);
    
private:
    std::list<std::pair<utils::Uuid,messaging::HAMSTER_MESSAGE_CODE>> message_pool;
};

} /* namespace comm */
} /* namespace hamster */
#endif /* MESSAGEPOOLER_H */

