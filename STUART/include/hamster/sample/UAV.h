/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UAV.h
 * Author: Mariana
 *
 * Created on 25 de Dezembro de 2017, 14:42
 */

#ifndef UAV_H
#define UAV_H

#include "HAMSTERUserEntity.h"
#include <iostream>

namespace hamster {
namespace sample {

class UAV : public HAMSTERUserEntity {
public:
    // Constructor / Destructor
    UAV(char * config_file_name);
    virtual ~UAV();

    enum class UAV_STATE{
        INITIAL,
        CONNECTING,
        EXECUTING,
        WAIT_RESPONSE,
        FINALIZING
    };
    
    // Entity methods
    virtual void customInitialization(void);
    virtual void customExecution(void);
    virtual void customTermination(void);
    virtual void processMessage(utils::Uuid& peer_id, char * message);
    
protected:
    UAV_STATE getState(){
        return this->my_state;
    }
            void setState(UAV_STATE my_state) {
                this->my_state = my_state;
            }

private:
    UAV_STATE my_state = UAV_STATE::INITIAL;
 
};

} /* namespace sample */
} /* namespace hamster */
#endif /* UAV_H */

