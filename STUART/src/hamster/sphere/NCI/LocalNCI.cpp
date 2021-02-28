/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LocalNCI.cpp
 * Author: Mariana
 * 
 * Created on 30 de Março de 2018, 12:36
 */

#include "LocalNCI.h"

namespace hamster{
    namespace sphere{
        namespace NCI{
            
LocalNCI::LocalNCI(Unit * unit, HAMSTERUnitCommInfo * info) : NCI(unit,info){
}


LocalNCI::~LocalNCI() {
}

        }
    }
}