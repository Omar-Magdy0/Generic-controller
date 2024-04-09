#pragma once
#include "thermistor/thermistor.h"
#include "../HAL/HAL.h"
#include "../Config.h"
#include "../Pins/pins.h"

struct _temperature{
private:
uint8_t pin;
uint16_t temperature_val;
uint16_t temperature_setpoint;
uint16_t adc_sum;
uint8_t adc_samples_num;
thermistor* _thermistor;


public:
_temperature(uint8_t p, uint8_t i);
void get_adc_val();
uint16_t get_temperature_val();
void set_temperature_setpoint(uint16_t val);

};

extern _temperature temperature0,temperature1,temperature2;