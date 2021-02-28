/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HAMSTERObjectDescriptor.h
 * Author: Mariana
 *
 * Created on 27 de Março de 2018, 14:15
 */

#ifndef HAMSTEROBJECTDESCRIPTOR_H
#define HAMSTEROBJECTDESCRIPTOR_H

#include "HAMSTERUnitDescriptor.h"
#include "HAMSTERUVComponent.h"
#include "HAMSTERObject.h"

namespace hamster{

class HAMSTERObjectDescriptor : public HAMSTERUnitDescriptor {
public:
    HAMSTERObjectDescriptor(utils::Uuid id, HAMSTER_UNIT_TYPE type);
    virtual ~HAMSTERObjectDescriptor();
    
    HAMSTERUVComponent * getComponent(uint8_t number) const;
    HAMSTERUVComponent * getComponents();
    uint8_t getNumComponents() const;
    void setNumComponents(uint8_t num_components);
    void setClassification(HAMSTERUVComponent::COMPONENT_CLASSIFICATION obj_class);
    bool isRequired() const;
    
private:
    uint8_t num_components = 0;
    HAMSTERUVComponent * components = NULL;
    HAMSTERUVComponent::COMPONENT_CLASSIFICATION object_classification;
};

} /* namespace hamster */

#endif /* HAMSTEROBJECTDESCRIPTOR_H */

