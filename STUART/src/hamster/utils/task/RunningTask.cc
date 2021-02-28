/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RunningTask.cc
 * Author: Mariana
 * 
 * Created on 17 de Setembro de 2018, 15:18
 */

#include "RunningTask.h"

namespace hamster{
namespace utils{
namespace task{

RunningTask::RunningTask(void (*task)(void)):task_handler(task) {
}

RunningTask::~RunningTask() {
}

} /* namespace task */
} /* namespace utils */
} /* namespace hamster */