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
 * \anchor SPHERE
 * \class hamster::sphere::SPHERE SPHERE.h
 * \brief SPHERE (Security and safety Platform for HEteRogeneous systEms) is 
 * the safety and security platform for HAMSTER architecture. 
 * \details SPHERE allow every unmanned vehicle running a HAMSTER-based 
 * architecture to safely share information and provide/consume services. Also,
 * SPHERE centralizes the health checking of HAMSTER Units, which guarantees a
 * safer operation for the vehicle and, consequently, the entire system.
 * 
 * SPHERE functionality are split in three modules:
 * - CSU (Central Security Unit): provides secure communication and information
 *   exchange between HAMSTER Units.
 * - SMU (Safety Management Unit): provides health checking of HAMSTER Units 
 *   and safety control.
 * - SEMU (Sevice Exchange Management Unit): provides secure provision and/or
 *   consumption of services between HAMSTER Units.
 * 
 *  \image html SPHERE_Conceptual_Platforms_Brief.svg
 *  \image latex SPHERE_Conceptual_Platforms_Brief.pdf "SPHERE Platforms" width=0.3\textwidth
 * 
 * Although the platform has centralised modules, their implementation is 
 * distributed among the HAMSTER Units, depending on its type:
 * - \ref HAMSTEREntity "HAMSTER Entities" have a \ref CentralSPHERE "Central
 *   SPHERE", responsible for overall health monitoring and service exchange
 *   security, as well as its secure interface with HAMSTER Objects and 
 *   HAMSTER Super Entity or other entities, depending on the \ref scenarios
 *   "operating scenario". A Central SPHERE is composed by a \ref CentralCSU
 *   "Central CSU", a \ref CentralSMU "Central SMU" and a \ref CentralSEMU
 *   "Central SEMU".
 * - \ref HAMSTERObject "HAMSTER Objects" have a \ref LocalSPHERE "Local SPHERE"
 *   responsible for its secure interface with their entities, health checking
 *   and service exchange security. A Local SPHERE is composed by a \ref LocalCSU
 *   "Local CSU", a \ref LocalSMU "Local SMU" and a \ref LocalSEMU
 *   "Local SEMU".
 * - \ref HAMSTERSuperEntity "HAMSTER Super Entities" have a \ref SPHERESuper
 *   "Super SPHERE" responsible secure communication between entities in the
 *   system.for identifying and authentication the entities of
 *   the system, depending on the \ref Scenarios "scenarios".  A Super SPHERE is
 *   composed by a \ref SuperCSU "Super CSU", a \ref SuperSMU "Super SMU" and a 
 *   \ref SuperSEMU "Super SEMU".
 * .
 * 
 * \image html SPHERE_Conceptual_Platforms_Detail.svg
 * \image latex SPHERE_Conceptual_Platforms_Detail.pdf width=\textwidth
 * 
 *  \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 *  \copyright GNU Lesser General Public License.
 */

#ifndef SPHERE_H
#define SPHERE_H

#include "HAMSTERPlatform.h"
#include "FlightData.h"


namespace hamster {
namespace sphere{
namespace csu{class CSU;}
namespace smu{class SMU;}
namespace NCI{class NCI;}
namespace semu{class SEMU;}
    
class SPHERE : public HAMSTERPlatform{
    
    friend class comm::CommBroker;
    
public:
    
//-----------------------------------------------------------------------------
// Constructor / Destructor
//----------------------------------------------------------------------------- 
    SPHERE(Unit * unit, HAMSTERUnitCommInfo * info);
    virtual ~SPHERE();
    
//-----------------------------------------------------------------------------
// HAMSTER Platform Methods
//----------------------------------------------------------------------------- 
    virtual void platformInitialization(void);
    
    void receberDados(sample::FlightData dados); //metrica da csu
    void receberDadosSaude(sample::FlightData dadosSaude); // metrica da smu
    void get_Security(sample::FlightData *data_history, int flightData_ID);
        
    void platformLoop(void);
    virtual void platformTermination(void) = 0;
    virtual void parseMessage(hamster::comm::messaging::HAMSTERMessage * msg) = 0;
    virtual bool setupFinished();
    
            csu::CSU* getCSUModule() const {
                return csu_module;
            }

            semu::SEMU* getSEMUModule() const {
                return semu_module;
            }

            smu::SMU* getSMUModule() const {
                return smu_module;
            }

            NCI::NCI* getNCIModule() const {
                return NCI_module;
            }


protected:
//-----------------------------------------------------------------------------
// SET methods for modules
//-----------------------------------------------------------------------------
    void SetCSUModule(csu::CSU* csu_module);
    void SetSEMUModule(semu::SEMU* semu_module);
    void SetSMUUModule(smu::SMU* smu_module);
    void SetNCIModule(NCI::NCI* NCI_module);
   
private:
//-----------------------------------------------------------------------------
// SPHERE modules
//-----------------------------------------------------------------------------
    /*! \brief Points to CSU module of SPHERE. The piece of functionality of
     *  each CSU will depend on the \ref HAMSTERUnitType "HAMSTER Unit type". */
    csu::CSU * csu_module;
    /*! \brief Points to SMU module of SPHERE. The piece of functionality of
     *  each SMU will depend on the \ref HAMSTERUnitType "HAMSTER Unit type". */
    smu::SMU * smu_module;
    NCI::NCI * NCI_module;
    /*! \brief Points to SEMU module of SPHERE. The piece of functionality of
     *  each SEMU will depend on the \ref HAMSTERUnitType "HAMSTER Unit type". */
    semu::SEMU * semu_module;
};

} /* namespace sphere */
} /* namespace hamster */

#endif /* SPHERE_H */

