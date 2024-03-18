#pragma once
#include <stdlib.h>
#include <stdint.h>
#include "HAL/HAL.h"
#include "../Config.h"
#include "../Pins/pins.h"


#if defined _TRIAC0
#define bufferLength 64

struct Triac_zeroCross{
    private:
  
    uint16_t Amplitude;
    uint8_t power;
    public:
    double frequency; 
    uint8_t _point_num;
    bool _get_frequency;
    volatile uint32_t time_sample0;
    volatile uint32_t time_sample1;
    uint8_t dim_Type;
    unsigned char *buffer;
    virtual void init();
    void set_power();
    double getFrequency();
    void frequency_check();
    void calc_buffer();
};

class STTriac0 : public Triac_zeroCross{
    public:
    void init();
};

class STTriac1 : public Triac_zeroCross{
    public:
    void init();
};
#endif

#if defined _TRIAC0
extern STTriac0 Triac0;
#endif
#if defined _TRIAC1
extern STTriac1 Triac1;
#endif