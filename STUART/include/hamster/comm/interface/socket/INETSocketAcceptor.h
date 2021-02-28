/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   INETSocketAcceptor.h
 * Author: Mariana
 *
 * Created on 25 de Dezembro de 2017, 12:03
 */

#ifndef INETSOCKETACCEPTOR_H
#define INETSOCKETACCEPTOR_H

#include "AcceptorConn.h"
#include "INETSocketInterface.h"
#include "INETSocketAddressInfo.h"


namespace hamster{
namespace comm{
namespace interface{
namespace inet_socket{
    
class INETSocketAcceptor : public AcceptorConn {
public:
// Constructor / Destructor
    INETSocketAcceptor(CommInterface * interface);
    INETSocketAcceptor(CommInterface * interface, INETSocketAddressInfo * info, int connections);
    virtual ~INETSocketAcceptor();

// Acceptor methods
    HAMSTER_RETURN open(void);
    virtual HAMSTER_RETURN close(void);

private:
    void threadLoop(void);
    
    int acceptor_descriptor;                /*!< \brief Socket descriptor.           */
    const int max_connections;              /*!< \brief Maximum number of connections
                                             *   the acceptor will take.             */
    struct sockaddr_in acceptor_address;    /*!< \brief Adress structure for socket. */
    
    
};

} /* namespace inet_socket */
} /* namespace interface */
} /* namespace comm */
} /* namespace hamster */

#endif /* INETSOCKETACCEPTOR_H */

