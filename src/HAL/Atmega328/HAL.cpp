#include "HAL.h"


uint32_t globalTime;

#define PCINT()\
do {\
\
}while(1)\



ISR(PCINT0_vect){
    PCINT();
};

ISR(PCINT1_vect){
    PCINT();
};

ISR(PCINT2_vect){
    PCINT();
};
