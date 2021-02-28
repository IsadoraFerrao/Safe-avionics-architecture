/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Listener.h
 * Author: Mariana
 *
 * Created on 15 de Setembro de 2018, 16:36
 */

#ifndef LISTENER_H
#define LISTENER_H

/*!
 * \class Listener Listener.h "Listener.h"
 * \brief A class to passively initialize a network connection.
 * \detail The class Listener initializes a point in the network interface that
 *  accepts messages from other peers, in a connectionless scheme of communication.
 *  When receiving a message, the Listener forward it to the ConnectionlessDispatcher,
 *  which will handle the response for each one.
 */

class Listener {
public:
    Listener();
    Listener(const Listener& orig);
    virtual ~Listener();
private:

};

#endif /* LISTENER_H */

