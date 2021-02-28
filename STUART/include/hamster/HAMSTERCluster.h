/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HAMSTERCluster.h
 * Author: Mariana
 *
 * Created on 26 de Março de 2018, 19:18
 */

#ifndef HAMSTERCLUSTER_H
#define HAMSTERCLUSTER_H

#include "HAMSTERObject.h"

namespace hamster{

class HAMSTERCluster : public HAMSTERObject{
public:
    HAMSTERCluster(char * config_file_name);
    virtual ~HAMSTERCluster();
private:

};

} /* namespace hamster */
#endif /* HAMSTERCLUSTER_H */

