#pragma once
#include <stdint.h>

#define timeKeeper \
do {\
  SET_CS0(PRESCALER_64); \
  SET_COMA(0,NORMAL); \
  SET_COMB(0,NORMAL); \
  SET_WGM(0,PWM_PC_10); \
  SET_FOCA(0,0); \
  SET_FOCB(0,0); \
} while(0)



#define START 1
#define END 0
void clk0CountMillis(uint8_t command);
uint16_t millis(); 