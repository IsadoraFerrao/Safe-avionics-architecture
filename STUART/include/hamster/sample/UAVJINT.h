/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UAVJINT.h
 * Author: Mariana
 *
 * Created on 28 de Setembro de 2018, 00:17
 */

#include "UAV.h"
#include "FlightData.h"
#include "CSVReader.h"

#ifndef UAVJINT_H
#define UAVJINT_H

namespace hamster{
namespace sample{    

class UAVJINT : public UAV{
public:
    UAVJINT(char * config_file_name);
    virtual ~UAVJINT();
    
    virtual void customInitialization(void);
    virtual void customExecution(void);
    virtual void customTermination(void);
    virtual void processMessage(utils::Uuid& peer_id, char * message);
    FlightData get_my_flight_data();
    void show_flightData_history(); //Declarei o cabeçalho aqui e implementei no .cc
    
private:
    FlightData my_flight_data;
    int flightData_ID; //Variável para contar o numero dos dados de voo, ou seja, controlar o tamanho do realloc
    FlightData *data_history; //Array para armazenar os dados do voo para analise pelo NCI (Foi alocado no construtor e desalocado no destrutor da classe)
    hamster::utils::CSVReader * flight_data_bag = NULL;
    utils::Uuid central_unit_id = this->centralUnitID();
};

} /* namespace sample */
} /* namespace hamster */

#endif /* UAVJINT_H */