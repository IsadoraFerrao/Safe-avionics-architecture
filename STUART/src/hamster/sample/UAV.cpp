/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UAV.cpp
 * Author: Mariana
 * 
 * Created on 25 de Dezembro de 2017, 14:42
 */

#include "UAV.h"
#include "HAMSTEREntity.h"
#include <cstring>

   // Phase triggers
    bool initializationTrigger(void);
    bool cruisingTrigger(void);
    bool executionTrigger(void);
    bool returnTrigger(void);
    bool finalizationTrigger(void);


namespace hamster{

#ifdef UAV1_MAIN
utils::Uuid peer_id("355FF919-1432-DA5A-72A9-B1B957AA4AA5");
#endif
#ifdef UAV2_MAIN
utils::Uuid peer_id("5A7CB2A9-062A-AD03-68A5-634F6CDDB833");
#endif
#if !defined UAV1_MAIN && !defined UAV2_MAIN
utils::Uuid peer_id;
#endif


namespace sample{

// Constructor / Destructor
UAV::UAV(char * config_file_name) : HAMSTERUserEntity(config_file_name){
    
}
UAV::~UAV() {
}
void UAV::customInitialization(void) {
    logVerboseMessage("UAV Custom Initialization.");
/*    hamster::navigation_phases::Mission my_mission;
    my_mission.setNumberOfPhases(5);
    navigation_phases::NavigationPhase phase;
    navigation_phases::PhaseBehaviour all_on(0,hamster::HAMSTER_COMPONENT_STATE::COMPONENT_ON,hamster::HAMSTER_COMPONENT_STATE::COMPONENT_ON);
    navigation_phases::PhaseBehaviour mission_off(0,hamster::HAMSTER_COMPONENT_STATE::COMPONENT_ON,hamster::HAMSTER_COMPONENT_STATE::COMPONENT_OFF);
    char phase_description[50];
    // Phase 1
    // Initialization --- All modules are active
    all_on.setNumber(1);
    phase.setComponentBehaviour(all_on);
    strncpy(phase_description,"Initialization",14);
    phase_description[14] = '\0';
//    phase.setDescription(phase_description);
    phase.setTriggerToNextPhase(&initializationTrigger);
    my_mission.addPhase(phase);
    logVerboseMessage("Phase 1 added.");
    // Phase 2
    // Cruising --- Only main modules are active
    mission_off.setNumber(2);
    phase.setComponentBehaviour(mission_off);
    strncpy(phase_description,"Cruising",8);
    phase_description[8] = '\0';
//    phase.setDescription(phase_description);
    phase.setTriggerToNextPhase(&cruisingTrigger);
    my_mission.addPhase(phase);
    logVerboseMessage("Phase 2 added.");
    // Phase 3
    // Mission execution --- All modules are active
    all_on.setNumber(3);
    phase.setComponentBehaviour(all_on);
    strncpy(phase_description,"Mission execution",17);
    phase_description[17] = '\0';
//    phase.setDescription(phase_description);
    phase.setTriggerToNextPhase(&executionTrigger);
    my_mission.addPhase(phase);
    logVerboseMessage("Phase 3 added.");
    // Phase 4
    // Return to base --- Only main modules are active
    mission_off.setNumber(4);
    phase.setComponentBehaviour(mission_off);
    strncpy(phase_description,"Return to base",14);
    phase_description[14] = '\0';
//    phase.setDescription(phase_description);
    phase.setTriggerToNextPhase(&returnTrigger);
    my_mission.addPhase(phase);
    logVerboseMessage("Phase 4 added.");
    // Phase 5
    // Finalization --- All modules are active
    all_on.setNumber(5);
    phase.setComponentBehaviour(all_on);
    strncpy(phase_description,"Finalization",12);
    phase_description[12] = '\0';
//    phase.setDescription(phase_description);
    phase.setTriggerToNextPhase(&finalizationTrigger);
    my_mission.addPhase(phase);
    logVerboseMessage("Phase 5 added.");
    // Set mission
    this->setMission(my_mission);
    logVerboseMessage("Mission set.");*/
}
void UAV::customExecution(void){
    std::cout << "UAV custom execution" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS*3));    
    switch(this->my_state){
        case UAV_STATE::INITIAL:
#ifdef UAV2_MAIN
            this->my_state = UAV_STATE::CONNECTING;
#else
            this->my_state = UAV_STATE::EXECUTING;
#endif
            break;
        case UAV_STATE::CONNECTING:
            std::cout << "UAV State = CONNECTING." << std::endl;
            switch(this->requestPeerConnection(peer_id)){
                case HAMSTER_RETURN::RETURN_OK:
                    std::cout << "Connection request accepted." << std::endl;
                    this->my_state = UAV_STATE::EXECUTING;
                    break;
                default:
                    std::cout << "Could not connect to peer." << std::endl;
                    break;
            }
            break;
        case UAV_STATE::EXECUTING:
            std::cout << "UAV State = EXECUTING." << std::endl;
#ifdef UAV2_MAIN
            this->sendMessage(peer_id,(char *) "Hello, my friend!");
            this->my_state = UAV_STATE::WAIT_RESPONSE;
#endif
            break;
        case UAV_STATE::WAIT_RESPONSE:
            // Do nothing
            break;
        case UAV_STATE::FINALIZING:
            std::cout << "That's all, folks!" << std::endl;
            this->stopExecution();
            break;
    }
}

void UAV::customTermination(void){
    std::cout << "UAV custom termination." << std::endl;
}

void UAV::processMessage(utils::Uuid& peer_id, char * message){
    if(strcmp(message,"Hello, my friend!") == 0){
        this->sendMessage(peer_id,(char *) "Hello back!");
    }
    if(strcmp(message,"Hello back!") == 0){
        std::cout << "Message \"Hello back!\" received." << std::endl;
        this->my_state = UAV_STATE::FINALIZING;
    }
}



} /* namespace sample */  
} /* namespace hamster */

   // Phase triggers
    bool initializationTrigger(void){
        // Time trigger;
        static int times = 5;
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
        times--;
        return (times == 0);
    }
    bool cruisingTrigger(void){
        // Time trigger;
        static int times = 10;
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
        times--;
        return (times == 0);
    }
    bool executionTrigger(void){
        srand(time(NULL));
        int random = rand()%10;
        return (random > 5);
    }
    bool returnTrigger(void){
        // Time trigger;
        static int times = 10;
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
        times--;
        return (times == 0);
    }
    bool finalizationTrigger(void){
        srand(time(NULL));
        int random = rand()%10;
        return (random > 8);
    }