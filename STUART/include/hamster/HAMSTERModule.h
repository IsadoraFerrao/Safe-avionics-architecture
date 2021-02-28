/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HAMSTERModule.h
 * Author: Mariana
 *
 * Created on 8 de Março de 2018, 15:35
 */

#ifndef HAMSTERMODULE_H
#define HAMSTERMODULE_H

#include "HAMSTERObject.h"

namespace hamster{

class HAMSTERModule : public HAMSTERObject{
public:
    HAMSTERModule(char * config_file_name);
    virtual ~HAMSTERModule();
private:

};
} /* namespace hamster */
#endif /* HAMSTERMODULE_H */

