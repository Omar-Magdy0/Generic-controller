#include "HOT_AIR_GUN.H"

_hotAirGun HOTAIR_0;

void _hotAirGun::loop_func(){
    Serial.println(temperature->get_temperature_val());
    heatValidation();
    Serial.print("OUTPUT IS :");
    outputVal->set_setpoint(100);
    Serial.println(outputVal->PID_func(temperature->get_temperature_val(),globalTime));

}

void _hotAirGun::init(){
    Triac0.init();
    Triac0.set_power(50);
    temperature = new _temperature(hotAir_thermistor_pin,0);
    outputVal = new PID(2,10,10,10,-10,(32000),0);
    TICK =  interrupt_tick;
    TICK_INIT();
}

void _hotAirGun::interrupt_tick(){
        HOTAIR_0.interrupt_tick_count++;

        if(!(HOTAIR_0.interrupt_tick_count%5)){
        triac0_irq();
        HOTAIR_0.temperature->get_adc_val();
        }
}


enum temp_validator{
    idle,
    wait_check,
    check,
};


void _hotAirGun::heatValidation(){
    if(temperature->get_temperature_val() > HOT_AIR_MAXTEMP){
        Serial.println(F("THERMAL RUNAWAY"));
    }
    else if(temperature->get_temperature_val() < HOT_AIR_MINTEMP){
        Serial.println(F("THERMAL RUNAWAY"));
    }

    switch (heat_validation_state)
    {
    case idle:
        if(heating){
        temp0_val = temperature->get_temperature_val();
        heat_validation_state = wait_check;
        temp0_time = globalTime/1000;
        }
        break;
    
    case wait_check:
        if( (temp0_time/1000 + THEMAL_RUNAWAY_TIMEOUT_HOTAIR0) >= globalTime/1000){
            if((temp0_val - temperature->get_temperature_val()) >= MINIMUM_TEMPERATURE_CHANGE_HOTAIR0){
                heat_validation_state = idle;
            }
            else{
                Serial.println("THERMAL RUNAWAY");
            }
        }
        break;
    
    default:
        break;
    }

}