/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FlightData.cc
 * Author: Mariana
 * 
 * Created on 27 de Setembro de 2018, 23:53
 */

#include "FlightData.h"
#include "HAMSTERLogger.h"
#include <iostream>
#include <cstring>
#include <math.h>  
#include <stdlib.h>

using namespace std;

namespace hamster{
namespace sample{

FlightData::FlightData() {
    
}

FlightData::~FlightData() {
    
}


void FlightData::printEssentialFlightData(){
    //std::cout << "Latitude: " << latitude_deg << "\t Longitude: ";
    printf("Latitude: %.7lf \t Longitude: ", latitude_deg);
    std::cout << longitude_deg << "\t Altitude:" << altitude_m << std::endl;
    std::cout << "Roll: " << roll_rad << "\t Pitch: " << pitch_rad;
    std::cout << "\t Yaw: " << yaw_rad << std::endl;
    
}

double FlightData::get_latitude(){
    return latitude_deg;
}

double FlightData::get_longitude(){
    return longitude_deg;
}

double FlightData::get_camera_priority(){
    return camera_priority;
}

double FlightData::get_health(){
    return health_camera;
}

int FlightData::get_hora(){
    return(hora);
}

int FlightData::get_minuto(){
    return(minuto);
}

int FlightData::get_qntd_bateria(){
    return(qntd_bateria);
}


int FlightData::publishData(MQTTClient handler, int qos, int retained, std::string root_topic){
//    MQTTClient_deliveryToken token;
//    int res, root_size = root_topic.size();
//    char message[30];
//    char topic[root_size + 30];
//
//    memcpy(topic,root_topic.c_str(),root_size);
//    
//    memset(message,0,30);
//    sprintf(message,"%ld",latitude_deg);
//    memcpy(&(topic[root_size]),"/latitude\0",10);
//    res = MQTTClient_publish(handler, topic, strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%ld",longitude_deg);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, topic, strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%d",altitude_m);
//    memcpy(&(topic[root_size]),"/altitude\0",10);
//    res = MQTTClient_publish(handler, topic, strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%f",velocity_north_mps);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, root_topic"/north_velocity", strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%f",velocity_east_mps);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, root_topic"/east_velocity", strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%f",velocity_down_mps);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, root_topic"/south_velocity", strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%d",roll_rad);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, root_topic"/roll", strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%d",pitch_rad);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, root_topic"/pitch", strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%d",yaw_rad);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, root_topic"/yaw", strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%d",gyro_x_rad);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, root_topic"/gyro_x", strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%d",gyro_y_rad);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, root_topic"/gyro_y", strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%d",gyro_z_rad);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, root_topic"/gyro_z", strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%d",accel_x_mpsps);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, root_topic"/accel_x", strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%d",accel_y_mpsps);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, root_topic"/accel_y", strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%d",accel_z_mpsps);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, root_topic"/accel_z", strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%d",mag_x_mG);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, root_topic"/mag_x", strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%d",mag_y_mG);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, root_topic"/mag_y", strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%d",mag_z_mG);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, root_topic"/mag_z", strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%d",indicated_air_speed_cmps);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, root_topic"/air_speed", strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%d",wind_direction_rad);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, root_topic"/wind_direction", strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
//    memset(message,0,30);
//    sprintf(message,"%d",wind_magnitude);
//    memcpy(&(topic[root_size]),"/longitude\0",11);
//    res = MQTTClient_publish(handler, root_topic"/wind_magnitude", strlen(message), message, qos, retained, &token);
//    if(res != MQTTCLIENT_SUCCESS){
//        logWarningMessage("Error in publishing in MQTT. Error code = ",res);
//        return res;
//    }
    return 0;
}

void FlightData::extractFromString(std::string line, std::string delimiter){
    int pos, pos_ant;
    int delimiter_size = delimiter.size();
    std::string field;
    
    // Hora
    pos = line.find(delimiter.c_str(),0,delimiter_size);
    field = line.substr(0,pos);
    sscanf(field.c_str(),"%d",&(hora));
    
    
    // Minuto
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%d",&(minuto));
    
    // Timestamp
    //pos = line.find(delimiter.c_str(),0,delimiter_size);
    //field = line.substr(0,pos);
    //sscanf(field.c_str(),"%ld",&(timestamp_us));
    // SVs --- Ignore it
    //pos_ant = pos + delimiter_size;
    //pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    
    // Latitude
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%lf",&(latitude_deg));
    
    // Longitude
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%lf",&(longitude_deg));
    
    // Altitude
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%d",&(altitude_m));
    // North velocity
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%f",&(velocity_north_mps));
    // East velocity
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%f",&(velocity_east_mps));
    // Down velocity
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%f",&(velocity_down_mps));
    // Roll
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%d",&(roll_rad));
    // Pitch
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%d",&(pitch_rad));
    // Yaw
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%d",&(yaw_rad));
    // X Gyro
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%d",&(gyro_x_rad));
    // Y Gyro
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%d",&(gyro_y_rad));
    // Z Gyro
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%d",&(gyro_z_rad));
    // X Acceleration
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%d",&(accel_x_mpsps));
    // Y Acceleration
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%d",&(accel_y_mpsps));
    // Z Acceleration
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%d",&(accel_z_mpsps));
    // X Magnetometer
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%d",&(mag_x_mG));
    // Y Magnetometer
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%d",&(mag_y_mG));
    // Z Magnetometer
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%d",&(mag_z_mG));
    // Air Speed
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%d",&(indicated_air_speed_cmps));
    // Wind direction
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%d",&(wind_direction_rad));
    // Wind magnitude
    pos_ant = pos + delimiter_size;
    pos = line.find(delimiter.c_str(),pos_ant,delimiter_size);
    field = line.substr(pos_ant,pos);
    sscanf(field.c_str(),"%d",&(wind_magnitude));
}

} /* namespace sample */
} /* namespace hamster */