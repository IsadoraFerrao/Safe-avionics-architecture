/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HAMSTERUserEntity.cc
 * Author: Mariana
 * 
 * Created on 9 de Fevereiro de 2018, 12:56
 */

#include "HAMSTERUserEntity.h"
#include "CommInterface.h"
#include "CentralCSU.h"
#include "CentralNCI.h"
#include "ConnectionHandler.h"
#include "Mission.h"
#include "NPManager.h"

namespace hamster{

HAMSTERUserEntity::HAMSTERUserEntity(char * config_file_name):HAMSTEREntity(config_file_name){
    
}

HAMSTERUserEntity::~HAMSTERUserEntity() {
}

void HAMSTERUserEntity::loadEntity(){
    this->initialize();
    this->execute();
    this->nodeTermination();        
}

HAMSTER_RETURN HAMSTERUserEntity::sendMessage(utils::Uuid& peer_id, char* message){
//    logEventMessage("User-defined message \"",message,"\" sent.");
    comm::HAMSTERPeer * peer = this->getCommunicationInfo()->getPeer(peer_id);
    comm::messaging::HAMSTERMessage * msg = 
            new comm::messaging::HAMSTERMessage(comm::messaging::HAMSTER_MESSAGE_DIRECTION::EXTERNAL,
            comm::messaging::HAMSTER_MESSAGE_CODE::HAMSTER_USER_MSGS);
    msg->copyToPayload(message,strlen(message));
    msg->setRecipient(peer);
    this->getCommunicationBbroker()->parseMessage(msg);
    return HAMSTER_RETURN::RETURN_OK;
}

HAMSTER_RETURN HAMSTERUserEntity::requestPeerConnection(utils::Uuid& peer_id){
    
    HAMSTER_RETURN ret = HAMSTER_RETURN::RETURN_NOK;

    // 0. Try to find peer in list --- used in tests afterwards
    comm::HAMSTERPeer * peer = this->getCommunicationInfo()->getPeer(peer_id);
    
    // 2. Is the system centralized?
    if(this->getCommunicationInfo()->isCentralized() == true){
        // 2.1 Is peer in list?
        if(peer != NULL){
            // 2.1.1 Is Peer connected?
            if(peer->isConnected() == true){
                // 2.1.1.1 Is peer authorized?
                if(peer->isAuthorized() == true){
                    return HAMSTER_RETURN::RETURN_OK;
                }
                peer->disconnect();
            }
            peer->resetPeerData();
        }
        logDebugMessage("Request connection to peer to central unit.");
        // \todo implementação
        return static_cast<sphere::csu::CentralCSU *>(this->getSPHEREPlatform()->getCSUModule())->requestConnectionToCentralUnit(peer_id);
    }
    else{
        // 2.2 Is formation knwon?
        if(this->getCommunicationInfo()->formationKnown() == true){
            // 2.2.a Formation known
            // 2.2.a.1 Is peer in list?
            if(peer == NULL){
                // 2.2.a.1.a --- Peer not in list in known formation --- Error
                logErrorMessage("Requested ID not in list in known formation");
                return HAMSTER_RETURN::UNKNOWN_PEER;
            }
        }
        /* 2.2.b Formation unknwon but have peer ID to connect or
         * 2.2.a.1.b --- Formation known and peer in list
         */
        // 2.3 Is peer in list?
        if(peer != NULL){
            // 2.3.1 Is the peer connected?
            if(peer->isConnected() == true){
                if(peer->isAuthorized() == true){
                    // Peer already connected and authorized
                    logEventMessage("Authorization Request to Peer ID ", 
                            peer->GetID()," granted. Peer already connected.");
                    return RETURN_OK;
                }else{
                    // Request authentication in peer
                    logDebugMessage("Requested peer connected but not authorized. Attempting authorization...");
                    // \todo Implementar rotina. 
                    //return this->RequestAuthorizationToPeer(peer);
                    return RETURN_NOK;
                }
            }
            // 2.3.2 Peer not connected
            peer->resetPeerData();
        }
        // 2.3.b Peer not in list or Peer in list but not connected
        logDebugMessage("Requesting connection to peer ID ",peer->GetID());
        // \todo Implementação
        //ret = this->RequestConnectionToPeer(peer_id);
        if(ret!= RETURN_OK){
            return ret;
        }
        // Connection to peer successful
        // peer = this->getCommunicationInfo()->getPeer(peer_id);
        //\todo Implementação
        //ret = this->RequestAuthorizationToPeer(peer);
        if(ret != RETURN_OK){
            //\todo Neste caso, disconecta?
        }
        return ret;
    }
}


utils::Uuid HAMSTERUserEntity::getMyID() const {
    return this->getID();
}

void HAMSTERUserEntity::stopExecution(){
    this->terminate = true;
}
bool HAMSTERUserEntity::terminateExecution(){
    return this->terminate;
}
void HAMSTERUserEntity::setMission(navigation_phases::Mission entity_mission){
    // \todo A mensagem passa a vigorar quando o trigger passar a ser um serviço
    comm::messaging::HAMSTERMessage * msg = new comm::messaging::HAMSTERMessage(
            comm::messaging::HAMSTER_MESSAGE_DIRECTION::INTERNAL,
            comm::messaging::HAMSTER_MESSAGE_CODE::MISSION_CONFIGURATION);
    msg->pushMessageField(&entity_mission);
    this->putMessageInBroker(msg);
    static_cast<navigation_phases::NPManager *>(this->getNPPlatform())->setMission(entity_mission);
}

} /* namespace hamster*/