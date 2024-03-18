#include "AC_control.h"
#include "../HAL/HAL.h"

#define millis_to_secs(c)( (c/10e3) )

#if defined _TRIAC0
    STTriac0 Triac0;
#endif
#if defined _TRIAC1
    STTriac1 Triac1;
#endif


#if defined _TRIAC0 || defined _TRIAC1


void Triac_zeroCross::frequency_check(){
    _get_frequency = true;
}

double Triac_zeroCross::getFrequency(){
    if(_point_num == 2){
    frequency =  (1/ ((time_sample1 - time_sample0) / 500.0) );
    _point_num = 0;
    return frequency;
    } 
    return -1;
}

void Triac_zeroCross::calc_buffer(){
;}
#endif

#if defined _TRIAC1
void zeroCross1_irq(){
    Triac1.time_sample0= Triac1.time_sample1;
    Triac1.time_sample1 = globalTime;
    //Function for deciding on or off state for Triac at zero points
}
#endif


#if defined _TRIAC0
void zeroCross0_irq(){
    
if(Triac0._get_frequency == true){
        unsigned long time = millis();
        if(Triac0._point_num == 0){
        Triac0.time_sample0 = time;
        Triac0._point_num = 1;
        Serial.println(Triac0.time_sample0);
        }  else if (Triac0._point_num == 1 && (Triac0._point_num != time)){
        Triac0.time_sample1 = time;
        Triac0._get_frequency = false;
        Serial.println(Triac0.time_sample1);
        Triac0._point_num = 2;
        }
}

        //Function for deciding on or off state for Triac at zero points
}


void STTriac0::init(){
    buffer = (unsigned char*)malloc(sizeof(unsigned char)*bufferLength);
    #if defined AVR
    attachInterrupt(digitalPinToInterrupt(ZEROCROSS0_PIN),zeroCross0_irq,FALLING);
    SET_INPUT(ZEROCROSS0_PIN);
    #endif
    
  }
#endif

#if defined _TRIAC1
  void STTriac1::init(){
    buffer = (unsigned char*)malloc(sizeof(unsigned char)*bufferLength);
    #if defined AVR
    attachInterrupt(digitalPinToInterrupt(ZEROCROSS1_PIN),zeroCross1_irq,FALLING);
    SET_INPUT_PULLUP(ZEROCROSS1_PIN);
    #endif
    
  }
#endif



