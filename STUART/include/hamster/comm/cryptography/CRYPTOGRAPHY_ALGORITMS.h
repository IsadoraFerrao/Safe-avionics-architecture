/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CRYPTOGRAPHY_ALGORITMS.h
 * Author: Mariana
 *
 * Created on 25 de Maio de 2018, 16:36
 */

#ifndef CRYPTOGRAPHY_ALGORITMS_H
#define CRYPTOGRAPHY_ALGORITMS_H

#include <iostream>

namespace hamster{
namespace comm{
namespace cryptography{
    
    
    
enum CRYPTOGRAPHY_TYPE : uint8_t{
    SYMMETRICAL = 0x00,
    ASYMMETRICAL = 0x80
};
            
/*!
 * \attention ASYMMETRICAL algorithms must initialize with 1 at bit 7.
 */
enum CRYPTOGRAPHY_ALGORITM: uint8_t {
    NO_CRYPTO = 0,
    ECC_160,  /*!< Eliptic Curve Criptography with 160-bit key. */
    ECC_256,
    RSA,
    AES,
    UNKNOWN_CRYPTO
};

//CRYPTOGRAPHY_ALGORITM integer2CryptoAlgorithm(int arg);

//inline std::ostream& operator<<(std::ostream& stream, const CRYPTOGRAPHY_TYPE& type){
//    switch(type){
//        case CRYPTOGRAPHY_TYPE::ASYMMETRICAL:
//            stream << "ASYMMETRICAL";
//            break;
//        case CRYPTOGRAPHY_TYPE::SYMMETRICAL:
//            stream << "SYMMETRICAL";
//            break;
//    }
//    return stream;
//}



}
}
}


#endif /* CRYPTOGRAPHY_ALGORITMS_H */

