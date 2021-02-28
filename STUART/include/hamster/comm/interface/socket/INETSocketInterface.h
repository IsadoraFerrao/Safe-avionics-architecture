/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   INETSocketInterface.h
 * Author: Mariana
 *
 * Created on 25 de Dezembro de 2017, 11:36
 */

#ifndef INETSOCKETINTERFACE_H
#define INETSOCKETINTERFACE_H

#define DEFAULT_INETSOCKET_ADRRESS       "127.0.0.1"
#define DEFAULT_INETSOCKET_PORT                12000
#define DEFAULT_INETSOCKET_MAXCONN                10

#include "CommInterface.h"
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace hamster{
namespace comm{
namespace interface{
namespace inet_socket{
    
    class INETSocketAddressInfo;
    
enum class INETSocketProtocol : int{
    UNKNOWN = 0,
    TCP = 1,
    UDP = 2
};

inline INETSocketProtocol& operator<<(INETSocketProtocol& prot, int prot_code){
    switch(prot_code){
        case 1:
            prot = INETSocketProtocol::TCP;
            break;
        case 2:
            prot = INETSocketProtocol::UDP;
            break;
        default:
            prot =  INETSocketProtocol::UNKNOWN;
            break;
    }
    return prot;
}
    
class INETSocketInterface : public CommInterface{
public:
    INETSocketInterface(uint8_t number,Unit * unit, HAMSTERUnitCommInfo * info,
        COMM_INTERFACE_TYPE type,INETSocketAddressInfo * acc_info,
        int max_acc_connections);
    virtual ~INETSocketInterface();
//-----------------------------------------------------------------------------
// HAMSTERNode methods
//-----------------------------------------------------------------------------
    void platformInitialization(void){
        CommInterface::platformInitialization();
        logDebugMessage("INET Socket interface initialized.");
    };
    
    void dados(void);
//    void executionLoop(void){};
    void platformTermination(void);
//    void parseMessage(hamster::comm::messaging::HAMSTERMessage* msg){};
    
private:
    /*!
     * \fn virtual std::ostream& hamster::HAMSTERNode::printNode(std::ostream& stream) const
     * \brief Outputs the information of the HAMSTERNode to the output stream.
     * \details Pure virtual method which inserts the details of a HAMSTER Node
     * in an output stream to be used in operator << overload.
     * \attention All concrete child classes must provide an implementation for
     * this method.
     */
    std::ostream& printPlatform(std::ostream& stream) const{return stream;}

};

} /* namespace socket */
} /* namespace interface */
} /* namespace comm */
} /* namespace hamster */

#endif /* INETSOCKETINTERFACE_H */

