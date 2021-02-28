/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LocalNCI.h
 * Author: Mariana
 *
 * Created on 30 de Março de 2018, 12:36
 */

#ifndef LOCALNCI_H
#define LOCALNCI_H

#include "HAMSTER.h"
#include "NCI.h"


namespace hamster{
    namespace sphere{
        namespace NCI{
            
class LocalNCI : public NCI{
public:
    LocalNCI(Unit * unit, HAMSTERUnitCommInfo * info);
    virtual ~LocalNCI();
    
//-----------------------------------------------------------------------------
// HAMSTERPlatform methods
//-----------------------------------------------------------------------------
    virtual void executionLoop(void){
        logDebugMessage("Central NCI main loop.");
    };
    virtual void platformTermination(void){};
    void parseMessage(hamster::comm::messaging::HAMSTERMessage * msg){};
private:
std::ostream& printPlatform(std::ostream& stream) const{return stream;}  
};

        }
    }
}
#endif /* LOCALNCI_H */

