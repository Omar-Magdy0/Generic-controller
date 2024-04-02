#pragma once
#include <stdlib.h>
#include <stdint.h>
#include "HAL/HAL.h"
#include "../Config.h"
#include "../Pins/pins.h"


#if defined _TRIAC0
#define bufferLength 32

struct Triac_zeroCross{
    private:
    double frequency; 
    uint16_t Amplitude;
    uint8_t power = 0;
    bool zerocross_detect;
    public:
    bool get_zerocross_detect();
    bool _get_frequency;
    volatile uint32_t time_sample0;
    volatile uint32_t time_sample1;
    
    uint8_t dim_Type;
    unsigned char *buffer;
    uint8_t buffer_head = 0;
    void zeroCross_irq_mode(uint8_t mode);
    virtual void init();
    void set_power(uint8_t p);
    double getFrequency();

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

