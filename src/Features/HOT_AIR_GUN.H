#pragma once

#include "../HAL/HAL.h"
#include "Temperature.h"
#include "AC_control.h"
#include "program.h"
#include "PID.h"

struct _hotAirGun :public program{
    private:
    unsigned long temp0_time;
    uint16_t temp0_val;
    public:
    uint8_t fanspeed;
    void init();
    void loop_func();
    static void interrupt_tick();
    void set_temperature(uint16_t t);
    uint16_t get_temperature();
    _temperature *temperature;
    unsigned int interrupt_tick_count = 0;
    uint8_t heat_validation_state;
    void heatValidation();
    bool heating;
    PID *outputVal;
};


extern _hotAirGun HOTAIR_0;