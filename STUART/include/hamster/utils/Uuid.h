/*! 
 * \if DESIGN_MODEL
 * 
 *    \class hamster::utils::Uuid
 *    \brief A unique identifier \cite RFC4122 for HAMSTER Nodes.
 *    \details 
 *       \note This class is taken from 
 *        <a href="https://seer.ufmg.br/index.php/jidm/article/view/240">ObInject framework</a> 
 *        source code.
 *    \n
 * 
 * \endif
 * 
 * \file      UUID.h
 * \author    Enzo Seraphim
 * \copyright GNU Lesser General Public License.
 * 
 */

// \todo Colocar artigo do ObInject na bibliografia e mudar aqui pra \cite?
#ifndef UUID_H
#define UUID_H

#include "HAMSTERID.h"
#include <string>
#include <stdint.h>

namespace hamster {
namespace utils {

class Uuid{//: public identification::HAMSTERID{
    
private:
    int64_t most_sig_bits;          /*!< \brief UUID most significant bits. */
    int64_t least_sig_bits;         /*!< \brief UUID least significant bits. */
    
    /*!
     * \fn static std::string hamster::utils::Uuid::digits(int64_t val, int32_t digits)
     * \brief Outputs number digits to string.
     */
    static std::string digits(int64_t val, int32_t digits);

public:

    Uuid();
    Uuid(Uuid &orig);
    Uuid(const Uuid &orig);
    Uuid(int64_t most_sig_bits, int64_t least_sig_bits);
    Uuid(std::string value);
    virtual ~Uuid();
    
    /*!
     * \fn void hamster::utils::Uuid::assign(int64_t most_sig_bits, int64_t least_sig_bits)
     * \brief Assign most and least significant digits to UUID.
     */
    void assign(int64_t most_sig_bits, int64_t least_sig_bits);
    
    /*!
     * \fn void hamster::utils::Uuid::fromString(std::string value)
     * \brief Compares two UUIDs.
     * \return 1 if higher, 0 if equals and -1 if lower.
     */
    int32_t compareTo(Uuid* uuid);

    /*!
     * \fn void hamster::utils::Uuid::fromString(std::string value)
     * \brief Extract UUID from string.
     */
    void fromString(std::string value);
    /*!
     * \fn void hamster::utils::Uuid::fromString(std::string value)
     * \brief Outputs UUID to string.
     */
    std::string toString() const;

    int64_t getLeastSignificantBits();
    int64_t getMostSignificantBits();

    
//-----------------------------------------------------------------------------
// Operator overloading
//-----------------------------------------------------------------------------
    /*!
     * \fn inline bool hamster::utils::Uuid::operator==(const Uuid& id);
     * \brief Operator overloading for UUID equality comparison.
     */
    inline bool operator==(const Uuid id){
        bool result = (this->most_sig_bits == id.most_sig_bits)
                && (this->least_sig_bits == id.least_sig_bits);
        return result;
    }
    
    /*!
     * \fn inline friend std::ostream& hamster::utils::Uuid::operator<<(std::ostream& stream, const Uuid& uuid)
     * \brief Operator overloading for printing the UUID in ostream.
     */
    inline friend std::ostream& operator<<(std::ostream& stream, const Uuid& uuid){
        stream << uuid.toString();
        return stream;
    }
    
    /*!
     * \fn inline friend std::ostream& hamster::utils::Uuid::operator=(const Uuid& uuid)
     * \brief Operator overloading for printing the UUID in ostream.
     */
    inline Uuid& operator=(const Uuid& id){
       this->most_sig_bits = id.most_sig_bits;
       this->least_sig_bits = id.least_sig_bits;
       return *this;
    }
    
//    bool operator<(const Uuid& id){
//        if (most_sig_bits == id.most_sig_bits) {
//            return (this->least_sig_bits < id.least_sig_bits);
//        }
//        return (this->most_sig_bits < id.least_sig_bits);
//    }
    
    friend bool operator<(const Uuid id1,const Uuid id2){
        if (id1.most_sig_bits == id2.most_sig_bits) {
            return (id1.least_sig_bits < id2.least_sig_bits);
        }
        return (id1.most_sig_bits < id2.most_sig_bits);
    }

};

    
    

} /* namespace utils */
} /* namespace hamster */

#endif	/* UUID_H */

