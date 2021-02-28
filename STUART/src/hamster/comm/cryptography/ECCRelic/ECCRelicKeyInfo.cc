/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ECCRelicKeyInfo.cc
 * Author: Mariana
 * 
 * Created on 5 de Setembro de 2018, 16:34
 */

#include "ECCRelicKeyInfo.h"

namespace hamster{
namespace comm{
namespace cryptography{


ECCRelicKeyInfo::ECCRelicKeyInfo() {
}

ECCRelicKeyInfo::ECCRelicKeyInfo(const ECCRelicKeyInfo& orig) {
}

ECCRelicKeyInfo::~ECCRelicKeyInfo() {
}

int ECCRelicKeyInfo::pushInPayload(char ** buffer){
    int i;
    int offset = 0;
    memcpy((void *) (*buffer), (void *) &(this->my_public_key->norm), sizeof(int));
    offset += sizeof(int);

    for(i = 0; i < (FP_DIGS + PADDING(FP_BYTES)/sizeof(dig_t)); i++)
    {
            memcpy((void *) ((*buffer) + offset), (void *) &(this->my_public_key->x[i]), sizeof(dig_t));
            offset += sizeof(dig_t);
    }
    for(i = 0; i < (FP_DIGS + PADDING(FP_BYTES)/sizeof(dig_t)); i++)
    {
            memcpy((void *) ((*buffer) + offset), (void *) &(this->my_public_key->y[i]), sizeof(dig_t));
            offset += sizeof(dig_t);
    }
    for(i = 0; i < (FP_DIGS + PADDING(FP_BYTES)/sizeof(dig_t)); i++)
    {
            memcpy((void *) ((*buffer) + offset), (void *) &(this->my_public_key->z[i]), sizeof(dig_t));
            offset += sizeof(dig_t);
    }
    printf("Serialized key:");
    for (int i = 0; i < offset; i++) {
        printf("%c",buffer[i]);
    }
    printf("\n");
    return offset;
};

int ECCRelicKeyInfo::pullFromPayload(char * buffer){
    int i;
    int offset = 0;
    memcpy((void *) &(this->my_public_key->norm), (void *) (buffer + offset), sizeof(int));
    offset += sizeof(int);

    for(i = 0; i < (FP_DIGS + PADDING(FP_BYTES)/sizeof(dig_t)); i++)
    {
            memcpy((void *) &(this->my_public_key->x[i]), (void *) (buffer + offset), sizeof(dig_t));
            offset += sizeof(dig_t);
    }
    for(i = 0; i < (FP_DIGS + PADDING(FP_BYTES)/sizeof(dig_t)); i++)
    {
            memcpy((void *) &(this->my_public_key->y[i]), (void *) (buffer + offset), sizeof(dig_t));
            offset += sizeof(dig_t);
    }
    for(i = 0; i < (FP_DIGS + PADDING(FP_BYTES)/sizeof(dig_t)); i++)
    {
            memcpy((void *) &(this->my_public_key->z[i]), (void *) (buffer + offset), sizeof(dig_t));
            offset += sizeof(dig_t);
    }
    return offset;
}

} /* namespace cryptography */
} /* namespace comm */
} /* namespace hamster */