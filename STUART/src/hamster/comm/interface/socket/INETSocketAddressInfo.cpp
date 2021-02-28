/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   INETSocketAddressInfo.cpp
 * Author: Mariana
 * 
 * Created on 9 de Janeiro de 2018, 13:17
 */

#include "INETSocketAddressInfo.h"
#include <cstring>

namespace hamster{
namespace comm{
namespace interface{
namespace inet_socket{

INETSocketAddressInfo::INETSocketAddressInfo():prot(INETSocketProtocol::TCP) {
    this->socket_address.sin_family = AF_INET;
    inet_aton(DEFAULT_INETSOCKET_ADRRESS, &(this->socket_address.sin_addr));
    this->socket_address.sin_port = htons(DEFAULT_INETSOCKET_PORT);
}
INETSocketAddressInfo::INETSocketAddressInfo(char * address, int port, INETSocketProtocol type):prot(type) {
    this->socket_address.sin_family = AF_INET;
    inet_aton(address, &(this->socket_address.sin_addr));
    this->socket_address.sin_port = htons(port);
}
INETSocketAddressInfo::INETSocketAddressInfo(char * address, int port):prot(INETSocketProtocol::TCP) {
    this->socket_address.sin_family = AF_INET;
    inet_aton(address, &(this->socket_address.sin_addr));
    this->socket_address.sin_port = htons(port);
}
INETSocketAddressInfo::INETSocketAddressInfo(struct sockaddr_in add){
    this->socket_address.sin_family = AF_INET;
    this->socket_address.sin_addr = add.sin_addr;
    this->socket_address.sin_port = add.sin_port;
}
INETSocketAddressInfo::~INETSocketAddressInfo() {
}
struct sockaddr_in INETSocketAddressInfo::GetAddress() const {
    return this->socket_address;
}
INETSocketProtocol INETSocketAddressInfo::GetProt() const {
    return this->prot;
}

int INETSocketAddressInfo::pushInPayload(char ** buffer){
    char * address = inet_ntoa(this->socket_address.sin_addr);
    int port = (int) ntohs(socket_address.sin_port);
    uint8_t size = strlen(address);
    (*buffer) = new char[size+5];
    (*buffer)[0] = size;
    strncpy(&((*buffer)[1]),address,size);
    sprintf((char *) &((*buffer)[size+1]),"%04x",port);
    return (size+5);
}

int INETSocketAddressInfo::pullFromPayload(char * buffer){
    uint8_t size;
    char * address;
    uint16_t port;

    // Read string address
    sscanf(buffer,"%c",&size);
    address = new char[size];
    strncpy(address,&(buffer[1]),size);
    address[size] = '\0';
    // Read port
    sscanf(&(buffer[size+1]),"%4x",&port);
    logVerboseMessage("Socket Address recovered from message. IP = ",address,
                      ", port = ",port);
    // Initialize fields
    inet_aton(address, &(this->socket_address.sin_addr));
    this->socket_address.sin_port = htons(port);
    return (size+1+sizeof(uint16_t));
}

} /* namespace inet_socket */
} /* namespace interface */
} /* namespace comm */
} /* namespace hamster */
