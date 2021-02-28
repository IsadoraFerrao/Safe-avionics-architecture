/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newmain.cpp
 * Author: Mariana
 *
 * Created on 21 de Novembro de 2017, 14:37
 */


#include <cstdlib>
#include <iostream>
#include <iterator>
#include  <iomanip>

#include "HAMSTER.h"
//#include "Uuid.h"
#include "UAV.h"
#include "Station.h"
//#include "SensorUnit.h"
//#include "Autopilot.h"
//#include "MissionPlanner.h"
//#include "NavigationPhase.h"
//#include "RGBCamera.h"
//#include "MultispectralCamera.h"
//#include "Mission.h"
//#include "relic.h"
//#include "CRYPTOGRAPHY_ALGORITMS.h"
#include "UAVJINT.h"
#include "StationJINT.h"
//#include "MQTTSubscriber.h"
//#include "Registerer.h"
//#include "FarashRegistraton.h"


using namespace std;
//using namespace hamster;
/*
 * 
 */


int main(int argc, char** argv) {
    
    char file[20];
    register_cipher(&aes_desc);
    register_hash(&sha256_desc);
    
#if defined(UAV1_MAIN) || defined (UAV2_MAIN) || defined (UAV3_MAIN)
    
#ifdef UAV1_MAIN
    strcpy(file,"UAV_1.xml");
#endif
#ifdef UAV2_MAIN
    strcpy(file,"UAV_2.xml");
#endif
#ifdef UAV3_MAIN
    strcpy(file,"UAV_3.xml");
#endif
    hamster::sample::UAVJINT * my_uav = new hamster::sample::UAVJINT(file);
    std::cout << "Entity:" << std::endl << my_uav << std::endl;
   // printf("CAMERAAAAAAAAAA: %lf\n\n", my_uav->get_my_flight_data().get_camera_priority());
    
    my_uav->loadEntity();
#endif
    
#ifdef STATION_MAIN
    strcpy(file,"Station.xml");  // strcpy (string_destino,string_origem);
    hamster::sample::StationJINT super(file);
    std::cout << "Super:" << std::endl<<super << std::endl;
    super.load();
    std::cout << "Station initialized. "<< std::endl;
#endif
    
#ifdef MISSION_PLANNER
//    strcpy(file,"MissionPlanner.xml");
//    hamster::sample::MissionPlanner station(file);
//    std::cout << "Mission Planner:"  << station.getID() << std::endl;
//    station.initialize();
#endif

#ifdef AUTOPILOT
    strcpy(file,"Autopilot.xml");
    hamster::sample::Autopilot autopilot(file);
    autopilot.load();
#endif
    
#ifdef RGB_CAMERA 
    strcpy(file,"RGB.xml");
    hamster::sample::RGBCamera rgb_camera(file);
    rgb_camera.load();
#endif
    
#ifdef MULTISPECTRAL_CAMERA
    strcpy(file,"Multispectral.xml");
    hamster::sample::MultispectralCamera multi_camera(file);
    multi_camera.load();
#endif
    
#ifdef SENSOR_UNIT
    strcpy(file,"SensorUnit.xml");
    hamster::sample::SensorUnit sensors(file);
    sensors.load();
#endif
    
#ifdef SUBSCRIBER_MAIN
    MQTTSubscriber sub;
    sub.load();
#endif
   
    //my_uav->show_flightData_history(); //Criei esta função para imprimir os dados armazenados
    return 0;
}

