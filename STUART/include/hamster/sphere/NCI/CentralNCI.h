/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CentralNCI.h
 * Author: Mariana
 *
 * Created on 15 de Dezembro de 2017, 16:27
 */

#ifndef CENTRALNCI_H
#define CENTRALNCI_H

#include "NCI.h"
#include "UAV.h"

namespace hamster{
    namespace sphere{
        namespace NCI{
            
        
class CentralNCI : public NCI{
public:
    CentralNCI(Unit * unit,HAMSTERUnitCommInfo * info);
    virtual ~CentralNCI();
//-----------------------------------------------------------------------------
// HAMSTERPlatform methods
//-----------------------------------------------------------------------------
    virtual void executionLoop(void){
        logDebugMessage("Central NCI main loop.");
    };
    virtual void platformTermination(void){};
    void parseMessage(hamster::comm::messaging::HAMSTERMessage * msg){};
    HAMSTER_RETURN requestConnectionToCentralUnit(utils::Uuid& peer_id);
    
    
    
protected:
    bool areAllCriticalModulesAuthenticated() const {
        return all_critical_modules_authenticated;
    }
    
private:
    
    std::ostream& printPlatform(std::ostream& stream) const{return stream;}
    bool all_critical_modules_authenticated = true;

};

    }
}
}


#endif /* CENTRALNCI_H */

