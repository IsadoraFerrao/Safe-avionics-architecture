/*
 * Copyright (C) 2017     Critical Embedded System Laboratory (LSEC)
 * 
 * This program is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * See the GNU Lesser General Public License for more details.
 * <http://www.gnu.org/licenses/>
 */

/*!
 * \anchor CSU
 * \class hamster::sphere::csu::CSU CSU.h
 * \brief Communication security module of \ref SPHERE. 
 * \details The Central Security Unit (CSU) provides communication security 
 * for HAMSTER Units. The main services provided by CSU are:
 * - Identification & Authentication of HAMSTER modules, clusters and entities
 * in order to provide secure communication among them;
 * - Secure communication between HAMSTER units, including message integrity
 * and confidentiality.
 * .
 * \n
 * The CSU functionality is distributed among its specializations depending on
 * the type of \ref Unit "HAMSTER Unit":
 * - \ref HAMSTEREntity "HAMSTER Entities" have a \ref CSUCentral "Central CSU"
 * which is responsible for:
 *    - Verifying the identification and authenticating all modules and clusters
 *      of the entity;
 *    - Providing identification and authentication info for another entities or
 *      super entities, depending on the \ref Scenarios "scenario".
 *    .
 * - \ref HAMSTERObject "HAMSTER Objects" have a \ref CSULocal "Local CSU" which
 *   is responsible for providing the identification and authentication 
 *   information for its entity.
 * - \ref HAMSTERSuperEntity "HAMSTER Super Entities" have a \ref CSUSuper
 *   "Super CSU" responsible for identifying and authentication the entities of
 *   the system, depending on the \ref Scenarios "scenario".
 * .
 * 
 *  \sa HAMSTERUnitType
 *  
 *  \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 *  \copyright GNU Lesser General Public License.
 */

#ifndef CSU_H
#define CSU_H

#include "FlightData.h"
#include "HAMSTERPlatform.h"
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stack> //biblioteca da pilha
#include <iostream>

using namespace std;

namespace hamster {
namespace sphere {
namespace csu{

enum class CSU_STATE : uint8_t{
    INITIAL,
    WAITING_MODULES,        // HAMSTER Entity
    WAITING_PEERS,          // HAMSTER SuperEntity
    CONNECTING_CENTRAL_UNIT, // Centralized Architecture
    WAITING_CENTRAL_UNIT,      // Centralized Architecture
    REQUESTINTG_AUTHORIZATION,
//    SEND_REQUEST_ACCESS,
    WAITING_ACCESS_GRANTED,
    EXECUTING,
    EMERGENCY
};

inline std::ostream& operator<<(std::ostream& stream, const CSU_STATE& state) {
    switch(state){
        case CSU_STATE::INITIAL:
            stream << "INITIAL";
            break;
        case CSU_STATE::WAITING_MODULES:
            stream << "WAITING_MODULES";
            break;
        case CSU_STATE::WAITING_PEERS:
            stream << "WAITING_PEERS";
            break;
        case CSU_STATE::CONNECTING_CENTRAL_UNIT:
            stream << "CONNECTING_CENTRAL_UNIT";
            break;
        case CSU_STATE::WAITING_CENTRAL_UNIT:
            stream << "WAITING_CENTRAL_UNIT";
            break;
        case CSU_STATE::REQUESTINTG_AUTHORIZATION:
            stream << "REQUESTINTG_AUTHORIZATION";
            break;
        case CSU_STATE::WAITING_ACCESS_GRANTED:
            stream << "WAITING_ACCESS_GRANTED";
            break;
        case CSU_STATE::EXECUTING:
            stream << "EXECUTING";
            break;
        case CSU_STATE::EMERGENCY:
            stream << "EMERGENCY";
            break;
        default:
            stream << "without description";
            break;
    }
    return stream;
};

class CSU : public HAMSTERPlatform{
    
    friend class comm::CommBroker;
    
public:
//-----------------------------------------------------------------------------
// Constructor / Destructor
//----------------------------------------------------------------------------- 
    CSU(Unit * unit, HAMSTERUnitCommInfo * info) : HAMSTERPlatform(unit,info){};
    virtual ~CSU(){};

//-----------------------------------------------------------------------------
// HAMSTER Platform Methods
//----------------------------------------------------------------------------- 
    virtual void platformInitialization(void){
        this->SetIncomingQueue(new comm::HAMSTERQueue());
        logDebugMessage("CSU Initialization.");
    }
    
    void receberDados(sample::FlightData dados){ 
        int h = dados.get_hora();
        int m = dados.get_minuto();
        std::cout << "\t Horario = " << h << ":" << m << "\n";
            
    }
    
        
    
    void emergency(stack <double> latitudes, stack <double> longitudes, int bateria){ //ciclo OODA para tomada de decisao
        int cont = 0;
         /* ciclo ooda : DECIDE - continua executando com as coordenadas seguras*/
        if(cont < 3){
            printf("EMERGENCY: Recalculating coordenates");
            this->setState(CSU_STATE::EXECUTING); /*resiliencia - restabelecendo continuando a missao atraves coordenada antiga e segura*/
            cont = cont+1;
        }
        else{ /* ciclo ooda : ORIENT - volta para a base pela direção possivel pelo delta seguro - a mais rapida ou a mais segura*/
            if(bateria < 50){ /* retorna pela rota mais rapida entre as coordenadas guiadas */
                printf("EMERGENCY: Retornando a base");
                this->setState(CSU_STATE::INITIAL); // retorna a base a finaliza o percurso 
                exit(0); /*finaliza a missao */
            }
            else{ /*se possui bateria suficiente, retorna pela rota mais segura com base nas coordenadas conhecidas */
                this->setState(CSU_STATE::INITIAL); // retorna a base a finaliza o percurso
                exit(0); /*finaliza a missao */
            }
        }
    }
        
    void get_Security(sample::FlightData *data_history, int flightData_ID){ 
        /*sensor ids - caixa e - em busca de uma alteração na rede*/
        int pos = flightData_ID;
        int bateria = 100;
        float pi =3.14159;
        double dist = -1;
        int totalTempo = 0;
        double velocidadeMedia = 0;
        int aceleracaoMedia = 0;
        double velocMediaDrone = 80.0;
        
        if (pos >= 2){
            printf("\t Verificacao de security...\n");
            
            int hr1 = data_history[pos-2].get_hora();
            int hr2 = data_history[pos-1].get_hora();
            int min1 = data_history[pos-2].get_minuto();
            int min2 = data_history[pos-1].get_minuto();
            
            int primeiroHorario = ((hr1*60)+min1);
            int segundoHorario = ((hr2*60)+min2);
            
            totalTempo = segundoHorario - primeiroHorario; 
            int tempoSegundos = totalTempo*60; //segundos
            int tempoEmHora = totalTempo/60; //hora
            
            double lat1 = data_history[pos-2].get_latitude();
            double long1 = data_history[pos-2].get_longitude();
            double lat2 = data_history[pos-1].get_latitude();
            double long2 = data_history[pos-1].get_longitude();                         

            lat1 = ((lat1 * pi)/180.0); //conversao para grau
            long1 = ((long1 * pi)/180.0);
            lat2 = ((lat2 * pi)/180.0);
            long2 = ((long2 * pi)/180.0);
            
            // criando uma pilha com latitudes e longitudes
            stack <double> latitudes, longitudes; //dados de odometria ciclo OADA - observe
            
            latitudes.push(lat1);  // add na pilha com push as latitudes
            latitudes.push(lat2);
            longitudes.push(long1); // add na pilha com push as longitudes
            longitudes.push(long2);
            
            cout << "Tamanho da pilha: " << latitudes.size() << "\n";
            
            double Lat = lat2 - lat1;
            double Long = long2 - long1;
            double val1 = 6371;
            
            //calcula o angulo e a derivada para se obter a distancia
            double val2 = sin(Lat/2) * sin(Lat/2) + cos(lat1) * cos(lat2) * sin(Long/2) * sin(Long/2); 
            val2 = 2 * atan2(sqrt(val2), sqrt(1 - val2)); // 
            dist = val1 * val2; // distancia em kms
            
            velocidadeMedia = (dist/totalTempo);             
            aceleracaoMedia = (velocidadeMedia/tempoSegundos); //velocidade sobre o tempo
            bateria = bateria-5;
            
            if(velocidadeMedia>velocMediaDrone){  /* caixa A ids - verificando o tipo de ataque*/
                //apresentando a localizacao insegura 
                printf("\t ALERTA DE GPS SPOOFING...\n");
                cout << "Latitude insegura: "<< latitudes.top() << " | ";
                cout << "Longitude insegura: "<< longitudes.top() << "\n";
                
                latitudes.pop();  // retira da pilha com a latitude vulneravel
                longitudes.pop();
                emergency(latitudes, longitudes,bateria);
              
            }
            else{
                
                printf("\t Drone estavel \n");
                my_state = CSU_STATE::EXECUTING;
            }

        } else {
            printf("\t Preparando para voo...\n");
        }
        
        if(dist = -1){
            printf("\t\n");
        }else{
            printf("\t Distancia: %.3lf\n", dist);
            printf("\t Velocidade Media: %lf\n", velocidadeMedia);
        
        }
        
    }

protected:    
        
    CSU_STATE getState() const {
        return my_state;
    }
    
    void setState(CSU_STATE state) { 
        this->my_state = state;  
        logVerboseMessage("CSU state = ",state);

        //max(storedData,latitude_deg);
    }

private:
    CSU_STATE my_state = CSU_STATE::INITIAL;
};

} /* namespace csu */
} /* namespace sphere */
} /* namespace hamster */

#endif /* CSU_H */

