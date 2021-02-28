/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LocalSMU.cpp
 * Author: Mariana
 * 
 * Created on 30 de Março de 2018, 12:36
 */

#include "LocalSMU.h"

namespace hamster{
    namespace sphere{
        namespace smu{
            
LocalSMU::LocalSMU(Unit * unit, HAMSTERUnitCommInfo * info) : SMU(unit,info){
}


LocalSMU::~LocalSMU() {
}

        }
    }
}