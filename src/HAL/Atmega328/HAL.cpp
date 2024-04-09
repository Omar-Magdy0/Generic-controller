#include "HAL.h"


unsigned long globalTime;

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


void(*TICK)();

ISR(TIMER2_COMPA_vect){
        (*TICK)();
}




#define TICK_FREQUENCY 500
#define TICK_TIME_ms (1000/TICK_FREQUENCY)

void TICK_INIT(){
        //Sets prescaler to 128 and Compare match every 124counts ==> 2ms
    SBI(TCCR2B, CS20);
    CBI(TCCR2B, CS21);
    SBI(TCCR2B, CS22);
    SET_WGM(2, CTC_OCRnA );
    OCR2A = 124;
    SBI(TIMSK2, OCIE0A);
}