/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SuperSPHERE.h
 * Author: Mariana
 *
 * Created on 6 de Dezembro de 2017, 11:36
 */

#ifndef SUPERSPHERE_H
#define SUPERSPHERE_H

#include "SPHERE.h"

namespace hamster{
namespace sphere{

class SuperSPHERE : public SPHERE {
public:
//-----------------------------------------------------------------------------
// Constructor / Destructor
//-----------------------------------------------------------------------------
    SuperSPHERE(Unit * unit,HAMSTERUnitCommInfo * info);
    virtual ~SuperSPHERE();
    
//-----------------------------------------------------------------------------
// HAMSTERPlatform methods
//-----------------------------------------------------------------------------
    virtual void platformTermination(void);
    virtual void executionLoop(void);
    void parseMessage(hamster::comm::messaging::HAMSTERMessage * msg);
    
private:
    std::ostream& printPlatform(std::ostream& stream) const{return stream;}
};

} /* namespace sphere */
} /* namespace hamster */

#endif /* SUPERSPHERE_H */

