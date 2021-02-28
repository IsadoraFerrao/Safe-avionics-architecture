/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AddressInfo.cc
 * Author: Mariana
 * 
 * Created on 9 de Janeiro de 2018, 13:06
 */

#include "AddressInfo.h"
#include "INETSocketAddressInfo.h"

namespace hamster{
namespace comm{
namespace interface{

AddressInfo::AddressInfo(){   
}   
AddressInfo::AddressInfo(AddressInfo & info){
}    
AddressInfo::~AddressInfo(){
}
    
AddressInfo * AddressInfo::buildAddressInfo(interface::COMM_INTERFACE_TECH type){
    switch(type){
        case interface::COMM_INTERFACE_TECH::SOCKET:
            return new inet_socket::INETSocketAddressInfo();
            break;
        default:
            logErrorMessage("Unknown interface tech.");
            return NULL;
            break;
    }
}


} /* namespace interface */
} /* namespace comm */
} /* namespace hamster */