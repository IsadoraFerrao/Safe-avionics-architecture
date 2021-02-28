/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HAMSTERModulePeer.h
 * Author: Mariana
 *
 * Created on 26 de Março de 2018, 13:21
 */

#ifndef HAMSTERMODULEPEER_H
#define HAMSTERMODULEPEER_H

#include "HAMSTERPeer.h"


namespace hamster{
    class HAMSTERUVComponent;
namespace comm{

class HAMSTERObjectPeer : public HAMSTERPeer {
public:
    HAMSTERObjectPeer(interface::CommInterface * inter, interface::AddressInfo * info, utils::Uuid& id);
    virtual ~HAMSTERObjectPeer();
private:
    /*!< \brief Number of components in the object: 1 for HAMSTERModules and 2+
     *   for HAMSTERCluster.
     */
    uint8_t num_components;
    /*!< \brief Vector of components. */
    HAMSTERUVComponent * object_components;   

};        

} /* namespace comm */
} /* namespace hamster */

#endif /* HAMSTERMODULEPEER_H */

