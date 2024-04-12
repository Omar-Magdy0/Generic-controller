#pragma once

#include "../HAL/HAL.h"
#include "Temperature.h"
#include "../core/core.h"
#include "AC_control.h"
#include "program.h"
#include "PID.h"

struct _hotAirGun :public program{
    private:
    uint8_t fanspeed;
    int _temperature_setpoint;
    unsigned long temp0_time;
    uint16_t temp0_val;
    public:
    
    void init();
    void loop_func();
    static void interrupt_tick();
    void set_temperature(int t);
    void set_fanspeed(uint8_t f);
    uint16_t get_temperature();
    _temperature *temperature;
    unsigned int interrupt_tick_count = 0;
    uint8_t heat_validation_state;
    void heatValidation();
    bool heating;
    PID *_PID;
};


extern _hotAirGun HOTAIR_0;