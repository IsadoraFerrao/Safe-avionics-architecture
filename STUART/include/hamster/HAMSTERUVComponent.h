/*
 * Copyright (C) 2018     Critical Embedded System Laboratory (LSEC)
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
 * \anchor HAMSTERUVComponent
 * \class hamster::HAMSTERUVComponent HAMSTERUVComponent.h
 * \brief Class that represents any component of an Unmanned Vehicle.
 * \details A HAMSTER Component represents any sensor or actuator of the 
 * unmanned vehicle, as well as any equipment like cameras, GPS receiver, 
 * autopilot, etc. Each \ref HAMSTERModule "HAMSTER Module" is associated with
 * one component, while the \ref HAMSTERCluster "HAMSTER Cluster" can be 
 * associated to two or more components.
 * 
 * \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 *
 */

#ifndef HAMSTERUVCOMPONENT_H
#define HAMSTERUVCOMPONENT_H

#include "HAMSTER.h"
#include "HAMSTER_FUNCTIONAL_CODE.h"
#include "HAMSTER_COMPONENT_STATE.h"


namespace hamster{
    
class HAMSTERUVComponent {

public:
   
    /*! 
     *  \anchor COMPONENT_CLASSIFICATION
     *  \enum HAMSTERUVComponent::COMPONENT_CLASSIFICATION
     *  \brief Classification of the vehicle's component.
     */
    enum class COMPONENT_CLASSIFICATION{
        REQUIRED_FOR_OPERATION = 1,     /*!< The component is essential to the
                                         *   vehicle operation.               */
        MISSION_SPECIFIC = 2            /*!< The component is used only for 
                                         *   performing the mission.          */
    };
    
    inline static COMPONENT_CLASSIFICATION integer2ComponentClassification(int code){
        return (code == 1? COMPONENT_CLASSIFICATION::REQUIRED_FOR_OPERATION : COMPONENT_CLASSIFICATION::MISSION_SPECIFIC);
    }
    
    HAMSTERUVComponent();
    HAMSTERUVComponent(uint8_t number, HAMSTER_FUNCTIONAL_CODE code, COMPONENT_CLASSIFICATION classification);
    virtual ~HAMSTERUVComponent();
    
    void readFromXMLElement(TiXmlElement * xml_element);
    
    COMPONENT_CLASSIFICATION getClassification() const;
    HAMSTER_FUNCTIONAL_CODE getCode() const;
    uint8_t getNumber() const;
    HAMSTER_COMPONENT_STATE getComponent_state() const;
    
    void setClassification(COMPONENT_CLASSIFICATION classification);
    void setCode(HAMSTER_FUNCTIONAL_CODE code);
    void setNumber(uint8_t component_number);
    void setState(HAMSTER_COMPONENT_STATE state);

    
private:
    /*!< \brief State of component. */
    HAMSTER_COMPONENT_STATE component_state;
    /*!< \brief The number of the component. */
    uint8_t component_number;
    /*!< \brief Functional code of the component, defined by the enumeration 
     *    \ref HAMSTER_FUNCTIONAL_CODE "HAMSTER_FUNCTIONAL_CODE". */
    HAMSTER_FUNCTIONAL_CODE component_code;
    /*!< \brief Component classification, according to the enumeration 
     *   \ref ComponentClassification.
     */
    COMPONENT_CLASSIFICATION component_classification;
    /*!< \brief Component state in emergency situations. Only used by HAMSTER
     *   Entities. */
    HAMSTER_COMPONENT_STATE emergency_state;
};

} /* namespace hamster */



#endif /* HAMSTERUVCOMPONENT_H */

