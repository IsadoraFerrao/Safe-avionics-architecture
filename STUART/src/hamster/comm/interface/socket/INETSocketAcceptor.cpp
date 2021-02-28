/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   INETSocketAcceptor.cpp
 * Author: Mariana
 * 
 * 
 * Created on 25 de Dezembro de 2017, 12:03
 */

#include "INETSocketAcceptor.h"
#include "INETSocketHandler.h"


namespace hamster{
namespace comm{
namespace interface{
namespace inet_socket{

// Constructor / Destructor
INETSocketAcceptor::INETSocketAcceptor(CommInterface * interface):max_connections(DEFAULT_INETSOCKET_MAXCONN),AcceptorConn(interface) {
    this->acceptor_address.sin_family = AF_INET;
    inet_aton(DEFAULT_INETSOCKET_ADRRESS, &(this->acceptor_address.sin_addr));
    this->acceptor_address.sin_port = htons(DEFAULT_INETSOCKET_PORT);
}
INETSocketAcceptor::INETSocketAcceptor(CommInterface * interface, INETSocketAddressInfo * info, int connections):max_connections(connections),AcceptorConn(interface){
    this->acceptor_address.sin_family = AF_INET;
    this->acceptor_address.sin_addr = info->GetAddress().sin_addr;
    this->acceptor_address.sin_port = info->GetAddress().sin_port;
}
INETSocketAcceptor::~INETSocketAcceptor() {
}

// Acceptor methods
HAMSTER_RETURN INETSocketAcceptor::open(void){
    
    // INET Socket creation
    this->acceptor_descriptor = socket(AF_INET , SOCK_STREAM , 0);
    if (this->acceptor_descriptor == -1)
    {
        // Error in creating socket
        logErrorMessage("Could not create INET Socket Acceptor. Error ", errno,
                "Unit ID = ", this->getCommInterface()->GetUnit()->getID().toString(),
                "\t Communication interface type = ",this->getCommInterface()->getType());
        return HAMSTER_RETURN::RETURN_NOK;
    }
    // Bind socket to address
    if(bind(this->acceptor_descriptor,(struct sockaddr *) &(this->acceptor_address), sizeof(this->acceptor_address)) < 0){
        //  Error in binding address
        logErrorMessage("Cloud not bind INET Socket to Adress. Error ", errno,
                "Unit ID = ", this->getCommInterface()->GetUnit()->getID().toString(),
                "\t Communication interface type = ",this->getCommInterface()->getType());
        return HAMSTER_RETURN::RETURN_NOK;
    }
    // Mark the socket as an acceptor
    if(listen(this->acceptor_descriptor,this->max_connections) < 0){
        // Error
        logErrorMessage("Cloud not bind INET Socket to Adress. Error ", errno,
                "Unit ID = ", this->getCommInterface()->GetUnit()->getID().toString(),
                "\t Communication interface type = ",this->getCommInterface()->getType());
        return HAMSTER_RETURN::RETURN_NOK;
    }
    // Load thread to listen
    try{
        this->setAcceptorThread(new std::thread(AcceptorConn::acceptorThread,this));
    }catch (const std::exception& e){
        logErrorMessage("Error in creating Acceptor Thread. Error message: ",e.what());
        return HAMSTER_RETURN::RETURN_NOK;
    }
    // All set!!
    logDebugMessage("INET Socket Acceptor loaded.\tCommunication interface type = ",this->getCommInterface()->getType()); 
    return AcceptorConn::open();
}
HAMSTER_RETURN INETSocketAcceptor::close(void){
    return AcceptorConn::close();
}

void INETSocketAcceptor::threadLoop(void){
    
    int c = sizeof(struct sockaddr_in);
    int client_handler;
    struct sockaddr_in client_address;
    
    // \todo Mudar o loop
    for(;;){ //ever
        client_handler = accept(this->acceptor_descriptor,(struct sockaddr *)&client_address, &c);
        if(client_handler < 0){
            // Error
            logErrorMessage("Cloud not accept new client in Acceptor. Error ", errno,
                "Unit ID = ", this->getCommInterface()->GetUnit()->getID().toString(),
                "\t Communication interface type = ",this->getCommInterface()->getType());
        }
        else{
            // Connection successfull
            //\todo Verificar mensagem de log aqui.
            logEventMessage("New connection, client port = ",client_address.sin_port);
            
            // Add new connection to interface
            INETSocketAddressInfo * info = new INETSocketAddressInfo(client_address);
            INETSocketHandler * handler = new INETSocketHandler(client_handler,static_cast<INETSocketInterface *>(this->getCommInterface()));
            HAMSTER_RETURN ret = this->addNewConnection(handler);
            if(ret != RETURN_OK){
                // Close connection
                /* The :: marks means the compiler has to look for the method in
                 * the global namespace. This way the method invocation do not
                 * conflicts with close() method of Acceptor class.
                 */
                ::close(client_handler);
            }else{
                // Connection successfully added to list. Wait for ID message
                this->waitIDMessage(static_cast<ConnectionHandler *>(handler),
                        static_cast<AddressInfo *>(info));
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
    }
}

} /* namespace socket */
} /* namespace interface */
} /* namespace comm */
} /* namespace hamster */