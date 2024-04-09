#include "Temperature.h"

_temperature::_temperature(uint8_t p , uint8_t i){
    pin = p;
    adc_init();
    adc_enable(pin);
    *_thermistor = thermistor(pin,i);
};


uint16_t _temperature::get_temperature_val(){
    return temperature_val;
}

void _temperature::set_temperature_setpoint(uint16_t val){
    temperature_setpoint = val;
}

void _temperature::get_adc_val(){
    if(adc_ready()){
        uint16_t val = adc_value();
        adc_sum += val;
        adc_samples_num++;
        if(adc_samples_num == 16/*oversampling num*/){
            adc_samples_num = 0;
            temperature_val = _thermistor->analog2tempEADC(adc_sum);
            adc_sum = 0;
        }
    }
    adc_start(ADC_TO_CHANNEL(A0));
}