/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LocalSMU.h
 * Author: Mariana
 *
 * Created on 30 de Março de 2018, 12:36
 */

#ifndef LOCALSMU_H
#define LOCALSMU_H

#include "SMU.h"


namespace hamster{
    namespace sphere{
        namespace smu{
            
class LocalSMU : public SMU{
public:
    LocalSMU(Unit * unit, HAMSTERUnitCommInfo * info);
    virtual ~LocalSMU();
    
//-----------------------------------------------------------------------------
// HAMSTERPlatform methods
//-----------------------------------------------------------------------------
    virtual void executionLoop(void){
        logDebugMessage("Central SMU main loop.");
    };
    virtual void platformTermination(void){};
    void parseMessage(hamster::comm::messaging::HAMSTERMessage * msg){};
private:
std::ostream& printPlatform(std::ostream& stream) const{return stream;}  
};

        }
    }
}
#endif /* LOCALSMU_H */

