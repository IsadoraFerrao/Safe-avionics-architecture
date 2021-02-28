/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Registerer.h
 * Author: Mariana
 *
 * Created on 9 de Abril de 2019, 15:51
 */

#ifndef REGISTERER_H
#define REGISTERER_H

#include <assert.h>
#include "HAMSTER.h"
#include "RegistrationStrategy.h"


namespace hamster{
namespace registration{
    
template <class strategy>
class Registerer {
public:
    Registerer(){
        static_assert(std::is_base_of<RegistrationStrategy,strategy>::value,
            "Registration Strategy adopted do not derive from class RegistrationStrategy.");
    };
    virtual ~Registerer(){};
private:

};

    
}
}


#endif /* REGISTERER_H */

