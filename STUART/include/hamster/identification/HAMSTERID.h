/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HAMSTERID.h
 * Author: Mariana
 *
 * Created on 17 de Maio de 2018, 17:28
 */

#ifndef HAMSTERID_H
#define HAMSTERID_H

#include "HAMSTER.h"

namespace hamster{
namespace identification{

class HAMSTERID {

public:
    HAMSTERID(){
      
    }
    HAMSTERID(const HAMSTERID& orig){};
    virtual ~HAMSTERID() = 0;

    
//-----------------------------------------------------------------------------
// Operator overloading
//-----------------------------------------------------------------------------

private:

};

} /* namespace identification */
} /* namespace hamster */
#endif /* HAMSTERID_H */

