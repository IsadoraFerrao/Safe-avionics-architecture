/* Put the implementations of ENUMS here */

#include "HAMSTER_FUNCTIONAL_CODE.h"
#include "CRYPTOGRAPHY_ALGORITMS.h"
#include "HAMSTER_UNIT_TYPE.h"

namespace hamster{
//-----------------------------------------------------------------------------
// HAMSTER_UNIT_TYPE
//-----------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& stream, const HAMSTER_UNIT_TYPE& type) {
    switch (type) {
        case HAMSTER_UNIT_TYPE::ENTITY:
            stream << "HAMSTER Entity";
            break;
        case HAMSTER_UNIT_TYPE::CLUSTER:
            stream << "HAMSTER Cluster";
            break;
        case HAMSTER_UNIT_TYPE::MODULE:
            stream << "HAMSTER Module";
            break;
        case HAMSTER_UNIT_TYPE::SUPER_ENTITY:
            stream << "HAMSTER Super Entity";
            break;
        default:
            /*!< \todo LOG EVENT ERROR_UNIT_TYPE_NOT_VALID */
            logWarningMessage("HAMSTERUnitType not valid. Type inserted = ", type);
            break;
    }
    return stream;
}
HAMSTER_UNIT_TYPE integer2UnitType(int arg){
    switch(arg){
        case 3:
            return HAMSTER_UNIT_TYPE::ENTITY;
        case 4:
            return HAMSTER_UNIT_TYPE::SUPER_ENTITY;
        case 2:
            return HAMSTER_UNIT_TYPE::CLUSTER;
        case 1:
            return HAMSTER_UNIT_TYPE::MODULE;
        default:
            return HAMSTER_UNIT_TYPE::UNKNOWN;
    }
}
//-----------------------------------------------------------------------------
// HAMSTER_FUNCTIONAL_CODE
//-----------------------------------------------------------------------------
// Operator overload to print type enum type
std::ostream& operator<<(std::ostream& stream, const HAMSTER_FUNCTIONAL_CODE& type) {
    switch (type) {
        case HAMSTER_FUNCTIONAL_CODE::AUTOPILOT:
            stream << "Autopilot";
            break;
        case HAMSTER_FUNCTIONAL_CODE::RGB_CAMERA:
            stream << "RGB Camera";
            break;
        case HAMSTER_FUNCTIONAL_CODE::NIR_CAMERA:
            stream << "NIR Camera";
            break;
        case HAMSTER_FUNCTIONAL_CODE::MULTISPECTRAL_CAMERA:
            stream << "Multispectral Camera";
            break;
        case HAMSTER_FUNCTIONAL_CODE::ALTITUDE_SENSOR:
            stream << "Altitude Sensor";
            break;
        case HAMSTER_FUNCTIONAL_CODE::DYNAMIC_PRESSURE_SENSOR:
            stream << "Dynamic Pressure Sensor";
            break;
        case HAMSTER_FUNCTIONAL_CODE::TEMPERATURE_SENSOR:
            stream << "Temperature Sensor";
            break;
        case HAMSTER_FUNCTIONAL_CODE::GPS_SENSOR:
            stream << "GPS Sensor";
            break;
        default:
            logWarningMessage("ObjectFunctionalCode invalid in operator << overload.");
            break;
    }
    return stream;
}
// Convert from integer argument
HAMSTER_FUNCTIONAL_CODE integer2FunctionalCode(int code){
    switch(code){
        case 1:
            return HAMSTER_FUNCTIONAL_CODE::AUTOPILOT;
        case 2:
            return HAMSTER_FUNCTIONAL_CODE::RGB_CAMERA;
        case 3:
            return HAMSTER_FUNCTIONAL_CODE::NIR_CAMERA;
        case 4:
            return HAMSTER_FUNCTIONAL_CODE::MULTISPECTRAL_CAMERA;
        case 5:
            return HAMSTER_FUNCTIONAL_CODE::ALTITUDE_SENSOR;
        case 6:
            return HAMSTER_FUNCTIONAL_CODE::DYNAMIC_PRESSURE_SENSOR;
        case 7:
            return HAMSTER_FUNCTIONAL_CODE::TEMPERATURE_SENSOR;
        case 8:
            return HAMSTER_FUNCTIONAL_CODE::GPS_SENSOR;
        default:
            return HAMSTER_FUNCTIONAL_CODE::UNKNOWN;
    }
}

namespace comm{
namespace cryptography{

//CRYPTOGRAPHY_ALGORITM integer2CryptoAlgorithm(int arg){
//    switch(arg){
//        case 1:
//            return CRYPTOGRAPHY_ALGORITM::ECC_160;
//            break;
//        default:
//            return CRYPTOGRAPHY_ALGORITM::UNKNOWN;
//            break;
//    }
//}

}
}

} /* namespace hamster */

char * toString(uint8_t value){
    char * buffer = new char[3];
    for (int i = 0; i < 3; i++) {
        buffer[i] = '\0';
    }
    sprintf(buffer,"%hhu",value);
    return buffer;
}