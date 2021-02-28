/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FarashRegistraton.h
 * Author: Jean Amaro
 *
 * Created on 9 de Abril de 2019, 17:16
 */

#ifndef FARASHREGISTRATON_H
#define FARASHREGISTRATON_H

#include "RegistrationStrategy.h"
#include "Complementos.h"
#include "libtomcrypt-develop/src/headers/tomcrypt.h"
#include "HAMSTERID.h"
#include "HAMSTER_UNIT_TYPE.h"

namespace hamster{
namespace sample{
namespace registration{

//template <class id>
class FarashRegistraton{
public:
    FarashRegistraton(utils::Uuid& id):my_id(id){
    };
    virtual ~FarashRegistraton(){};
    
    // Serialize data to an Array that will later be copied to the message buffer
    const std::vector<unsigned char> issueRegistration(utils::Uuid * destUAV){
        
        unsigned char hash_result[32];
        unsigned long int outlen;
        std::vector<unsigned char> registration_message;
        int result;
        registration_message.clear();
        
        if(destUAV == NULL){
            // UAV -> GCS
            result = hash_memory(find_hash("sha256"),(const unsigned char *)my_id.toString().c_str(),my_id.toString().size(),hash_result,&outlen);
        
            if(result != CRYPT_OK){
                logErrorMessage("Could not hash, error code  = ",(int) result);
            }else{
                memcpy(this->KgcsUAV.data(),hash_result,32);
            }

            // Step 1 - random Rj
            const auto r = numeroAleatorio();

            // Step 2 - MPj
            const auto T1 = std::chrono::high_resolution_clock::now().time_since_epoch().count();

            const std::vector <unsigned char> P = concatenar(this->KgcsUAV, concatenar(r, concatenar(this->my_id.toString(), T1)));
            result = hash_memory(find_hash("sha256"),P.data(),P.size(),hash_result,&outlen);
            if(result != CRYPT_OK){
                logErrorMessage("Could not hash, error code  = ",(int) result);
                return registration_message;
            }
            // MNj
            const auto MN = ouExclusivo(r, this->KgcsUAV);
            // Setup registration message
            // {UIDj, MPj,MNj,T1}
            size_t message_size = 16 + // UUid
                                  32 + // Mpj
                                  32 + // MNj
                                   8;   // T1
            registration_message.resize(message_size);
            int64_t bits = this->my_id.getMostSignificantBits();
            memcpy(registration_message.data(),(const void *)&bits,sizeof(int64_t));
            bits = this->my_id.getLeastSignificantBits();
            memcpy((registration_message.data()+sizeof(int64_t)),(const void *) &bits,sizeof(int64_t));
            memcpy((registration_message.data()+16),(const void *) hash_result,32);
            memcpy((registration_message.data()+48),(const void *) MN.data(),32);
            memcpy((registration_message.data()+80),(const void *) &T1,8);
        }else{
            //GCS -> UAV
            result = hash_memory(find_hash("sha256"),(const unsigned char *)destUAV->toString().c_str(),destUAV->toString().size(),hash_result,&outlen);
            if(result != CRYPT_OK){
                logErrorMessage("Could not hash, error code  = ",(int) result);
            }else{
                memcpy(this->KgcsUAV.data(),hash_result,32);
            }
            //Kgcs
            result = hash_memory(find_hash("sha256"),(const unsigned char *)my_id.toString().c_str(),destUAV->toString().size(),hash_result,&outlen);
            if(result != CRYPT_OK){
                logErrorMessage("Could not hash, error code  = ",(int) result);
            }else{
                memcpy(this->Kgcs.data(),hash_result,32);
            }
            //xj
            const int id_size = destUAV->toString().size();
            std::vector<unsigned char> id;
            id.resize(id_size);
            memcpy(id.data(),destUAV->toString().c_str(),destUAV->toString().size());
            std::vector <unsigned char> X = concatenar(id,Kgcs);
            result = hash_memory(find_hash("sha256"),X.data(),X.size(),hash_result,&outlen);
            if(result != CRYPT_OK){
                logErrorMessage("Could not hash X, error code  = ",(int) result);
                return registration_message;
            }
            X.clear();
            X.resize(32);
            memcpy(X.data(),hash_result,32);  // X now holds xj
            //ej
            std::vector<unsigned char> key;
            key.resize(32);
            memcpy(key.data(),KgcsUAV.data(),32);
            const auto ej = ouExclusivo(X,key);
            //dj
            memcpy(id.data(),my_id.toString().c_str(),my_id.toString().size());
            const std::vector <unsigned char> P = concatenar(X,id);
            result = hash_memory(find_hash("sha256"),P.data(),P.size(),hash_result,&outlen);
            if(result != CRYPT_OK){
                logErrorMessage("Could not hash, error code  = ",(int) result);
                return registration_message;
            }
            //dj in hash_result
            size_t message_size = 16 + // UUid
                                  32 + // ej
                                  32; // dj
            registration_message.resize(message_size);
            int64_t bits = this->my_id.getMostSignificantBits();
            memcpy(registration_message.data(),(const void *)&bits,sizeof(int64_t));
            bits = this->my_id.getLeastSignificantBits();
            memcpy((registration_message.data()+sizeof(int64_t)),(const void *) &bits,sizeof(int64_t));
            memcpy((registration_message.data()+16),(const void *) ej.data(),32);
            memcpy((registration_message.data()+48),(const void *) hash_result,32);
        }
        return registration_message;
    }
    
    // Verify the registration data sent by the issuer
    bool verifyRegistration(HAMSTER_UNIT_TYPE type, unsigned char * registration_data,utils::Uuid * peer,std::array<unsigned char, 32> * secret){
        
        int64_t MSbits;
        int64_t LSbits;
        
        if(type == HAMSTER_UNIT_TYPE::SUPER_ENTITY){

            memcpy((void *)&MSbits,registration_data,sizeof(int64_t));
            memcpy((void *) &LSbits,(registration_data+sizeof(int64_t)),sizeof(int64_t));
            utils::Uuid peer_id(MSbits,LSbits);
            std::array<unsigned char,32> MP;
            memcpy((void *) MP.data(),(registration_data+16),32);
            std::array<unsigned char,32> MN;
            memcpy((void *) MN.data(),(registration_data+48),32);
            int64_t T1;
            memcpy((void *) &T1,(registration_data+80),8);

            // KgcsUAV
            unsigned char hash_result[32];
            unsigned long int outlen;
            int res = hash_memory(find_hash("sha256"),(const unsigned char *)peer_id.toString().c_str(),peer_id.toString().size(),hash_result,&outlen);
            if(res != CRYPT_OK){
                logErrorMessage("Could not hash, error code  = ",res);
                return false;
            }
            std::array<unsigned char,sizeof(unsigned char) * 32> key;
            memcpy(key.data(),hash_result,32);
            //r'j
            const auto r = ouExclusivo(MN,key);

            //MP'j
            const std::vector <unsigned char> P = concatenar(key, concatenar(r, concatenar(peer_id.toString(), T1)));
            res = hash_memory(find_hash("sha256"),P.data(),P.size(),hash_result,&outlen);
            if(res != CRYPT_OK){
                logErrorMessage("Could not hash, error code  = ",(int) res);
                return false;
            }
            for (int i = 0; i < 32; i++) {
                if(hash_result[i]!=MP.at(i)){
                    logErrorMessage("MP did not match");
                    return false;
                }
            }
            //xj
            peer->assign(peer_id.getMostSignificantBits(),peer_id.getLeastSignificantBits());
            const int id_size = peer_id.toString().size();
            std::vector<unsigned char> id;
            id.resize(id_size);
            memcpy(id.data(),peer_id.toString().c_str(),peer_id.toString().size());
            //Kgcs
            res = hash_memory(find_hash("sha256"),(const unsigned char *)my_id.toString().c_str(),my_id.toString().size(),hash_result,&outlen);
            if(res != CRYPT_OK){
                logErrorMessage("Could not hash, error code  = ",(int) res);
            }else{
                memcpy(this->Kgcs.data(),hash_result,32);
            }
            const std::vector <unsigned char> X = concatenar(id,Kgcs);
            res = hash_memory(find_hash("sha256"),X.data(),X.size(),hash_result,&outlen);
            if(res != CRYPT_OK){
                logErrorMessage("Could not hash X, error code  = ",(int) res);
                return false;
            }
            memcpy(secret->data(),hash_result,32);

            std::cout << "xj: ";
            for (int k = 0; k < 32; k++) {
                std::cout << std::hex << (int) hash_result[k];
            }
            std::cout << std::endl;
    //        
    //        result->first.assign(peer_id.getMostSignificantBits(),peer_id.getLeastSignificantBits());
            return true;
        }
        if(type == HAMSTER_UNIT_TYPE::ENTITY){
            memcpy((void *)&MSbits,registration_data,sizeof(int64_t));
            memcpy((void *) &LSbits,(registration_data+sizeof(int64_t)),sizeof(int64_t));
            utils::Uuid peer_id(MSbits,LSbits);

            std::array<unsigned char,32> ej;
            memcpy((void *) ej.data(),(registration_data+16),32);
            std::array<unsigned char,32> dj;
            memcpy((void *) dj.data(),(registration_data+48),32);

            // xj
            const auto xj = ouExclusivo(ej,this->KgcsUAV);

            //dj
            unsigned char hash_result[32];
            unsigned long int outlen;
            std::vector<unsigned char> id;
            id.resize(peer_id.toString().size());
            memcpy(id.data(),peer_id.toString().c_str(),peer_id.toString().size());
            const std::vector <unsigned char> P = concatenar(xj,id);
            //d_j?
            int res = hash_memory(find_hash("sha256"),P.data(),P.size(),hash_result,&outlen);
            if(res != CRYPT_OK){
                logErrorMessage("Could not hash, error code  = ",res);
                return false;
            }
            for (int i = 0; i < 32; i++) {
                if(hash_result[i]!=dj.at(i)){
                    logErrorMessage("MP did not match");
                    return false;
                }
            }
            // Secret in xj
            //xj
            peer->assign(peer_id.getMostSignificantBits(),peer_id.getLeastSignificantBits());

            memcpy(secret->data(),xj.data(),32);

            std::cout << "xj: ";
            for (int k = 0; k < 32; k++) {
                std::cout << std::hex << (int) hash_result[k];
            }
            std::cout << std::endl;
    //        const int id_size = peer_id.toString().size();
    //        std::vector<unsigned char> id;
    //        id.resize(id_size);
    //        memcpy(id.data(),peer_id.toString().c_str(),peer_id.toString().size());
    //        const std::vector <unsigned char> X = concatenar(id,key);
    //        res = hash_memory(find_hash("sha256"),X.data(),X.size(),hash_result,&outlen);
    //        if(res != CRYPT_OK){
    //            logErrorMessage("Could not hash X, error code  = ",(int) res);
    //            return false;
    //        }
    //        memcpy(result->second.data(),hash_result,32);
    //        
    //        std::cout << "xj: ";
    //        for (int k = 0; k < 32; k++) {
    //            std::cout << std::hex << (int) hash_result[k];
    //        }
    //        std::cout << std::endl;
    //        
    //        result->first.assign(peer_id.getMostSignificantBits(),peer_id.getLeastSignificantBits());
            return true;
        }
        return false;
    }
    
private:
    std::array<unsigned char,32> KgcsUAV;
    utils::Uuid my_id;
//    std::array < unsigned char, sizeof(unsigned char) * 32 > Kgcs = numeroAleatorio();
    std::array < unsigned char, sizeof(unsigned char) * 32 > Kgcs;
};



}
}
}

#endif /* FARASHREGISTRATON_H */

