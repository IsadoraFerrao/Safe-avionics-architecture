/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   INETSocketAddressInfo.h
 * Author: Mariana
 *
 * Created on 9 de Janeiro de 2018, 13:17
 */

#ifndef SOCKETADDRESSINFO_H
#define SOCKETADDRESSINFO_H

#include "AddressInfo.h"
#include "INETSocketInterface.h"

namespace hamster{
namespace comm{
namespace interface{
namespace inet_socket{
    
class INETSocketAddressInfo : public AddressInfo {
public:
    INETSocketAddressInfo();
    INETSocketAddressInfo(char * address, int port, INETSocketProtocol type);
    INETSocketAddressInfo(char * address, int port);
    INETSocketAddressInfo(struct sockaddr_in);
    virtual ~INETSocketAddressInfo();

    struct sockaddr_in GetAddress() const;
    INETSocketProtocol GetProt() const;
    virtual int pushInPayload(char ** buffer);
    int pullFromPayload(char * buffer);

    
private:
    struct sockaddr_in socket_address;
    INETSocketProtocol prot;
};

} /* namespace inet_socket */
} /* namespace interface */
} /* namespace comm */
} /* namespace hamster */

#endif /* SOCKETADDRESSINFO_H */

