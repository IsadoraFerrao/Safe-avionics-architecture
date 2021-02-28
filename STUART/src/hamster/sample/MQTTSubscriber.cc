/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MQTTSubscriber.cc
 * Author: Mariana
 * 
 * Created on 28 de Setembro de 2018, 21:53
 */

#include "MQTTSubscriber.h"
#include "MQTTClient.h"
#include "stdlib.h"
#include "HAMSTERLogger.h"
#include "HAMSTER.h"

#define server "10.70.1.234:1883"	
#define clientID "client"
#define user "client1"
#define senha "B%6nM&8,"
#define QoS 1
#define mainTopic "iod/station/"

void onDisconect(void *context, char *token){
	printf("Disconected.");
}
int onMessage(void *context, char *topicName, int topicLen, MQTTClient_message *message){
	//apenas teste
    logEventMessage(topicName," = ",(char*) message->payload);
    return 1;
}

MQTTSubscriber::MQTTSubscriber() {
}

MQTTSubscriber::MQTTSubscriber(const MQTTSubscriber& orig) {
}

MQTTSubscriber::~MQTTSubscriber() {
}

void MQTTSubscriber::load(){
	MQTTClient client;
	MQTTClient_deliveryToken token;		

	MQTTClient_connectOptions client_config = MQTTClient_connectOptions_initializer;
	
	//when false, allow simultaneous messages
	client_config.reliable = 0;
        client_config.keepAliveInterval = 20;
        client_config.cleansession = 1;
        client_config.username = user;
	client_config.password = senha;
        
        //connecting client
	MQTTClient_create(&client, server, clientID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
        //callbacks
	MQTTClient_setCallbacks(client, NULL, onDisconect, onMessage, NULL);
	MQTTClient_connect(client, &client_config);
	


	//verify if the client connected succesfully
	int rc = MQTTClient_isConnected(client);
	 
	if(rc == 1){
		printf("Client succesfully connected to the server.\n\n");
	}
	else{
		printf("Client did not connect to the server\n");
		exit(EXIT_FAILURE);
	}

	//subscribing to topics
	int sr1 = MQTTClient_subscribe(client, "uas/UAV1/#", QoS);
//        sr1 = MQTTClient_subscribe(client, "uas/UAV1/longitude", QoS);
	int sr2 = MQTTClient_subscribe(client, "uas/UAV2/#", QoS);
//	int sr3 = MQTTClient_subscribe(client, "uas/UAV3/#", QoS);
        
	//verify subscription
//	if(sr1 == 0 && sr2 == 0 && sr3 == 0)
//		printf("Subscribed to main topic  %s  for client %s using QoS %d\n\nPress Q <Enter> to quit.\n\n", mainTopic, clientID, QoS);

	char input='0';

	while(input != 'q' && input != 'Q'){
//		input = getchar();
                std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
	}

	MQTTClient_disconnect(client, 1000);
	MQTTClient_destroy(&client);
}
