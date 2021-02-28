/*
 * Copyright (C) 2018     Critical Embedded System Laboratory (LSEC)
 * 
 * This program is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * See the GNU Lesser General Public License for more details.
 * <http://www.gnu.org/licenses/>
 */

/* 
 * \file   HAMSTERUnitCommInfo.cc
 * \author: Mariana Rodrigues   rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#include "HAMSTERUnitCommInfo.h"
#include "HAMSTERPeer.h"
#include "INETSocketInterface.h"
#include "INETSocketAddressInfo.h"
//#include "ECCRelicHandler.h"

namespace hamster{

//------------------------------------------------------------------------------
// Constructor / Destructor
//------------------------------------------------------------------------------
HAMSTERUnitCommInfo::HAMSTERUnitCommInfo(char * config_file_name, Unit * my_unit){
    int integer_attribute, total_interfaces, interface_number;
    TiXmlDocument config_file;
    
    // Initialize lists
//    this->cryptography_algorithms = std::vector<comm::cryptography::CriptographyAlgorithm *>(comm::cryptography::CRYPTOGRAPHY_ALGORITM::UNKNOWN_CRYPTO,NULL);
    this->peer_list.clear();
    
    // Load configuration file
    if(config_file.LoadFile(config_file_name) != true){
//        utils::Uuid * temp_id = new utils::Uuid();
//        this->ID.fromString(temp_id->toString());
        logErrorMessage("Error in loading configuration file in unit. Error description:",
                config_file.ErrorDesc());
    }else{
        // Read configuration file
        // 1. Read options
        TiXmlElement * options = config_file.FirstChildElement("OPTIONS");
        options->QueryBoolAttribute("CENTRALIZED",&(this->centralized_system));
        options->QueryBoolAttribute("KNOWN_FORMATION",&(this->known_formation));
        // 2. Read unit
        TiXmlElement * unit_element = options->NextSiblingElement();    // 'Unit' element
        //  2.1 Number of interfaces
        unit_element->Attribute("Interfaces",&total_interfaces);
        this->num_interfaces = total_interfaces;
        this->communication_interfaces = new comm::interface::CommInterface * [total_interfaces];
        TiXmlElement * interfaces = unit_element->FirstChildElement("interfaces");
        TiXmlElement * interface = interfaces->FirstChildElement("int");
        for (int i = 1; i <= total_interfaces; i++) {
            // 2.4 Each interface
            interface->Attribute("Number",&interface_number);
            interface->Attribute("Type",&integer_attribute);
            comm::interface::COMM_INTERFACE_TYPE com_type;
            com_type << integer_attribute;
            interface->Attribute("TECH",&integer_attribute);
            switch(integer_attribute){
                case 1:     // Wifi
//                    communication_interfaces[i] = new WifiInterface();
                    break;
                case 2:     // Ethernet
//                    communication_interfaces[i] = EthernetInterface();
                    break;
                case 3:     // Socket
                    // Acceptor socket port
                    interface->Attribute("Port",&integer_attribute);
                    // Unit IP
                    char * interface_ip = (char *) interface->Attribute("IP");
                    comm::interface::inet_socket::INETSocketAddressInfo * acc_info = 
                            new comm::interface::inet_socket::INETSocketAddressInfo(interface_ip,integer_attribute);
                    interface->Attribute("Max_conn",&integer_attribute);
                    communication_interfaces[i-1] = new comm::interface::inet_socket::INETSocketInterface((uint8_t) interface_number,my_unit,this,com_type,acc_info,integer_attribute);
                    break;
            }
            interface = interface->NextSiblingElement("int");
        }
        // Cryptography Algorithms
        TiXmlElement * cryptography = unit_element->FirstChildElement("cryptography");
        TiXmlElement * alg = cryptography->FirstChildElement("alg");
        cryptography->Attribute("total",&integer_attribute);
//        while(alg != NULL){
//            alg->Attribute("Number",&integer_attribute);
//            switch(comm::cryptography::integer2CryptoAlgorithm(integer_attribute)){
//                case comm::cryptography::CRYPTOGRAPHY_ALGORITM::ECC_160:
//                {
//                    comm::cryptography::ECCRelicHandler * new_handler = new comm::cryptography::ECCRelicHandler();
//                    this->addCryptographyHandler(new_handler);
//                    break;
//                }
//                default:
//                    logErrorMessage("Cryptography Algorithm unknown");
//                    break;
//            }
//            alg = alg->NextSiblingElement("alg");
//        }

        //  2.2 Central unit
        unit_element->Attribute("UnitType",&integer_attribute);
        
        switch(hamster::integer2UnitType(integer_attribute)){
            case HAMSTER_UNIT_TYPE::ENTITY:     // HAMSTER Entity
                if(this->centralized_system == true){
                    // There is a HAMSTER SuperEntity
                    TiXmlElement * super_element = unit_element->NextSiblingElement();
                    // Get which interface the HAMSTER Super Entity connects to
                    super_element->Attribute("Interface",&integer_attribute);
                    utils::Uuid super_ID(super_element->Attribute("ID"));
                    comm::interface::CommInterface * super_interface = this->getInterface(integer_attribute);
                    comm::interface::AddressInfo * super_address;
                    switch(super_interface->getTechnology()){
                        case comm::interface::COMM_INTERFACE_TECH::WIFI:
//                          super_address = new WifiAddressInfo();
                            break;
                        case comm::interface::COMM_INTERFACE_TECH::ETHERNET:
                            break;
                        case comm::interface::COMM_INTERFACE_TECH::SOCKET:
                            super_element->Attribute("Port",&integer_attribute);
                            super_address = new comm::interface::inet_socket::INETSocketAddressInfo((char *) super_element->Attribute("IPAddress"),integer_attribute);
                            break;
                        default:
                            break;
                    }
                    this->central_unit = new comm::HAMSTERPeer(super_interface,super_address,super_ID);
                }
                break;
            case HAMSTER_UNIT_TYPE::CLUSTER:
            case HAMSTER_UNIT_TYPE::MODULE:
                // Get Entity data
                TiXmlElement * entity_element = unit_element->NextSiblingElement();
                // Get which interface the HAMSTER Super Entity connects to
                entity_element->Attribute("Interface",&integer_attribute);
                utils::Uuid entity_ID(entity_element->Attribute("ID"));
                comm::interface::CommInterface * entity_interface = this->getInterface(integer_attribute);
                comm::interface::AddressInfo * entity_address;
                switch(entity_interface->getTechnology()){
                    case comm::interface::COMM_INTERFACE_TECH::WIFI:
//                          super_address = new WifiAddressInfo();
                        break;
                    case comm::interface::COMM_INTERFACE_TECH::ETHERNET:
                        break;
                    case comm::interface::COMM_INTERFACE_TECH::SOCKET:
                        entity_element->Attribute("Port",&integer_attribute);
                        entity_address = new comm::interface::inet_socket::INETSocketAddressInfo((char *) entity_element->Attribute("IPAddress"),integer_attribute);
                        break;
                    default:
                        break;
                }
                this->central_unit = new comm::HAMSTERPeer(entity_interface,entity_address,entity_ID);
                break;
        }
    }
}

HAMSTERUnitCommInfo::~HAMSTERUnitCommInfo() {
}

//------------------------------------------------------------------------------
// Communication Interfaces methods
//------------------------------------------------------------------------------
void HAMSTERUnitCommInfo::initializeInterfaces(){
    for (int i = 0; i < this->num_interfaces; i++) {
        this->communication_interfaces[i]->platformInitialization();
    }
}
void HAMSTERUnitCommInfo::initializeCryptography(){

//    this->crypt_handler->getAlgorithm()->initializeKeys(this->my_key);
    
    // Iterate over the algorithms
//    for (std::pair<comm::cryptography::CRYPTOGRAPHY_ALGORITM,comm::cryptography::CryptographyHandler *> element : this->cryptography_handlers) {
//        element.second->initialize();
//    }

}
void HAMSTERUnitCommInfo::loadInterfaceLoop(){
    for (int i = 0; i < this->num_interfaces; i++) {
        this->communication_interfaces[i]->platformLoop();
    }
}
//------------------------------------------------------------------------------
// Cryptography-related methods
//------------------------------------------------------------------------------
HAMSTER_RETURN HAMSTERUnitCommInfo::addCriptographyAlgorithm(comm::cryptography::CryptographyAlgorithm * handler){
    return HAMSTER_RETURN::RETURN_OK;
}


bool HAMSTERUnitCommInfo::cryptographyAlgorithmAvailable(comm::cryptography::CRYPTOGRAPHY_ALGORITM alg){
    return false;
}

comm::cryptography::CryptographyAlgorithm * getCryptoAlforithm(comm::cryptography::CRYPTOGRAPHY_ALGORITM alg){
    return nullptr;
}

//------------------------------------------------------------------------------
// Peer list methods
//------------------------------------------------------------------------------
HAMSTER_RETURN HAMSTERUnitCommInfo::AddPeer(comm::HAMSTERPeer * peer){
    
    std::pair<utils::Uuid,comm::HAMSTERPeer *> toinsert(peer->GetID(),peer);
    std::pair<std::map<utils::Uuid,comm::HAMSTERPeer *>::iterator,bool> ret = this->peer_list.insert(toinsert);
    
//    ret = this->peer_list.insert(std::pair<utils::Uuid,comm::HAMSTERPeer *>(peer->GetID(),peer));
    if(ret.second == false){
//        logWarningMessage("Duplicated Peer (ID = ",peer->GetID().toString(),
//                ") inserted in peer list of Unit ID = ",this->getID().toString());
        return RETURN_NOK;
    }
    return RETURN_OK;
}
bool HAMSTERUnitCommInfo::peerExists(utils::Uuid id){
    std::map<utils::Uuid,comm::HAMSTERPeer *>::iterator it;
    it = this->peer_list.find(id);
    return (it != this->peer_list.end());
}
comm::HAMSTERPeer * HAMSTERUnitCommInfo::getPeer(utils::Uuid id){
    std::map<utils::Uuid,comm::HAMSTERPeer *>::iterator it;
    it = this->peer_list.find(id);
    if(it != this->peer_list.end()){
        return it->second;
    }
    return NULL;
}
bool HAMSTERUnitCommInfo::areAllPeersAuthenticated(){
    // Iterate over the Peer map using c++11 range based for loop
    for (std::pair<utils::Uuid, comm::HAMSTERPeer*> element : this->peer_list) {
        if(element.second->isAuthorized() == false){
            return false;
        }
    }
    return true;
}
comm::HAMSTERPeer * HAMSTERUnitCommInfo::getPeerFromHandler(comm::interface::ConnectionHandler * find){
    logDetailedMessage("getPeerFromHandler() pointer find = ",find);
    // Iterate over the map using c++11 range based for loop
    for (std::pair<utils::Uuid, comm::HAMSTERPeer*> element : this->peer_list) {
        if((element.second->getRecHandler() == find) || (element.second->getSenHandler() == find)){
            return element.second;
        }
    }
    return NULL;
}

//------------------------------------------------------------------------------
// Member Access Methods
//------------------------------------------------------------------------------
bool HAMSTERUnitCommInfo::isCentralized() const {
    return centralized_system;
}

comm::interface::CommInterface* HAMSTERUnitCommInfo::getInterface(int index) const {
    for(int i = 0; i < this->num_interfaces; i++){
        if(communication_interfaces[i]->getInterfaceNumber() == (uint8_t) index){
            return communication_interfaces[i];
        }
    }
    return NULL;
}

bool HAMSTERUnitCommInfo::formationKnown() const {
    return known_formation;
}

uint8_t HAMSTERUnitCommInfo::getNumInterfaces() const {
    return num_interfaces;
}
    
comm::HAMSTERPeer* HAMSTERUnitCommInfo::getCentralUnit() const {
    return central_unit;
}

    
} /* namespace hamster */
