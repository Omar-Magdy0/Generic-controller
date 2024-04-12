#ifndef HAL_H
#define HAL_H

#include "hal_settings.h"
#include "ProIO.h"
#include "../../core/core.h"

#ifdef _customSerial

#include "My_Serial.h"
extern uart0 Serial0;
#endif

#define TEST(n,b) (!!((n)&_BV(b)))

#define HAL_ADC_RANGE 10
extern void(*TICK)();
void TICK_INIT();

extern uint32_t globalTime;
inline void getTime(){
    globalTime = millis();
} 

 // ADC Methods
  //

  // Called by Temperature::init once at startup
  static void adc_init() {
    ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADIF) | 0x07;
    DIDR0 = 0;
    #ifdef DIDR2
      DIDR2 = 0;
    #endif
  }

  // Called by Temperature::init for each sensor at startup
  static void adc_enable(const uint8_t ch) {
    #ifdef DIDR2
      if (ch > 7) { SBI(DIDR2, ch & 0x07); return; }
    #endif
    SBI(DIDR0, ch);
  }
  #define MUX5
#define ADC_TO_CHANNEL(c)(14-c)
  // Begin ADC sampling on the given channel. Called from Temperature::isr!
  static void adc_start(const uint8_t ch) {
    #ifdef MUX5
      ADCSRB = ch > 7 ? _BV(MUX5) : 0;
    #else
      ADCSRB = 0;
    #endif
    ADMUX = _BV(REFS0) | (ch & 0x07);
    SBI(ADCSRA, ADSC);
  }

  // Is the ADC ready for reading?
  static bool adc_ready() { return !TEST(ADCSRA, ADSC); }

  // The current value of the ADC register
  static __typeof__(ADC) adc_value() { return ADC; }


#endif