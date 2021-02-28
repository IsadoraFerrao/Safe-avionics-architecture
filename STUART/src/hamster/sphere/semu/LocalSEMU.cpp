/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LocalSEMU.cpp
 * Author: Mariana
 * 
 * Created on 30 de Março de 2018, 12:37
 */

#include "LocalSEMU.h"

namespace hamster{
    namespace sphere{
        namespace semu{

LocalSEMU::LocalSEMU(Unit * unit, HAMSTERUnitCommInfo * info):SEMU(unit,info) {
}


LocalSEMU::~LocalSEMU() {
}

        }
    }}