/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RunningTask.h
 * Author: Mariana
 *
 * Created on 17 de Setembro de 2018, 15:18
 */

#ifndef RUNNINGTASK_H
#define RUNNINGTASK_H

namespace hamster{
namespace utils{
namespace task{
    
class RunningTask {
public:
    static RunningTask * createTask(void *task(void));
    bool isRunning();
    
protected:
    RunningTask(void (*task)(void));
    virtual ~RunningTask();

    void setRunning(bool value);
    virtual void run() = 0;
    
private:
    void (*task_handler)(void);
    bool running = false;
    
};

} /* namespace task */
} /* namespace utils */
} /* namespace hamster */

#endif /* RUNNINGTASK_H */

