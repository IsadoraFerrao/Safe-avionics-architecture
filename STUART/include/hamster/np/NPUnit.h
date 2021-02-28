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
 * \page NPPlatform Navigation Phases Platform
 * 
 * The Navigation Phases platform manages the operation of all vehicle components
 * depending on the mission stage. In the \ref NP_conecptual "conceptual model"
 * of Navigation Phases platform, \em Unmanned \em Vehicle has components 
 * represented by a \ref HAMSTERUVComponent "HAMSTER Component" and performs a
 * Mission. The mission is given by a Mission Planner, a local or remote agent,
 * human or non-human.
 * 
* 
 * \image latex NP_concepts_compact.pdf "NP Conceptual Model" width=0.3\textwidth
 * 
 * \htmlonly
 * <div>
 * <div style="float: left; width: 35%; text-align:center;">
 * \image html NP_concepts_compact.svg "NP Conceptual Model"
 * Click \link NPConceptualLarge here \endlink for bigger.
 * </div>
 * \endhtmlonly
 * <div style="float: right; width: 65%;">
 * Each Mission is divided into stages described by a \emph{Navigation Phase}. A Navigation Phase is a very well defined mission stage for which every vehicle component has a \emph{Phase Behaviour}. The Phase Behaviour describes how each component is supposed to function during a Navigation Phase, with information such as the component's ON/OFF state, the transmission rate permissions, among others.

The Phase Behaviour of a component will depend on its \emph{classification}. Most common classification splits components into \emph{mission-specific} (the component is not essential for the vehicle's operation, but necessary to perform the mission) and \emph{main} components (essential for the vehicle's operation) \cite{Pigatto2016Aplicacao}. Each HAMSTER Component also has an \emph{Emergency Behaviour} that describes its operation in emergency situations.


 * </div>
 * </div>
 
 * Every 


The functionality of NP platform is distributed among HAMSTER Entities and Objects, as shown by \figurename~\ref{fig:NP_Conceptual_Platforms}. In a HAMSTER Entity, the \emph{NP Manager} is responsible for \begin{inparaenum}[(1)]\item receiving the Navigation Phases from the Mission Planner; \item sending the Phase Behaviour to authenticated HAMSTER Objects and notify them of a new Navigation Phase; \item sending ON/OFF commands to the non-authenticated HAMSTER Objects; and \item notifying all HAMSTER Objects of an Emergency Phase\end{inparaenum}. More information on HAMSTER Object authentication is given in Section \ref{prototype}.

\begin{figure}[!ht]
\centering
\includesvg[width=\columnwidth]{images/NP_Conceptual_Platforms}
\caption{NP implementation in different Units.}
\label{fig:NP_Conceptual_Platforms}
\end{figure}

 In a HAMSTER Object the \emph{NP Agent} is responsible for receiving  from the NP Manager \begin{inparaenum}[(1)]\item the Phase Behaviour for each Navigation Phase in authenticated modules; \item ON/OFF commands in non-authenticated HAMSTER Objects and \item Emergency Phases notifications\end{inparaenum}. NP Agents also are responsible for invoking HAMSTER Objects methods to turn ON or OFF the vehicles's components.
 * 
 */
/*!
 * \anchor NPConceptualLarge
 * \page NPConceptualLarge Navigation Phases Conceptual Model
 * \image html NP_concepts_Large.svg "NP Conceptual Model"
 */
/*!
 * \namespace navigation_phases
 * \anchor NPUnit
 * \class hamster::navigation_phases::NPUnit NPUnit.h
 * \brief 
 * \details 
 * 
 * HAMSTER Units are further specialized into \ref HAMSTEREntity "entities", 
 * comprising the unmanned vehicled as a whole, or \ref HAMSTERObject "objects",
 * which which handle the internal sensors/actuators of an entity.  HAMSTER 
 * Objects are further specialized into Modules and Clusters. A HAMSTER Module 
 * is a unit which handles a single sensor/actuator of the unmanned vehicle, 
 * like the GPS sensor; a HAMSTER Cluster is a unit which handles a set of 
 * sensor/actuators with one common communication interface.
 * 
 * \author    Mariana Rodrigues    rodrigues.mariana@gmail.com
 * \copyright GNU Lesser General Public License.
 *
 */

#ifndef NPUNIT_H
#define NPUNIT_H

#include "HAMSTERPlatform.h"

namespace hamster{
    namespace navigation_phases{

class NPUnit: public HAMSTERPlatform {
    friend class comm::CommBroker;
public:
    NPUnit(Unit * unit,HAMSTERUnitCommInfo * info):HAMSTERPlatform(unit,info){};
    virtual ~NPUnit(){};
//-----------------------------------------------------------------------------
// HAMSTER Platform Methods
//----------------------------------------------------------------------------- 
    virtual void platformInitialization(void){
        this->SetIncomingQueue(new comm::HAMSTERQueue());
        logDebugMessage("NP Initialization.");
    }
protected:
            bool missionWasReceived() const {
                return mission_received;
            }
            
            void missionReceived(){
                this->mission_received = true;
            }
            
            uint8_t getCurrentPhaseNumber() const {
                return current_phase_number;
            }

            void setCurrentPhaseNumber(uint8_t current_phase) {
                this->current_phase_number = current_phase;
                logEventMessage("Current phase number = ",toString(current_phase));
            }


private:
        bool mission_received = false;
        uint8_t current_phase_number = 0;

};

    }
}
#endif /* NPUNIT_H */

