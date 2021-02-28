/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HAMSTERUserEntity.h
 * Author: Mariana
 *
 * Created on 9 de Fevereiro de 2018, 12:56
 */

#ifndef HAMSTERUSERENTITY_H
#define HAMSTERUSERENTITY_H

#include "HAMSTEREntity.h"
#include "Mission.h"

namespace hamster{

/* \todo Built on entity for prototype. When building modules, put whatever is 
 * common in a userUnit class */
class HAMSTERUserEntity : public HAMSTEREntity {
public:
    HAMSTERUserEntity(char * config_file_name);
    virtual ~HAMSTERUserEntity();

    void loadEntity();

//------------------------------------------------------------------------------
// Semantic search on modules and entities
//------------------------------------------------------------------------------
//    List<ModuleInfo> requestInfoOnModule();     //\todo functional_ID
//    List<EntityFuncInfo> requestInfoOnPeer();       //\todo functional_ID
//------------------------------------------------------------------------------
// Connection to modules and entities
//------------------------------------------------------------------------------
//    HAMSTER_RETURN requestLocalConnection();  //\todo Connect to Module
    HAMSTER_RETURN requestPeerConnection(utils::Uuid& id);
//------------------------------------------------------------------------------
// Message handling
//------------------------------------------------------------------------------
    HAMSTER_RETURN sendMessage(utils::Uuid& peer_id, char * message);

//------------------------------------------------------------------------------
// Service exchange
//------------------------------------------------------------------------------
//    HAMSTER_RETURN registerService(service);
//    List<service> browseServices(service_desc);
//    HAMSTER_RETURN requestService(service_desc);
//-----------------------------------------------------------------------------
// User methods to be overloaded by application
//-----------------------------------------------------------------------------
    virtual void customInitialization(void) = 0;
    virtual void customExecution(void) = 0;
    virtual void customTermination(void) = 0;
    void receberDados(sample::FlightData dados){
         this->getSPHEREPlatform()->receberDados(dados);
    }

    void receberDadosSaude(sample::FlightData dadosSaude){ 
         this->getSPHEREPlatform()->receberDadosSaude(dadosSaude);
    }
        
    void get_Security(sample::FlightData *data_history, int flightData_ID){
        this->getSPHEREPlatform()->get_Security(data_history, flightData_ID);
    }   
        

//------------------------------------------------------------------------------
// HAMSTEREntity attributes made public
//------------------------------------------------------------------------------    
    utils::Uuid getMyID() const;
    
    void setMission(navigation_phases::Mission entity_mission);
    
inline friend std::ostream& operator<<(std::ostream& stream,HAMSTERUserEntity * node){
    return node->printNode(stream);
}

inline friend std::ostream& operator<<(std::ostream& stream,HAMSTERUserEntity& node){
    return node.printNode(stream);
}

protected:
    void stopExecution();
    bool terminateExecution();
    inline utils::Uuid centralUnitID(){
        return this->getCentralUnit()->GetID();
    }
    
private:
//    std::ostream& printNode(std::ostream& stream) const;
};

} /* namespace hamster */

#endif /* HAMSTERUSERENTITY_H */

