/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CriptographyAlgorithm.cc
 * Author: Mariana
 * 
 * Created on 10 de Setembro de 2018, 14:45
 */

#include "CryptographyAlgorithm.h"

namespace hamster{
namespace comm{
namespace cryptography{

CryptographyAlgorithm::CryptographyAlgorithm(CRYPTOGRAPHY_TYPE type):cryp_type(type) {
}

//CriptographyAlgorithm::CriptographyAlgorithm(const CriptographyAlgorithm& orig):cryp_type(orig.cryp_type) {
//}

CryptographyAlgorithm::~CryptographyAlgorithm() {
}

} /* namespace cryptography */
} /* namespace comm */
} /* namespace hamster */