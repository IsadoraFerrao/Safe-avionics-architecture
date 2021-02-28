/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CentralSMU.h
 * Author: Mariana
 *
 * Created on 15 de Dezembro de 2017, 16:27
 */

#ifndef CENTRALSMU_H
#define CENTRALSMU_H

#include "SMU.h"

namespace hamster{
    namespace sphere{
        namespace smu{
            
        
class CentralSMU : public SMU{
public:
    CentralSMU(Unit * unit,HAMSTERUnitCommInfo * info);
    virtual ~CentralSMU();
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


#endif /* CENTRALSMU_H */

