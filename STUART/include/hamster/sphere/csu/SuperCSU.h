/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SuperCSU.h
 * Author: Mariana
 *
 * Created on 25 de Janeiro de 2018, 10:44
 */

#ifndef SUPERCSU_H
#define SUPERCSU_H

#include "CentralCSU.h"

namespace hamster{
namespace sphere{
namespace csu{

class SuperCSU : public CentralCSU{
public:
    SuperCSU(Unit * unit, HAMSTERUnitCommInfo * info);
    virtual ~SuperCSU();
//-----------------------------------------------------------------------------
// HAMSTERNode methods
//-----------------------------------------------------------------------------
    void executionLoop(void);
    virtual void platformTermination(void){};
    virtual void parseMessage(hamster::comm::messaging::HAMSTERMessage* msg);
    
};

            
} /* namespace csu */
} /* namespace sphere */
} /* namespace hamster */
#endif /* SUPERCSU_H */

