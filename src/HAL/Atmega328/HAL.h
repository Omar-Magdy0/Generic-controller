#ifndef HAL_H
#define HAL_H

#include "ProIO.h"
#include "Serial.h"
extern Serial Serial0;

void setupFunction(){
  SREG |= (1<<SREG_I);
}

#endif