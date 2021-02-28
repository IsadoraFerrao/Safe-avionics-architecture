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
 * \file   ObjectFunctionalCode.h
 * \author Mariana Rodrigues   rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 */

#ifndef OBJECTFUNCTIONALCODE_H
#define OBJECTFUNCTIONALCODE_H

#include "HAMSTER.h"

namespace hamster{
/*! 
 * \anchor HAMSTER_FUNCTIONAL_CODE
 * \enum hamster::HAMSTER_FUNCTIONAL_CODE
 * \brief Code corresponding to the vehicle's component functionality.
 * \details The enum lists the possible functionality of vehicle's components. 
 * \note The ostream operator <b> \<\< </b> is overloaded for printing information
 * on the code.
 * \warning New codes may be included as the platform grows. Every new code \b MUST
 * also include: (1) entry on \<\< operator overload and (2) a case in method 
 * \c convertInt2FunctionalCode().
 */
enum class HAMSTER_FUNCTIONAL_CODE: uint8_t{
    UNKNOWN = 0,
    AUTOPILOT = 1,
    RGB_CAMERA= 2,
    NIR_CAMERA = 3,
    MULTISPECTRAL_CAMERA = 4,
    ALTITUDE_SENSOR = 5,
    DYNAMIC_PRESSURE_SENSOR = 6,
    TEMPERATURE_SENSOR = 7,
    GPS_SENSOR = 8
};

/*!
 * \fn std::ostream& operator\<\<(std::ostream& stream, const ObjectFunctionalCode& type)
 * \brief Overloads operator \<\< for ObjectFunctionalCode.
 */
std::ostream& operator<<(std::ostream& stream, const HAMSTER_FUNCTIONAL_CODE& type);

/*!
 * \fn ObjectFunctionalCode hamster::convertInt2FunctionalCode(int code)
 * \brief Creates functional code from integer argument
 */
HAMSTER_FUNCTIONAL_CODE integer2FunctionalCode(int code);

} /* namespace hamster */

#endif /* OBJECTFUNCTIONALCODE_H */

