/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Station.h
 * Author: Mariana
 *
 * Created on 26 de Dezembro de 2017, 13:14
 */

#ifndef STATION_H
#define STATION_H

#include "HAMSTERSuperEntity.h"
#include "INETSocketInterface.h"

namespace hamster {
    namespace sample {

        class Station : public HAMSTERSuperEntity {
        public:
            Station(char * config_file_name);
            virtual ~Station();

            virtual void customInitialization(void) {
//                std::cout << "Station custom init" << std::endl;
//                this->interface->loadAcceptor();
//                std::cout << "Station Acceptor Loaded." << std::endl;
            };

            virtual void customExecution(void) {
                std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_INTERVAL_MS*10)); 
            };

            virtual void customTermination(void) {
            };
            void processMessage(utils::Uuid& peer_id, char * message){};

//            hamster::comm::interface::CommInterface* getInterface() const {
//                return interface;
//            }
//            
//            bool acceptorState() {
//                return this->interface->isAcceptorOpen();
//            }
            
        private:
            // HAMSTER Node methods
            // std::ostream& printNode(std::ostream& stream) const;

//            hamster::comm::interface::CommInterface * interface = new hamster::comm::interface::inet_socket::INETSocketInterface(this,hamster::comm::interface::COMM_INTERFACE_TYPE::ENTITY_ENTITY);

        };

    } /* namespace sample */
} /* namespace hamster */



#endif /* STATION_H */

