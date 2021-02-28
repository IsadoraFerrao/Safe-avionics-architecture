/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Configurable.h
 * Author: Mariana
 *
 * Created on 10 de Abril de 2019, 13:36
 */

#ifndef CONFIGURABLE_H
#define CONFIGURABLE_H

#include <vector>

#include "HAMSTER.h"

namespace hamster{
namespace utils{

class Configurable {
public:
    Configurable();
    virtual ~Configurable();
    
    virtual HAMSTER_RETURN parseConfigurationMessage(std::vector<unsigned char>) = 0;
private:

};

}
}

#endif /* CONFIGURABLE_H */

