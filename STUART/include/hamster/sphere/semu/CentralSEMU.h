/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CentralSEMU.h
 * Author: Mariana
 *
 * Created on 15 de Dezembro de 2017, 15:52
 */

#ifndef CENTRALSEMU_H
#define CENTRALSEMU_H

#include "SEMU.h"

namespace hamster {
    namespace sphere {
        namespace semu {
            
class CentralSEMU : public SEMU{
public:
    CentralSEMU(hamster::Unit * unit,HAMSTERUnitCommInfo * info);
    virtual ~CentralSEMU();
//-----------------------------------------------------------------------------
// HAMSTERPlatform methods
//-----------------------------------------------------------------------------
    virtual void executionLoop(void){
        logDebugMessage("Central SEMU execution loop.");
    };
    virtual void platformTermination(void){};
    void parseMessage(hamster::comm::messaging::HAMSTERMessage * msg){};
    
private:
    
    std::ostream& printPlatform(std::ostream& stream) const{return stream;}

};

        }
    }
}

#endif /* CENTRALSEMU_H */

