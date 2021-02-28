/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SEMU.h
 * Author: Mariana
 *
 * Created on 15 de Dezembro de 2017, 14:45
 */

#ifndef SEMU_H
#define SEMU_H

#include "HAMSTERPlatform.h"

namespace hamster {
    namespace sphere {
        namespace semu {

            class SEMU : public HAMSTERPlatform {
                friend class comm::CommBroker;
            public:

                SEMU(Unit * unit, HAMSTERUnitCommInfo * info) : HAMSTERPlatform(unit,info) {
                };

                virtual ~SEMU() {
                };
//-----------------------------------------------------------------------------
// HAMSTER Platform Methods
//----------------------------------------------------------------------------- 
    virtual void platformInitialization(void){
        this->SetIncomingQueue(new comm::HAMSTERQueue());
        logDebugMessage("SEMU Initialization.");
    }

            };

        }
    }
}
#endif /* SEMU_H */

