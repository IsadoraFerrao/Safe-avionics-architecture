/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Station.h"


/* 
 * File:   StationJINT.h
 * Author: Mariana
 *
 * Created on 28 de Setembro de 2018, 14:27
 */

#include "Station.h"
#include "MQTTClient.h"
#include "FlightData.h"

#ifndef STATIONJINT_H
#define STATIONJINT_H

namespace hamster {
namespace sample {

class StationJINT : public Station {
public:
    StationJINT(char * config_file_name);
    virtual ~StationJINT();

    virtual void customInitialization(void);
    virtual void customExecution(void);
    virtual void customTermination(void);
    void processMessage(utils::Uuid& peer_id, char * message);
    
protected:    
    class UAVPeer{
    public:
        UAVPeer(){};
        virtual ~UAVPeer(){};
        utils::Uuid GetId() const {return id;}
        int GetCounter() const {return message_cnt;}
        void IncCounter(){message_cnt++;}
        void getDataFromString(std::string str){my_data.extractFromString(str,";");}
        void setMainTopic(std::string str){this->main_topic.assign(str);}
        void setData(std::string peer_id, std::string root){
            this->id.fromString(peer_id);
            this->main_topic.assign(root);
        }
        void publishData(MQTTClient handler, int qos, int retained){
            my_data.publishData(handler,qos,retained,this->main_topic);
        }
    private:
        utils::Uuid id;
        int message_cnt = 0;
        FlightData my_data;
        std::string main_topic;
    };
    
private:
        
    StationJINT::UAVPeer UAV1;//("5A7CB2A9-062A-AD03-68A5-634F6CDDB833","uas/UAV1/");
    StationJINT::UAVPeer UAV2;//("355FF919-1432-DA5A-72A9-B1B957AA4AA5","uas/UAV2/");
    StationJINT::UAVPeer UAV3;//("32755298-4E54-51C2-5501-759017E87C39","uas/UAV3/");
    
    MQTTClient mqtt_handler;
    
};

#endif /* STATIONJINT_H */

}/* namespace sample */
}/* namespace hamster */