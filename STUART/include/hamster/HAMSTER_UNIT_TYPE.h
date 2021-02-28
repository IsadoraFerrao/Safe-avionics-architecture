/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HAMSTER_UNIT_TYPE.h
 * Author: Mariana
 *
 * Created on 27 de Março de 2018, 13:35
 */

#ifndef HAMSTER_UNIT_TYPE_H
#define HAMSTER_UNIT_TYPE_H

namespace hamster{

/*! 
 * \anchor HAMSTERUnitType
 * \enum HAMSTERUnitType
 * \brief Describes the types of HAMSTER Units within the architecture.
 * \details New values can be added as the architecture expands. 
 * \note The ostream operator \b \<\< is overloaded so the type 
 * string is print transparently.
 */
enum class HAMSTER_UNIT_TYPE : uint8_t{
    UNKNOWN = 0,
    MODULE = 1,        /*!< The unit is a \ref HAMSTERModule 
                        * "HAMSTER module" */
    CLUSTER = 2,       /*!< The unit is a \ref HAMSTERCluster 
                        * "HAMSTER cluster" */
    ENTITY = 3,        /*!< The unit is a \ref HAMSTEREntity 
                        * "HAMSTER entity" */
    SUPER_ENTITY = 4   /*!< The unit is a \ref HAMSTERSuperEntity 
                        * "HAMSTER Super Entity" */
};

// Operator overload to print type enum type
std::ostream& operator<<(std::ostream& stream, const HAMSTER_UNIT_TYPE& type);

HAMSTER_UNIT_TYPE integer2UnitType(int arg);

} /* namespace hamster */

#endif /* HAMSTER_UNIT_TYPE_H */

