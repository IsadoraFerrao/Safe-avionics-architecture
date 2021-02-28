/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HAMSTERModulePeer.cc
 * Author: Mariana
 * 
 * Created on 26 de Março de 2018, 13:21
 */

#include "HAMSTERObjectPeer.h"

namespace hamster{
namespace comm{

HAMSTERObjectPeer::HAMSTERObjectPeer(interface::CommInterface * inter, interface::AddressInfo * info, utils::Uuid& id) : HAMSTERPeer(inter,info,id) {
}

HAMSTERObjectPeer::~HAMSTERObjectPeer() {
}

} /* namespace comm */
} /* namespace hamster */