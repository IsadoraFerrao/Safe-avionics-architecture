/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StationJINT.cc
 * Author: Mariana
 * 
 * Created on 28 de Setembro de 2018, 14:27
 */

#include "StationJINT.h"

// MQTT Definitions
#define server "10.70.1.234:1883"	
#define clientID "Station"
#define user "station"
#define senha "Z!2xC#4v"
#define QoS 1
#define mainTopic "UAS"

namespace hamster{
namespace sample{  


StationJINT::StationJINT(char * config_file_name):Station(config_file_name) {
    UAV1.setData("5A7CB2A9-062A-AD03-68A5-634F6CDDB833","uas/UAV1");
    UAV2.setData("355FF919-1432-DA5A-72A9-B1B957AA4AA5","uas/UAV2");
    UAV3.setData("32755298-4E54-51C2-5501-759017E87C39","uas/UAV3");
    
}
StationJINT::~StationJINT() {
}

void StationJINT::customInitialization(void) {
    logEventMessage("Station is initializing.");
    
    /*
    MQTTClient_connectOptions client_config = MQTTClient_connectOptions_initializer;

    // Configure connection
    client_config.reliable = 0;    //when false, allow simultaneous messages
    client_config.username = user;
    client_config.password = senha;

    // Connect to MQTT server
    MQTTClient_create(&(this->mqtt_handler), server, clientID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    MQTTClient_connect(this->mqtt_handler, &client_config);

    // Verify connection
    int rc = MQTTClient_isConnected(this->mqtt_handler);
 
    if(rc == 1){
        logEventMessage("Station successfully connected to the server.");
    }else{
        logErrorMessage("Station could not connect to MQTT broker. Error code = ",rc);
        this->terminate = true;
    }*/
}

void StationJINT::customExecution(void) {
    
}

void StationJINT::customTermination(void) {/*
    MQTTClient_disconnect(this->mqtt_handler, 1000);
    MQTTClient_destroy(&(this->mqtt_handler));*/
}

void StationJINT::processMessage(utils::Uuid& peer_id, char * message) {
    int counter;
    sscanf(message,"%d",&counter);
    std::string payload;
    payload.assign(&(message[sizeof(int)]));
            
    StationJINT::UAVPeer * peer;
    if(peer_id == this->UAV1.GetId()){
        peer = &UAV1;
    }
    else if(peer_id == this->UAV2.GetId()){
        peer = &UAV2;
        
    }else if(peer_id == this->UAV3.GetId()){
        peer = &UAV3;        
    }else{
        logDebugMessage("Message received from unknown peer.");
        return;
    }
    peer->IncCounter();
    if(counter != peer->GetCounter()){
        logWarningMessage("Message lost or received in wrong order.");
    }
    peer->getDataFromString(payload);
    peer->publishData(this->mqtt_handler,QoS,1);
}

} /* namespace sample */
} /* namespace hamster */