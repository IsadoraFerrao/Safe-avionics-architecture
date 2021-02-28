/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MQTTSubscriber.h
 * Author: Mariana
 *
 * Created on 28 de Setembro de 2018, 21:53
 */

#ifndef MQTTSUBSCRIBER_H
#define MQTTSUBSCRIBER_H

class MQTTSubscriber {
public:
    MQTTSubscriber();
    MQTTSubscriber(const MQTTSubscriber& orig);
    virtual ~MQTTSubscriber();
    void load();
private:

};

#endif /* MQTTSUBSCRIBER_H */

