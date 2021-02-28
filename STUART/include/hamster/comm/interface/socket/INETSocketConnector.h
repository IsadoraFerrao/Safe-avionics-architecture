/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   INETSocketConnector.h
 * Author: Mariana
 *
 * Created on 9 de Janeiro de 2018, 13:14
 */

#ifndef INETSOCKETCONNECTOR_H
#define INETSOCKETCONNECTOR_H

#include "Connector.h"
#include "INETSocketInterface.h"
#include "INETSocketAddressInfo.h"

namespace hamster{
namespace comm{
namespace interface{
namespace inet_socket{

class INETSocketConnector : public Connector{
public:
    // Constructor / Destructor
    INETSocketConnector(CommInterface * interface);
    virtual ~INETSocketConnector();
    // Connector methods
    ConnectionHandler * connectTo(AddressInfo * info);
private:

};

} /* namespace inet_socket */
} /* namespace interface */
} /* namespace comm */
} /* namespace hamster */

#endif /* INETSOCKETCONNECTOR_H */

