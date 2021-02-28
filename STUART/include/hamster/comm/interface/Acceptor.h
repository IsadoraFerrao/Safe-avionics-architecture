/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*! 
 * \file   Acceptor.h
 * \author rodrigues.mariana@gmail.com
 * \date 2018
 * \copyright
 */

#ifndef ACCEPTOR_H
#define ACCEPTOR_H

/*!
 * \class Acceptor Acceptor.h "Acceptor.h"
 * \brief A class to passively initialize a network connection.
 * \detail The class Acceptor initializes a point in the network interface that
 *  accepts connection from other peers. This construction in HAMSTER is based
 *  on the Acceptor-Connector design pattern for connected-oriented software.
 *  For every accepted connection, it will be a created ConnectionHandler
 *  responsible for operating the connection.
 */
class Acceptor {
public:
    Acceptor();
    Acceptor(const Acceptor& orig);
    virtual ~Acceptor();
private:

};

#endif /* ACCEPTOR_H */

