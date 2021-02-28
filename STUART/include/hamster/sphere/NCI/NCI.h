/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NCI.h
 * Author: Mariana
 *
 * Created on 15 de Dezembro de 2017, 14:42
 */

#ifndef NCI_H
#define NCI_H

#include "HAMSTERPlatform.h"
#include <string>
#include "MQTTClient.h"


namespace hamster {
    namespace sphere {
        namespace NCI {

            class NCI : public HAMSTERPlatform {
                friend class comm::CommBroker;
            public:

                NCI(Unit * unit, HAMSTERUnitCommInfo * info) : HAMSTERPlatform(unit, info) {
                };
                virtual ~NCI(){};
//-----------------------------------------------------------------------------
// HAMSTER Platform Methods
//----------------------------------------------------------------------------- 
                virtual void platformInitialization(void){
                    this->SetIncomingQueue(new comm::HAMSTERQueue());
                    logDebugMessage("NCI Initialization.");
                    
                }
                            
            };
        }
    }
}
#endif /* NCI_H */

