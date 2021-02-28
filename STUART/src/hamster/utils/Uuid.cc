/* 
 * \if DESIGN_MODEL
 * \file   UUID.cc
 * \author    Enzo Seraphim
 * \copyright GNU Lesser General Public License.
 * \endif
 */


#include "Uuid.h"
//#include <cstdlib>
//#include <cstdio>
//#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>

namespace hamster {
namespace utils {

static bool UUID_GENERATOR_RANDOMIZE = false;

//-----------------------------------------------------------------------------
// Constructor/Destructor
//-----------------------------------------------------------------------------
    Uuid::Uuid() {
        if (UUID_GENERATOR_RANDOMIZE == false) {
            UUID_GENERATOR_RANDOMIZE = true;
            srand(time(NULL));
        }
        most_sig_bits = (( int64_t) rand()) << 32;
        most_sig_bits |= (( int64_t) rand());
        least_sig_bits = (( int64_t) rand()) << 32;
        least_sig_bits += (( int64_t) rand());
    }

    Uuid::Uuid(Uuid &orig){
        this->most_sig_bits = orig.getMostSignificantBits();
        this->least_sig_bits = orig.getLeastSignificantBits();
    }
    
    Uuid::Uuid(const Uuid &orig){
        this->most_sig_bits = orig.most_sig_bits;
        this->least_sig_bits = orig.least_sig_bits;
    }
    
    Uuid::Uuid(int64_t most_sig_bits, int64_t least_sig_bits) {
        assign(most_sig_bits, least_sig_bits);
    }

    
    Uuid::Uuid(std::string value){
        fromString(value);
    }


    Uuid::~Uuid() {
        
    }
    
//-----------------------------------------------------------------------------
// GET Operators
//-----------------------------------------------------------------------------
    int64_t Uuid::getLeastSignificantBits() {
        return this->least_sig_bits;
    }

    int64_t Uuid::getMostSignificantBits() {
        return this->most_sig_bits;
    }
//-----------------------------------------------------------------------------
// SET Operators
//-----------------------------------------------------------------------------
    void Uuid::assign(int64_t most_sig_bits, int64_t least_sig_bits) {
        this->most_sig_bits = most_sig_bits;
        this->least_sig_bits = least_sig_bits;
    }
    
    
//-----------------------------------------------------------------------------
// Other methods
//-----------------------------------------------------------------------------
    std::string Uuid::digits( int64_t val, int32_t digits) {
        std::stringstream ss;
        int64_t hi = (( int64_t) 1) << (digits * 4);
        ss << std::setfill('0') << std::setw(digits + 1) << std::hex << std::uppercase << (hi | (val & (hi - 1)));
        return ss.str().substr(1, digits);
    }

    
    int32_t Uuid::compareTo(Uuid* uuid) {
        if (this->most_sig_bits == uuid->most_sig_bits) {
            if (this->least_sig_bits > uuid->least_sig_bits)
                return 1;
            else if (this->least_sig_bits < uuid->least_sig_bits)
                return -1;
            else return 0;
        } else if (this->most_sig_bits > uuid->most_sig_bits) return 1;
        else return -1;
    }

    
    void Uuid::fromString(std::string value) {
    #if !defined(UINT32_MAX)
    #error Unsupported fixed size variable
    #endif
        uint32_t val_comp[6] = {0,0,0,0,0,0};
        //split the components of the UUID   
        sscanf(value.c_str(), "%8x-%4x-%4x-%4x-%8x%4x",
                &val_comp[0], &val_comp[1], &val_comp[2], &val_comp[3], &val_comp[4], &val_comp[5]);
        //Most Significant Bits
        this->most_sig_bits = val_comp[0];
        this->most_sig_bits <<= 16;
        this->most_sig_bits |= val_comp[1];
        this->most_sig_bits <<= 16;
        this->most_sig_bits |= val_comp[2];
        //Least Significant Bits
        this->least_sig_bits = val_comp[3];
        this->least_sig_bits <<= 32;
        this->least_sig_bits |= val_comp[4];
        this->least_sig_bits <<= 16;
        this->least_sig_bits |= val_comp[5];
    }

    
    std::string Uuid::toString() const {
         int64_t most = ( int64_t)this->most_sig_bits;
         int64_t least = ( int64_t)this->least_sig_bits;
        return ( digits((most >> 32), 8) + "-"
                + digits((most >> 16), 4) + "-"
                + digits((most), 4) + "-"
                + digits((least >> 48), 4) + "-"
                + digits((least >> 16), 8)
                + digits((least), 4));
    }
//-----------------------------------------------------------------------------


    


} /* namespace utils */
} /* namespace hamster */

