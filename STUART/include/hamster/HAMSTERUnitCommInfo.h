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
 * \todo Fazer documentação
 */

#ifndef HAMSTERUNITCOMMINFO_H
#define HAMSTERUNITCOMMINFO_H

#include "HAMSTER.h"
#include "Unit.h"
#include "Uuid.h"
#include "tinyxml.h"
#include "tinystr.h"
#include "CryptographyHandler.h"
//#include "comm/cryptography/CryptographyAlgorithm.h"
//#include "comm/cryptography/ECCRelic.h"
//#include "comm/cryptography/ECCRelic/ECCRelicHandler.h"
#include <map>
#include <vector>

namespace hamster{
    
namespace comm{class HAMSTERPeer; namespace interface{class CommInterface; class ConnectionHandler;}}

class HAMSTERUnitCommInfo {
public:

//------------------------------------------------------------------------------
// Constructor / Destructor
//------------------------------------------------------------------------------
    HAMSTERUnitCommInfo(char * config_file_name, Unit * unit);
    virtual ~HAMSTERUnitCommInfo();
    
//------------------------------------------------------------------------------
// Communication Interfaces methods
//------------------------------------------------------------------------------
    void initializeInterfaces();
    void initializeCryptography();
    void loadInterfaceLoop();
    
//------------------------------------------------------------------------------
// Cryptography-related methods
//------------------------------------------------------------------------------
    /*! hamster::HAMSTERUnitCommInfo::addCryptographyAlgorithm(comm::cryptography::CriptographyAlgorithm * alg_implementation)
     *  \brief Add a new cryptography algorithm in the unit.
     */
    HAMSTER_RETURN addCriptographyAlgorithm(comm::cryptography::CryptographyAlgorithm * handler);
    /*! hamster::HAMSTERUnitCommInfo::handlerExists(utils::Uuid idcomm::cryptography::CRYPTOGRAPHY_ALGORITM alg)
     *  \briefs Indicates if a specific cryptogtraphy algorithm is available within the unit.
     */
    bool cryptographyAlgorithmAvailable(comm::cryptography::CRYPTOGRAPHY_ALGORITM alg);
    /*! hamster::HAMSTERUnitCommInfo::getCryptoAlforithm(comm::cryptography::CRYPTOGRAPHY_ALGORITM alg)
     * \brief Get the handler of this specific algorithm.
     * \todo Verify how it is going to be if more than one public key is used.
     */
//    comm::cryptography::CryptographyAlgorithm * getCryptoAlforithm(comm::cryptography::CRYPTOGRAPHY_ALGORITM alg){
//        return cryptography_algorithms;
//    }
//        comm::cryptography::KeyInfo* getMyKey() const {
//            return my_key;
//        }
//        
//        comm::cryptography::CryptographyHandler* getCryptHandler() const {
//            return crypt_handler;
//        }


    
//------------------------------------------------------------------------------
// Peer list methods
//------------------------------------------------------------------------------
    /*! hamster::HAMSTERUnitCommInfo::addPeer(comm::HAMSTERPeer * peer)
     *  \brief Add a new peer to the peer list.
     */
    HAMSTER_RETURN AddPeer(comm::HAMSTERPeer * peer);
    /*! hamster::HAMSTERUnitCommInfo::peerExists(utils::Uuid id)
     *  \briefs Indicate if a HAMSTERPeer is already on the PeerList.
     */
    bool peerExists(utils::Uuid id);
    /*! hamster::HAMSTERUnitCommInfo::peerFromHandler
     * \brief 
     */
    comm::HAMSTERPeer * getPeer(utils::Uuid id);
    
    bool areAllPeersAuthenticated();

    comm::HAMSTERPeer * getPeerFromHandler(comm::interface::ConnectionHandler * find);
//------------------------------------------------------------------------------
// Member Access Methods
//------------------------------------------------------------------------------
    bool isCentralized() const;
    comm::interface::CommInterface* getInterface(int i) const;
    bool formationKnown() const;
    uint8_t getNumInterfaces() const;
    comm::HAMSTERPeer* getCentralUnit() const;
        std::map<utils::Uuid, comm::HAMSTERPeer*> getPeerList() const {
            return peer_list;
        }

       
    
private:
   /*!< \brief Network interfaces of the unit. A unit can have many interfaces,
     * being inserted at different networks at the same time.
     */
    comm::interface::CommInterface ** communication_interfaces;
    uint8_t num_interfaces;
    
    /*!< \brief List of Criptography Algorithms available. */ 
    //std::vector<comm::cryptography::CriptographyAlgorithm *> cryptography_algorithms;

//    comm::cryptography::ECCRelicKeyInfo * my_key = new comm::cryptography::ECCRelicKeyInfo();    
//    comm::cryptography::CryptographyHandler * crypt_handler = new comm::cryptography::ECCRelicHandler(my_key);
//    

    
    /*!< \brief List of HAMSTER Peers of the unit. The Peers are put in a <map>
     *   structure using the unique ID (Uuid type) as key.
     */    
    std::map<utils::Uuid,comm::HAMSTERPeer *> peer_list;
    
    /*!< \brief Central unit in the system --- only used in a centralized scenario. */
    comm::HAMSTERPeer * central_unit = NULL;
    
    /*!< \brief States if the unit is operating in a centralized system. 
     * Initialized in unit construction based on configuration file. */
    bool centralized_system = false;
    /*!< \brief States if the unit knows its central unit or peers in advance.
     * Initialized in unit construction based on configuration file. */
    bool known_formation = false;
    
};

} /* namespace hamster */

#endif /* HAMSTERUNITCOMMINFO_H */

