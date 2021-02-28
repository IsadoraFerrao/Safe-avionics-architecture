/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ECCRelic.cc
 * Author: Mariana
 * 
 * Created on 10 de Setembro de 2018, 19:43
 */

#include "ECCRelic.h"
#include "CryptographyAlgorithm.h"
#include "CRYPTOGRAPHY_ALGORITMS.h"
#include "relic.h"

namespace hamster{
namespace comm{
namespace cryptography{

ECCRelic::ECCRelic():CryptographyAlgorithm(CRYPTOGRAPHY_TYPE::ASYMMETRICAL) {
    // Initialize curve
    core_init();
    ep_param_set_any();
}


ECCRelic::~ECCRelic() {
}

void ECCRelic::initializeKeys(KeyInfo * key_info){
    
    ECCRelicKeyInfo * key_info_ptr;
    bn_t n;
    
    try {
         key_info_ptr = dynamic_cast<ECCRelicKeyInfo *>(key_info);
    } catch(const std::bad_cast& e){
        //logErrorMessage("KeyInfo provided is not of correct cast. Message:",e.what());
    }
   
    //Private key
    bn_new(n);
    bn_new(key_info_ptr->getPrivateKey());
    ep_curve_get_ord(n);
    bn_rand(key_info_ptr->getPrivateKey(),BN_POS, bn_bits(n));

    //Public key
    ep_null(key_info_ptr->getPublicKey());
    ep_new(key_info_ptr->getPublicKey());
    ep_mul_gen(key_info_ptr->getPublicKey(),key_info_ptr->getPrivateKey());
    
    std::cout << "Initialized key: "<<std::endl;
    ep_print(key_info_ptr->getPublicKey());
}


int ECCRelic::encrypt(char ** criptext, char * plaintext, int plaintext_size, KeyInfo * my_key_info, KeyInfo * peer_key_info){

    ECCRelicKeyInfo * my_key, * peer_key;
    ep_t messagePoint, auxPoint;
    bn_t messageNumber;
    int size = 0;
    int number_pieces = (plaintext_size/MESSAGESIZE) + 1;
    unsigned char aux_buffer[MESSAGESIZE];
    int final_size = (number_pieces * (sizeof(ep_t) + sizeof(int))) + sizeof(int);
    
    (*criptext) = new char[final_size];

    try {
        my_key = dynamic_cast<ECCRelicKeyInfo *>(my_key_info);
    } catch(const std::bad_cast& e){
        //logErrorMessage("KeyInfo provided is not of correct cast. Message:",e.what());
    }
    try {
        peer_key = dynamic_cast<ECCRelicKeyInfo *>(peer_key_info);
    } catch(const std::bad_cast& e){
        //logErrorMessage("KeyInfo provided is not of correct cast. Message:",e.what());
    }
    
    
     memcpy(&((*criptext)[size]),&plaintext_size,sizeof(int));
     size += sizeof(int);
     
    // Divide the message payload in chunks sized MESSAGESIZE and encrypt each one of them
    for (int i = 0; i < number_pieces; i++) {
        // Clear auxiliar buffer
        memset(aux_buffer,0,MESSAGESIZE);
        // Copy chunk from payload to aux_buffer
        memcpy(aux_buffer,&(plaintext[i * MESSAGESIZE]),MESSAGESIZE);

        // Initialize variables for encryption
        ep_null(messagePoint);
        ep_new(messagePoint);
        bn_new(messageNumber);
//        size = 0;

        // Map variable to long integer
        bn_read_bin(messageNumber, aux_buffer, MESSAGESIZE);
        // Get generator in messagePoint
        ep_curve_get_gen(messagePoint);

        // Map integer to point
        for(int j = 0; j < messageNumber->used; j++)
        {
            messagePoint->x[j] = messagePoint->x[j] + messageNumber->dp[j];
        }
        
        printf("Valor de used = %d\n",messageNumber->used);

        //Multiplication of the public key point by the private key. 
        ep_null(auxPoint);
        ep_new(auxPoint);
        ep_mul_basic(auxPoint,peer_key->getPublicKey(),my_key->getPrivateKey());
        ep_add_basic(messagePoint,auxPoint,messagePoint);
        ep_free(auxPoint);

        // Write binary used parameter
        memcpy(&((*criptext)[size]),&messageNumber->used,sizeof(int));
        size += sizeof(int);
        // Write point that represent encrypted chunk
        size += write_ep((unsigned char *)&((*criptext)[size]),messagePoint);
    }
    if(size != final_size){
//        logErrorMessage("Class ",std::type_info(this).name(),": expected encryption size did not match actual encryption.");
        std::cout << "Class ECCRelic: expected encryption size did not match actual encryption." << std::endl;
        return -1;
    }
    printf("Encrypted message:\n");
    for(int j = 0; j < size;j++){
        printf("%02x",(uint8_t)(*criptext)[j]);
    }
    printf("\n");
    return size;
}


int ECCRelic::decrypt(char * criptext, char ** plaintext, int crypttext_size, KeyInfo * my_key_info, KeyInfo * peer_key_info){

    ep_t messagePoint, auxPoint, otherPoint;
    bn_t otherNumber;
    ECCRelicKeyInfo * my_key, * peer_key;
    int used,size = 0;
    int read_index = 0;
    int number_pieces = crypttext_size / sizeof(ep_t);
    
    
    memcpy(&size,&(criptext[0]),sizeof(int));
    read_index += sizeof(int);
    
    (* plaintext) = new char[number_pieces * MESSAGESIZE];
    
    try {
        my_key = dynamic_cast<ECCRelicKeyInfo *>(my_key_info);
    } catch(const std::bad_cast& e){
        //logErrorMessage("KeyInfo provided is not of correct cast. Message:",e.what());
    }
    try {
        peer_key = dynamic_cast<ECCRelicKeyInfo *>(peer_key_info);
    } catch(const std::bad_cast& e){
        //logErrorMessage("KeyInfo provided is not of correct cast. Message:",e.what());
    }
    
    // Initialize point to read message
    ep_null(messagePoint);
    ep_new(messagePoint);
    ep_null(auxPoint);
    ep_new(auxPoint);
    ep_mul_basic(auxPoint,peer_key->getPublicKey(),my_key->getPrivateKey());
   

    for (int i = 0; i < number_pieces; i++) {
        memcpy(&used,&(criptext[read_index]),sizeof(int));
        read_index += sizeof(int);
        
        read_index += read_ep((unsigned char *)&(criptext[read_index]),messagePoint);
        ep_sub_basic(messagePoint,messagePoint,auxPoint);
        
        ep_null(otherPoint);
        ep_new(otherPoint);
        ep_curve_get_gen(otherPoint);
        bn_new(otherNumber);

        for(int j = 0;j < used; j++){
            otherNumber->dp[j] = messagePoint->x[j] - otherPoint->x[j];
        }
        otherNumber->used = used;
        bn_write_bin((unsigned char *) &((*plaintext)[i*MESSAGESIZE]),MESSAGESIZE,otherNumber);
    }
    ep_free(auxPoint);
    ep_free(messagePoint);
    ep_free(otherPoint);
    bn_clean(otherNumber);
    return size;
}

int ECCRelic::write_ep(unsigned char *out, ep_t source){
    int i;
    int offset = 0;
    memcpy((void *) out, (void *) &(source->norm), sizeof(int));
    offset += sizeof(int);

    for(i = 0; i < (FP_DIGS + PADDING(FP_BYTES)/sizeof(dig_t)); i++)
    {
            memcpy((void *) (out + offset), (void *) &(source->x[i]), sizeof(dig_t));
            offset += sizeof(dig_t);
    }
    for(i = 0; i < (FP_DIGS + PADDING(FP_BYTES)/sizeof(dig_t)); i++)
    {
            memcpy((void *) (out + offset), (void *) &(source->y[i]), sizeof(dig_t));
            offset += sizeof(dig_t);
    }
    for(i = 0; i < (FP_DIGS + PADDING(FP_BYTES)/sizeof(dig_t)); i++)
    {
            memcpy((void *) (out + offset), (void *) &(source->z[i]), sizeof(dig_t));
            offset += sizeof(dig_t);
    }
    return offset;
}

int ECCRelic::read_ep(unsigned char *in, ep_t destination)
{
    int i;
    int offset = 0;
    memcpy((void *) &(destination->norm), (void *) (in + offset), sizeof(int));
    offset += sizeof(int);

    for(i = 0; i < (FP_DIGS + PADDING(FP_BYTES)/sizeof(dig_t)); i++)
    {
            memcpy((void *) &(destination->x[i]), (void *) (in + offset), sizeof(dig_t));
            offset += sizeof(dig_t);
    }
    for(i = 0; i < (FP_DIGS + PADDING(FP_BYTES)/sizeof(dig_t)); i++)
    {
            memcpy((void *) &(destination->y[i]), (void *) (in + offset), sizeof(dig_t));
            offset += sizeof(dig_t);
    }
    for(i = 0; i < (FP_DIGS + PADDING(FP_BYTES)/sizeof(dig_t)); i++)
    {
            memcpy((void *) &(destination->z[i]), (void *) (in + offset), sizeof(dig_t));
            offset += sizeof(dig_t);
    }
    return offset;
}

} /* namespace cryptography */
} /* namespace comm */
} /* namespace hamster */
