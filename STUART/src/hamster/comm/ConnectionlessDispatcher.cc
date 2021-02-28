/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * \file   ConnectionlessDispatcher.cc
 * \author rodrigues.mariana@gmail.com
 * \date 2018
 * \copyright
 */

#include "ConnectionlessDispatcher.h"

namespace hamster{
namespace comm{
    
/* Initialize unique instance with NULL pointer. */
ConnectionlessDispatcher * ConnectionlessDispatcher::unique_dispatcher = NULL;

ConnectionlessDispatcher::ConnectionlessDispatcher() {
}

ConnectionlessDispatcher::~ConnectionlessDispatcher() {
}

ConnectionlessDispatcher * ConnectionlessDispatcher::getConnectionlessDispatcher(){
    if(unique_dispatcher == NULL){
        unique_dispatcher = new ConnectionlessDispatcher();
    }
    return unique_dispatcher;
}

        
} /* namespace comm */
} /* namespace hamster */