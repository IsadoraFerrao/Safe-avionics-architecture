/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LocalSPHERE.h
 * Author: Mariana
 *
 * Created on 30 de Março de 2018, 10:53
 */

#ifndef LOCALSPHERE_H
#define LOCALSPHERE_H

#include "SPHERE.h"

namespace hamster{
namespace sphere{
    
class LocalSPHERE : public SPHERE{
public:
//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
    LocalSPHERE(Unit * unit, HAMSTERUnitCommInfo * info);
    virtual ~LocalSPHERE();
    
//-----------------------------------------------------------------------------
// HAMSTERPlatform methods
//-----------------------------------------------------------------------------
//    virtual void platformInitialization();
    virtual void executionLoop(void);
    virtual void platformTermination(void);
    void parseMessage(hamster::comm::messaging::HAMSTERMessage * msg);
    
private:    
    std::ostream& printPlatform(std::ostream& stream) const{return stream;}
};

} /* namespace sphere */
} /* namespace hamster */

#endif /* LOCALSPHERE_H */

