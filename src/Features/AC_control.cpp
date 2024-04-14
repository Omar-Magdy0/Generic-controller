#include "AC_control.h"
#include "../HAL/HAL.h"

#define millis_to_secs(c)( (c/10e3) )

#if defined _TRIAC0
    STTriac0 Triac0;
#endif
#if defined _TRIAC1
    STTriac1 Triac1;
#endif

// bit masks since shift left is slow in avr
#ifdef AVR
const uint8_t PROGMEM setbit[] = {0x01,0x02,0x04,0x08,
                                  0x10,0x20,0x40,0x80};
const uint8_t PROGMEM clrbit[] = {0xFE, 0xFD, 0xFB, 0xF7,
                                  0xEF, 0xDF, 0xBF, 0x7F};
#endif

void Triac_zeroCross::set_power(uint8_t p){
  power = p;
  if(power == 0){
    for(uint8_t i = 0;i < bufferLength;i++)buffer[i] = 0;
    return;
  }
  else if(power == 255){
    for(uint8_t i = 0;i < bufferLength;i++)buffer[i] = 255;
    return;
  }
  uint8_t mask;
  bool moreThanHalf = power/128;
  if(moreThanHalf){
    mask = round( (((bufferLength * 8) - 1.0))  /(256 - power) );
  } else {
    mask = round( (((bufferLength * 8) - 1.0))  / power);
  }

  for(uint8_t i = 0 ; i < bufferLength; i++){
    //cleans and clears byte before doing bitwise
    if(moreThanHalf){
      buffer[i] = 255;
    } else {
      buffer[i] = 0;
    }
    for(uint8_t j = 0 ; j < 8; j++){
      if( (( (i*8) + j + 1) % mask) == 0){
        #ifdef AVR
        if(moreThanHalf){
          buffer[i] &= pgm_read_byte(&clrbit[j & 7]);
        } else {
          buffer[i] |= pgm_read_byte(&setbit[j & 7]);
        }
        #else
        buffer[i] |= ( 1 << j );
        #endif
      }
    }
  }

}

uint8_t Triac_zeroCross::get_power(){
  return power;
}




#if defined _TRIAC0

void zeroCross0_irq(){
        //Function for deciding on or off state for Triac at zero points
}


void triac0_irq(){
  uint8_t pinValue = Triac0.buffer[Triac0.buffer_head / 8] & pgm_read_byte(&setbit[Triac0.buffer_head & 7]);
  WRITE(TRIAC0_PIN, pinValue);
  Triac0.buffer_head++;
  if(Triac0.buffer_head == 256)Triac0.buffer_head = 0;
}


void Triac_zeroCross::zeroCross_irq_mode(uint8_t mode){
  if(mode){
    zerocross_detect = true;
    attachInterrupt(digitalPinToInterrupt(ZEROCROSS0_PIN),zeroCross0_irq,FALLING);
  }else {
    zerocross_detect = false;
    detachInterrupt(digitalPinToInterrupt(ZEROCROSS0_PIN));
  }
}


void STTriac0::init(){
    buffer = (unsigned char*)malloc(sizeof(unsigned char)*bufferLength);
    SET_INPUT(ZEROCROSS0_PIN);
    SET_OUTPUT(TRIAC0_PIN);
  }
#endif



#if defined _TRIAC1

void zeroCross1_irq(){
    //Function for deciding on or off state for Triac at zero points
}

  void STTriac1::init(){
    buffer = (unsigned char*)malloc(sizeof(unsigned char)*bufferLength);
    #if defined AVR
    SET_CS2(PRESCALER_1024);
    SBI(TIMSK2,TOIE2);
    attachInterrupt(digitalPinToInterrupt(ZEROCROSS1_PIN),zeroCross1_irq,FALLING);
    SET_INPUT_PULLUP(ZEROCROSS1_PIN);
    #endif
  }
#endif



