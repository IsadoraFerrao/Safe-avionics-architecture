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
 * \page HAMSTER The HAMSTER Architecture
 *
 * The HAMSTER (HeAlthy, Mobility and Security based data communication 
 * archiTEctuRe) \cite Pigatto2014Hamster is a data communication architecture 
 * for unmanned vehicles designed for improving mobility, security and safety 
 * of the overall system. It specifies a well-defined ways of achieving 
 * communication goals through a reference model.
 *
 * The architecture has different versions for each type of Unmanned Vehicle 
 * (UV). In its present state, presented below, the architecture is divided 
 * into three main versions according to the most common types of UV:
 *   - <b>Flying HAMSTER</b>, designed for the aerial segment;
 *   - <b>Running HAMSTER</b>, designed for the terrestrial segment;
 *   - <b>Swimming HAMSTER</b>, designed fot the aquatic segment.
 *
 * HAMSTER can be extended for other vehicles and systems, such as unmanned 
 * trains or domestic robots.
 *
 * HAMSTER includes four different platforms:
 * - \b SPHERE: handles safety and security aspects of the architecture;
 * - \b NIMBLE: handles the external communication of unmanned vehicles;
 * - \b NCI: handles a rich index for Quality of Service (QoS) and security and 
 *      safety;
 * - \b NP: handles the state of each unmanned vehicle module during each phase 
 *      of a flight or mission, intending on reducing energy consumption.
 *
 * \todo Colocar Figura da HAMSTER com as plataformas. E só. Nada das especializações.
 * \anchor Figure1
 * \n
 *
 * \section HAM_Unit HAMSTER Unit
 * Basic HAMSTER functionality is implemented by a HAMSTER unit. The unit may 
 * be a dedicated hardware or software running on a microprocessor, acting as
 * an intermediate between the application and the communication module 
 * (wired or wireless).
 * 
 * HAMSTER Units can be either \b Entities, which handl the vehicles as a whole,
 * or \b Objects, which handle the internal sensors/actuators of an entity. 
 * HAMSTER Objects are further specialized into \b Modules and \b Clusters. A
 * HAMSTER Module is a unit which handles a single sensor/actuator of the
 * unmanned vehicle, like the GPS sensor; a HAMSTER Cluster is a unit which
 * handles a set of sensor/actuators with one common communication interface.
 *
 * Each HAMSTER unit will have within itself the necessary implementation of 
 * HAMSTER platforms.
 * 
 * For more information on HAMSTER platforms, see \ref SPHERE, \ref NIMBLE, 
 * \ref NCI, \ref NP.
 * 
 * \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License
 *
 */

#ifndef HAMSTER_H
#define HAMSTER_H

#include <exception>
#include <stdint.h>
#include <thread>
#include <chrono>
#include <string>
#include <type_traits>
#include "tinyxml.h"
#include "tinystr.h"
#include "HAMSTERLogger.h"
#include "HAMSTEROptions.h"
#include "Uuid.h"
#include "libtomcrypt-develop/src/headers/tomcrypt.h"

//#define UAV1_MAIN
//#define AUTOPILOT
//#define RGB_CAMERA
//#define MULTISPECTRAL_CAMERA
//#define SENSOR_UNIT
//#define UAV1_MAIN
//#define UAV2_MAIN
//#define UAV3_MAIN
#define STATION_MAIN
//#define NO_AUTHENTICATION
//#define SUBSCRIBER_MAIN

#ifdef STATION_MAIN
#define LOOP_SLEEP_INTERVAL_MS 300 //calcula a cada 300 milisegundos 
#else
#define LOOP_SLEEP_INTERVAL_MS 1000
#endif
/*! \namespace hamster */
namespace hamster{
    
enum HAMSTER_RETURN : uint8_t {
    RETURN_OK = 0,
    RETURN_NOK = 1,
    UNKNOWN_PEER,
    PEER_NOT_AUTH
};

}

//#define NO_AUTHENTICATION

char * toString(uint8_t value);

#endif /* HAMSTER_H */