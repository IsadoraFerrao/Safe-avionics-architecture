/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UAVJINT.cc
 * Author: Mariana
 * 
 * Created on 28 de Setembro de 2018, 00:17
 */

#include "UAVJINT.h"
#include "CSVReader.h"
#include <typeinfo>
#include <stdio.h>


namespace hamster{
namespace sample{  
    
int current_line = 0;

UAVJINT::UAVJINT(char * config_file_name):UAV(config_file_name) {
    flightData_ID = 1; //Inicializa com 1 posição para os dados e realoca a cada iteração do voo.
    data_history = (FlightData *)malloc(flightData_ID*sizeof(FlightData));
}

UAVJINT::~UAVJINT() {
    free(data_history);
}

FlightData UAVJINT::get_my_flight_data(){
    return this->my_flight_data;
}

void UAVJINT::customInitialization(void){
    logVerboseMessage("entered customInitialization()");
    // Read data from CSV file
    char file_name[20];
#ifdef UAV1_MAIN
    strcpy(file_name,"FlightData1.csv");
#elif defined UAV2_MAIN
    strcpy(file_name,"FlightData2.csv");
#elif defined UAV3_MAIN
    strcpy(file_name,"FlightData3.csv");
#endif
    this->flight_data_bag = new utils::CSVReader(file_name,";");
    if(this->flight_data_bag != NULL){
        this->flight_data_bag->readData();
    }
    logEventMessage("UAV Initialized.");
    logVerboseMessage("leave customInitialization()");
}

void UAVJINT::customExecution(void){
        logVerboseMessage("entered customExecution()");
        char * message;

        std::string current_flight_data;
        
//        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS*3));;
        switch(this->getState()){
            case UAV_STATE::INITIAL:
                this->setState(UAV_STATE::EXECUTING);
                std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
            break;
        case UAV_STATE::CONNECTING:
//            std::cout << "UAV State = CONNECTING." << std::endl;
//            switch(this->requestPeerConnection(peer_id)){
//                case HAMSTER_RETURN::RETURN_OK:
//                    std::cout << "Connection request accepted." << std::endl;
//                    this->setState(UAV_STATE::EXECUTING);
//                    break;
//                default:
//                    std::cout << "Could not connect to peer." << std::endl;
//                    break;
//            }
            break;
        case UAV_STATE::EXECUTING:
            logEventMessage("UAV is now sending telemetry data.");
            /* Get a line from file and:
             * 1) Print in log
             * 2) Send to central unit
             */
            current_flight_data.assign(this->flight_data_bag->getData(current_line));
            this->my_flight_data.extractFromString(current_flight_data,";"); //Aqui são populados os dados obtidos do arquivo csv, mas um a um, ou seja, ainda não está sendo salvo.
            this->my_flight_data.printEssentialFlightData();
            
            //Armazenando os dados do voo em um array
            data_history[flightData_ID-1] = this->my_flight_data;
            flightData_ID += 1;
            data_history = (FlightData*)realloc(data_history, flightData_ID*sizeof(FlightData));
            
            //Enviando pra SMU.H
           
            this->receberDadosSaude(my_flight_data);
            
            //Enviando pra CSU.H
            this->receberDados(my_flight_data);
            this->get_Security(data_history, flightData_ID-1); //Envia os dados do historico de voo para a CSV (Array de FlightData, ou seja, tem acesso a todos os parametros do voo)
            
            
            
            message = new char[current_flight_data.size() + sizeof(int)];
            
            //printf("---------------------------IMPRIMINDO CSV LINHA: %d\n\n", current_line);
            
            sprintf(message,"%d",(current_line+1));
            strncpy(&(message[sizeof(int)]),current_flight_data.c_str(),current_flight_data.size());
            this->sendMessage(central_unit_id, message);
            delete message;
            current_line++;
            if(current_line == 15){
                this->setState(UAV_STATE::FINALIZING);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS));
            break;
        case UAV_STATE::WAIT_RESPONSE:
            // Do nothing
            break;
        case UAV_STATE::FINALIZING:
            logEventMessage("UAV is now terminating.");
            this->stopExecution();
            break;
    }
        logVerboseMessage("Leave customExecution()");
    };
    void UAVJINT::customTermination(void){
        logVerboseMessage("Entered customTermination()");
        logVerboseMessage("Leave customTermination()");
    };
    void UAVJINT::processMessage(utils::Uuid& peer_id, char * message){
        
    };
    
    //Método para mostrar o histórico de voo
    void UAVJINT::show_flightData_history(){
        std::cout << "-------------------# APRESENTANDO O HISTÓRICO DE VOO #-----------------------" << std::endl;
        for(int i=0; i<this->flightData_ID-1; i++){
            std::cout << "Data ID (" << i << "): " << std::endl;
            this->data_history[i].printEssentialFlightData();
           
        }
    };

} /* namespace sample */
} /* namespace hamster */