/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SMU.h
 * Author: Mariana
 *
 * Created on 15 de Dezembro de 2017, 14:42
 */

#ifndef SMU_H
#define SMU_H

#include "HAMSTERPlatform.h"
#include "FlightData.h"

namespace hamster {
    namespace sphere {
        namespace smu {

            class SMU : public HAMSTERPlatform {
                friend class comm::CommBroker;
                public:
                    SMU(Unit * unit, HAMSTERUnitCommInfo * info) : HAMSTERPlatform(unit, info) {
                    };
                    virtual ~SMU(){};
                    virtual void platformInitialization(void){
                        this->SetIncomingQueue(new comm::HAMSTERQueue());
                        logDebugMessage("SMU Initialization.");
                    }

                    void receberDadosSaude(sample::FlightData dadosSaude){ 
                        double modulePriority = dadosSaude.get_camera_priority();
                        double health = dadosSaude.get_health();
                        average(modulePriority, health);
                    }

                protected:
                    void average(double modulePriority, double health){
                        double nci_safety = ((health+modulePriority)/2); 
                        std::cout << "\t NCI safety: " << nci_safety << std::endl;
                    }

            };
        }
    }
}
#endif /* SMU_H */

