#include "ProIO.h"
#include <avr/interrupt.h>

// TIMERCOUNTER1 settings
#define prescaler 64
volatile uint16_t globalTimeMillis;
volatile uint8_t allRemainingFract;
#define timerOVFtoMillis ((prescaler * 256) / (F_CPU))
#define remainingFractSH ((timerOVFtoMillis*1000 % 1000) >> 4)
#define maxFract (1000 >> 4)

ISR(TIMER0_OVF_vect){
	uint16_t mils; 
	uint8_t frcts;
	//pass global vars to local ones
	mils = globalTimeMillis;
	frcts = allRemainingFract;
	mils += 1;
	frcts += remainingFractSH;
	//logic for the remaining fract time
	if (frcts >= maxFract){
		frcts -= maxFract;
		mils += 1;
	}
	//pass again to global
	globalTimeMillis = mils;
	allRemainingFract = frcts;
}
// end for timer 1

uint16_t millis(){
    SREG &= ~(1 << SREG_I);
    uint16_t t = globalTimeMillis;
    SREG |= (1 << SREG_I);
    return t;
}

// TIMER 1 count millis
#define START 1
#define END 0

void clk0CountMillis(uint8_t command){
	if (command == START)TIMSK0 |= ( 1 << TOIE0);
	if (command == END)TIMSK0 &= ~( 1 << TOIE0);}


