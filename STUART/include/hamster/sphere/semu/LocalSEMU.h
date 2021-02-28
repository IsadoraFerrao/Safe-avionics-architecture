/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LocalSEMU.h
 * Author: Mariana
 *
 * Created on 30 de Março de 2018, 12:37
 */

#ifndef LOCALSEMU_H
#define LOCALSEMU_H

#include "SEMU.h"


namespace hamster{
    namespace sphere{
        namespace semu{
            class LocalSEMU : public SEMU{
public:
    LocalSEMU(Unit * unit, HAMSTERUnitCommInfo * info);
    virtual ~LocalSEMU();
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



#endif /* LOCALSEMU_H */

