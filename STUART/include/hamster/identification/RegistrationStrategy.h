/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RegistrationStrategy.h
 * Author: Mariana
 *
 * Created on 9 de Abril de 2019, 15:55
 */

#ifndef REGISTRATIONSTRATEGY_H
#define REGISTRATIONSTRATEGY_H

#include <vector>
#include "HAMSTER.h"


namespace hamster{
namespace registration{

class RegistrationStrategy {
public:
    RegistrationStrategy();
    virtual ~RegistrationStrategy();
    
    // Serialize data to an Array that will later be copied to the message buffer
    virtual const std::vector<unsigned char> issueRegistration(utils::Uuid * destUAV) = 0;
    
    // Verify the registration data sent by the issuer
    virtual bool verifyRegistration(unsigned char * registration_data,
    std::pair<utils::Uuid,std::array<unsigned char,32>> *) = 0;
private:

};

}
}

#endif /* REGISTRATIONSTRATEGY_H */

