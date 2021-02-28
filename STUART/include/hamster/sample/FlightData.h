/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FlightData.h
 * Author: Mariana
 *
 * Created on 27 de Setembro de 2018, 23:53
 */

        
#ifndef FLIGHTDATA_H
#define FLIGHTDATA_H

#include <string>
#include "MQTTClient.h"

namespace hamster{
namespace sample{

class FlightData {
public:
    FlightData(); 
    virtual ~FlightData();
    
    void extractFromString(std::string line, std::string delimiter);
    void printEssentialFlightData();
    double get_latitude();
    double get_longitude();
    double get_camera_priority();
    double get_health();
    int get_hora();
    int get_minuto();
    int get_qntd_bateria();
    int publishData(MQTTClient handler, int qos, int retained, std::string root_topic);
    
private:
    int hora;
    int minuto;
    long int timestamp_us;
    double latitude_deg;
    double longitude_deg;
    int altitude_m;
    int camera = 0;
    double camera_priority = 1;
    double health_camera = 0;
    double velocity_north_mps;
    double velocity_east_mps;
    double velocity_down_mps;
    int roll_rad;
    int pitch_rad;
    int yaw_rad;
    int gyro_x_rad;
    int gyro_y_rad;
    int gyro_z_rad;
    int accel_x_mpsps;
    int accel_y_mpsps;
    int accel_z_mpsps;
    int mag_x_mG;
    int mag_y_mG;
    int mag_z_mG;
    int indicated_air_speed_cmps;
    int wind_direction_rad;
    int wind_magnitude;
    int qntd_bateria = 100;
};

} /* namespace sample */
} /* namespace hamster */

#endif /* FLIGHTDATA_H */

