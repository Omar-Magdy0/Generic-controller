#pragma once

#include "../HAL/HAL.h"
extern unsigned long globalTime;

enum{
    start,
    checking,
    triggered,
    first
};

class timedEvent{
    unsigned long timeStart;
    unsigned long delay;
    unsigned char state = triggered;
    
    public:
    timedEvent(unsigned del){
        delay = del;
    }
    
    void set_delay(unsigned del){
        delay = del;
    
    }

    inline void RESTART(){
        if(state ==  triggered){
            timeStart = globalTime;
            state = checking;
        }
    }

    inline bool TRIGGERED(){
        if(globalTime - timeStart >= delay){
                state = triggered;
                return true;
        }
        return false;
    }
};