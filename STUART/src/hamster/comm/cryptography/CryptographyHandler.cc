/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CryptographyHandler.cc
 * Author: Mariana
 * 
 * Created on 18 de Maio de 2018, 11:18
 */

#include "CryptographyHandler.h"
#include "HAMSTERMessage.h"

namespace hamster{
namespace comm{
namespace cryptography{

CryptographyHandler::CryptographyHandler(CryptographyAlgorithm * alg, CRYPTOGRAPHY_TYPE type):crypt_algorithm(alg),crypt_type(type) {
//CryptographyHandler::CryptographyHandler(){
}

CryptographyHandler::CryptographyHandler(const CryptographyHandler& orig):crypt_algorithm(orig.crypt_algorithm),crypt_type(orig.crypt_type) {
//CryptographyHandler::CryptographyHandler(const CryptographyHandler& orig){
    
}

CryptographyHandler::~CryptographyHandler() {
}

// -----------------------------------------------------------------------------
// Get methods
// -----------------------------------------------------------------------------
CryptographyAlgorithm * CryptographyHandler::getAlgorithm() const {
    return crypt_algorithm;
}

CRYPTOGRAPHY_TYPE CryptographyHandler::getType() const {
    return crypt_type;
}
} /* namespace cryptography */
} /* namespace comm */
} /* namespace hamster */