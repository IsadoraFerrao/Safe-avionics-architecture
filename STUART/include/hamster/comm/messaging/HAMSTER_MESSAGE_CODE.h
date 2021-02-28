/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*! 
 * \file HAMSTER_MESSAGE_CODE.h
 * \author Mariana
 * Created on 30 de Março de 2018, 16:55
 */

/*!
 * \page HAMSTERMessages HAMSTER Messages
 * 
 * The messages in HAMSTER Architecture follow a generic structure composed by
 * a message CODE and the message payload.
 * 
 * The message code is a 32-bit unsigned integer. The most significant byte is
 * a bitwise mask used to redirect HAMSTER messages more easily.
 * 
 * The message payload is a unsigned char buffer whose size can be customized. 
 * The data on the payload is specific of each message.
 *
 * <pre>
   +-------------------+------------------------------------------------------+
   |   message  code   |                   message  payload                   |
   |-------------------+------------------------------------------------------+
   |  32-bit uns. int  |                 unsigned char buffer                 |
   +-------------------+------------------------------------------------------+
 * </pre>
 *
 *
 * \section messagecode Message Codes
 *
 * The code of HAMSTER Messages are represented by a 32-bit unsigned integer. 
 * The most significant byte is reserved for bitwise interactions which allow
 * an easier message routing. The most significant's byt bitwise meaning is 
 * detailed next.
 * 
 * A 0xFF value on code MSB indicates a user-defined message. This code can be
 * used by the HAMSTER user to create application-specific messages. If the 0xFF
 * code is identified, customParseMessage() method is invoked.
 *
 * The difference between an internal or external message is given by the most
 * significant bit. Two different scenarios are detailed:
 * 
 * <b> Internal Platform <-> Platform message: </b>
 * In this case, bit 7 is set to 0 (Internal message) and the correspondent bit
 * of the RECEIVING platform is also set. This way, the Communication Broker is
 * able to redirect the message to the proper queue.
 * 
 * <b> External Platform <-> Platform message: </b>
 * In this case, bit 7 is set to 1 (External message) and the correspondent bit
 * of the RECEIVING is set to 1. The Communication Broker, once detecting an 
 * external message, forwards it to the proper \ref CommInterface "Communication Interface". 
 * 
 * On the receiving side, the Communicatino Interface will check the message 
 * receipient's ID against its own Unit ID, and if a match is detected, the most
 * significant bit is set to 0 (Internal Message) and the message is forwarded
 * to the communication broker to be delivered to the proper platform.
 *
 *\verbatim
+---------------------------+---+---+---+---+---+---+---+---+-----------------+
| MSB bit                   | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | . other bytes . |
+---------------------------+---+---+---+---+---+---+---+---+-----------------+
+ User-defined              | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |      .....      |
+---------------------------+---+---+---+---+---+---+---+---+-----------------+
+ External broadcast        | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0 |      .....      |
+---------------------------+---+---+---+---+---+---+---+---+-----------------+
+ External to CSU           | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 |      .....      |
+---------------------------+---+---+---+---+---+---+---+---+-----------------+
+ External to SMU           | 1 | 0 | 0 | 1 | 0 | 0 | 0 | 0 |      .....      |
+---------------------------+---+---+---+---+---+---+---+---+-----------------+
+ External to SEMU          | 1 | 0 | 0 | 0 | 1 | 0 | 0 | 0 |      .....      |
+---------------------------+---+---+---+---+---+---+---+---+-----------------+
+ External to NCI           | 1 | 0 | 0 | 0 | 0 | 1 | 0 | 0 |      .....      |
+---------------------------+---+---+---+---+---+---+---+---+-----------------+
+ External to NIMBLE        | 1 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |      .....      |
+---------------------------+---+---+---+---+---+---+---+---+-----------------+
+ External to NP            | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |      .....      |
+---------------------------+---+---+---+---+---+---+---+---+-----------------+
+ Internal broadcast        | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 |      .....      |
+---------------------------+---+---+---+---+---+---+---+---+-----------------+
+ Internal to CSU           | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 |      .....      |
+---------------------------+---+---+---+---+---+---+---+---+-----------------+
+ Internal to SMU           | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 |      .....      |
+---------------------------+---+---+---+---+---+---+---+---+-----------------+
+ Internal to SEMU          | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 |      .....      |
+---------------------------+---+---+---+---+---+---+---+---+-----------------+
+ Internal to NCI           | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 |      .....      |
+---------------------------+---+---+---+---+---+---+---+---+-----------------+
+ Internal to NIMBLE        | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |      .....      |
+---------------------------+---+---+---+---+---+---+---+---+-----------------+
+ Internal to NP            | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |      .....      |
+---------------------------+---+---+---+---+---+---+---+---+-----------------+\endverbatim
 *
 * \section messagelist List of HAMSTER Messages
 * In this section, a list of HAMSTER Messages are provided. 
 */


#ifndef HAMSTER_MESSAGE_CODE_H
#define HAMSTER_MESSAGE_CODE_H

namespace hamster{
namespace comm{
namespace messaging{
    
#define HAMSTER_CODE_MASK 0xFFFFFFFF

    
enum HAMSTER_MESSAGE_MASKS : uint8_t{
    FIRST_MESSAGE_MASK = 1,
    USER_DEFINED_MASK = 0xFF,
    UNIT_MASK = 0x80,
    PLATFORM_MASK = 0x7F,
    CSU_MASK = 0x40,
    SMU_MASK = 0x20,
    NCI_MASK = 0x60,
    SEMU_MASK = 0x10,
    NIMBLE_MASK = 0x04,
    NP_MASK = 0x02
    //STUART_MASK = 0x01.
};

    
enum HAMSTER_MESSAGE_CODE : uint32_t{
    /*!
     * \page HAMSTERMessages
     * \subsection General messages
     */
    /*! \page HAMSTERMessages
     *  \par ACK ACK
     *  General OK message. Indicates that all went well.
     * 
     */
    ACK,
    NACK,
    HAMSTER_USER_MSGS = 2,
    HAMSTER_UNIT_ID = ((UNIT_MASK << 24) + FIRST_MESSAGE_MASK) & HAMSTER_CODE_MASK,  // UNIT MESSAGES
    REQ_CRYPTO_INFO,
    REQ_KEY_INFO,
    HAMSTER_SETUP_FINISHED,
    REQ_ENTITY_ACCESS = ((CSU_MASK << 24) + FIRST_MESSAGE_MASK) & HAMSTER_CODE_MASK, // CSU MESSAGES
    REQ_MODULE_ACCESS,
    ENTITY_ACC_GRANTED,
    MODULE_ACC_GRANTED,
    REQ_PEER_CONN_INFO,
    RET_PEER_CONN_INFO,
    RET_PEER_UNKNOWN,
    RET_PEER_NOT_AUTHORIZED,
    RET_PEER_NOT_AVAILABLE,
    NOT_NEW_PEER_CONNECTION,
    RET_NEW_PEER_ADDED,
    RET_NEW_PEER_REFUSED,
    MISSION_CONFIGURATION  = (NP_MASK << 24) + FIRST_MESSAGE_MASK, // NP MESSAGES
    MISSION_CONFIGURATION_ACK,
    MISSION_CONFIGURATION_START,
    MISSION_CONFIGURATION_START_ACK,
    ADD_MISSION_PHASE,
    MISSION_PHASE_ADDED,
    MISSION_BEHAVIOUR,
    MISSION_BEHAVIOUR_ACK,
    MISSION_CONFIGURATION_END,
    MISSION_CONFIGURATION_END_ACK,
    CURRENT_PHASE,
    CURRENT_BEHAVIOUR,
    TERMINATE_MISSION,
    TERMINATE_MISSION_ACK,
};
/*!\endsecreflist
 */

inline std::ostream& operator<<(std::ostream& stream, const HAMSTER_MESSAGE_CODE& code) {
    switch(code){
        case HAMSTER_MESSAGE_CODE::ACK:
            stream << "ACK";
            break;
        case HAMSTER_MESSAGE_CODE::NACK:
            stream << "NACK";
            break;
        case HAMSTER_MESSAGE_CODE::HAMSTER_USER_MSGS:
            stream << "USER MESSAGE";
            break;
        case HAMSTER_MESSAGE_CODE::HAMSTER_UNIT_ID:              // 0x10000000
            stream << "HAMSTER_UNIT_ID";
            break;
        case HAMSTER_MESSAGE_CODE::REQ_CRYPTO_INFO:
            stream << "REQ_CRYPTO_INFO";
            break;
        case HAMSTER_MESSAGE_CODE::REQ_KEY_INFO:
            stream << "REQ_KEY_INFO";
            break;
        case HAMSTER_MESSAGE_CODE::HAMSTER_SETUP_FINISHED:
            stream << "HAMSTER_SETUP_FINISHED";
            break;
        case HAMSTER_MESSAGE_CODE::REQ_ENTITY_ACCESS:            // 0xA0000002
            stream << "REQ_ENTITY_ACCESS";
            break;
        case HAMSTER_MESSAGE_CODE::REQ_MODULE_ACCESS:
            stream << "REQ_MODULE_ACCESS";
            break;
        case HAMSTER_MESSAGE_CODE::ENTITY_ACC_GRANTED:
            stream << "ENTITY_ACC_GRANTED";
            break;
        case HAMSTER_MESSAGE_CODE::MODULE_ACC_GRANTED:
            stream << "MODULE_ACC_GRANTED";
            break;
        case HAMSTER_MESSAGE_CODE::REQ_PEER_CONN_INFO:
            stream << "REQ_PEER_CONN_INFO";
            break;
        case HAMSTER_MESSAGE_CODE::RET_PEER_CONN_INFO:
            stream << "RET_PEER_CONN_INFO";
            break;
        case HAMSTER_MESSAGE_CODE::RET_PEER_UNKNOWN:
            stream << "RET_PEER_UNKNOWN";
            break;
        case HAMSTER_MESSAGE_CODE::RET_PEER_NOT_AUTHORIZED:
            stream << "RET_PEER_NOT_AUTHORIZED";
            break;
        case HAMSTER_MESSAGE_CODE::RET_PEER_NOT_AVAILABLE:
            stream << "RET_PEER_NOT_AVAILABLE";
            break;
        case HAMSTER_MESSAGE_CODE::NOT_NEW_PEER_CONNECTION:
            stream << "NOT_NEW_PEER_CONNECTION";
            break;
        case HAMSTER_MESSAGE_CODE::RET_NEW_PEER_ADDED:
            stream << "RET_NEW_PEER_ADDED";
            break;
        case HAMSTER_MESSAGE_CODE::RET_NEW_PEER_REFUSED:
            stream << "RET_NEW_PEER_REFUSED";
            break;
        case HAMSTER_MESSAGE_CODE::MISSION_CONFIGURATION:        // 0x1100000E
            stream << "MISSION_CONFIGURATION";
            break;
        case HAMSTER_MESSAGE_CODE::MISSION_CONFIGURATION_ACK:    // 0x110000F
            stream << "MISSION_CONFIGURATION_ACK";
            break;
        case HAMSTER_MESSAGE_CODE::MISSION_CONFIGURATION_START:  // 0x11000010
            stream << "MISSION_CONFIGURATION_START";
            break;
        case HAMSTER_MESSAGE_CODE::MISSION_CONFIGURATION_START_ACK: // 0x11000011
            stream << "MISSION_CONFIGURATION_START_ACK";
            break;
        case HAMSTER_MESSAGE_CODE::ADD_MISSION_PHASE:            // 0x11000012
            stream << "ADD_MISSION_PHASE";
            break;
        case HAMSTER_MESSAGE_CODE::MISSION_PHASE_ADDED:          // 0x11000013
            stream << "MISSION_PHASE_ADDED";
            break;
        case HAMSTER_MESSAGE_CODE::MISSION_BEHAVIOUR:            // 0x11000014
            stream << "MISSION_BEHAVIOUR";
            break;
        case HAMSTER_MESSAGE_CODE::MISSION_BEHAVIOUR_ACK:        // 0x11000015
            stream << "MISSION_BEHAVIOUR_ACK";
            break;
        case HAMSTER_MESSAGE_CODE::MISSION_CONFIGURATION_END:    // 0x11000016
            stream << "MISSION_CONFIGURATION_END";
            break;
        case HAMSTER_MESSAGE_CODE::MISSION_CONFIGURATION_END_ACK:// 0x11000017
            stream << "MISSION_CONFIGURATION_END_ACK";
            break;
        case HAMSTER_MESSAGE_CODE::CURRENT_PHASE:                // 0x11000018
            stream << "CURRENT_PHASE";
            break;
        case HAMSTER_MESSAGE_CODE::CURRENT_BEHAVIOUR:            // 0x11000019
            stream << "CURRENT_BEHAVIOUR";
            break;
        case HAMSTER_MESSAGE_CODE::TERMINATE_MISSION:
            stream << "TERMINATE_MISSION";
            break;
        case HAMSTER_MESSAGE_CODE::TERMINATE_MISSION_ACK:
            stream << "TERMINATE_MISSION_ACK";
            break;
        default:
            stream << "INVALID";
            break;
    }
    return stream;
}

} /* namespace messaging */
} /* namespace comm */
} /* namespace hamster */



#endif /* HAMSTER_MESSAGE_CODE_H */

