#ifndef HAL_H
#define HAL_H

#include "hal_settings.h"
#include "ProIO.h"

#ifdef _customSerial

#include "My_Serial.h"
extern uart0 Serial0;
#endif

extern uint32_t globalTime;

inline void getTime(){
    globalTime = millis();
} 




#endif