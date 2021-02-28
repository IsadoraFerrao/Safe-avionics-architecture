/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NIMBLE.h
 * Author: Mariana
 *
 * Created on 15 de Dezembro de 2017, 13:38
 */

#ifndef NIMBLE_H
#define NIMBLE_H

#include "HAMSTERPlatform.h"

namespace hamster{
    namespace nimble{
class NIMBLE : public HAMSTERPlatform{
    
    friend class comm::CommBroker;
public:
    NIMBLE(Unit * unit,HAMSTERUnitCommInfo * info);
    virtual ~NIMBLE();
//-----------------------------------------------------------------------------
// HAMSTER Platform Methods
//----------------------------------------------------------------------------- 
    virtual void platformInitialization(void){
        this->SetIncomingQueue(new comm::HAMSTERQueue());
        logDebugMessage("NIMBLE Initialization.");
    }
    virtual void executionLoop(void){};
    virtual void platformTermination(void){};
    void parseMessage(hamster::comm::messaging::HAMSTERMessage * msg){};
    
private:
    
    std::ostream& printPlatform(std::ostream& stream) const{return stream;}

};
    }
}
#endif /* NIMBLE_H */

