#include "HOT_AIR_GUN.H"
#include "stdio.h"

_hotAirGun HOTAIR_0;

//#define EXPERIMENT


void _hotAirGun::set_temperature(int t){
    _temperature_setpoint = t;
    _PID->set_setpoint(t);
}
void _hotAirGun::set_fanspeed(uint8_t f){
    fanspeed = f;
}


void _hotAirGun::loop_func(){
    #if !defined EXPERIMENT
    //GET TEMPERATURE VALUE
    int __temperature = (temperature->get_temperature_val());
    //GET OUTPUT POWER FROM PID FUNCTION and SET IT
    int power = _PID->PID_func(__temperature,globalTime);
    Triac0.set_power(power);
    //GET TEMPERATURE SET BY USER FROM SERIAL INTERFACE
    dataVals vH = _SerialGetValue(' ');
    switch (vH.c)
    {
    //SET VALUES
    case 'S':
        vH = _SerialGetValue('\r');
        switch (vH.c)
        {
        case 'F':
            set_fanspeed(vH.value);
            _SerialValidateMessage();
            break;
        case 'T':
            set_temperature(vH.value);
            _SerialValidateMessage();
            break;
        case 'P':
            _PID->set_Kp(vH.value);
            _SerialValidateMessage();
            break;
        case 'I':
            _PID->set_Ki(vH.value);
            _SerialValidateMessage();
            break;
        case 'D':
            _PID->set_Kd(vH.value);
            _SerialValidateMessage();
            break;
        default:
            _SerialErrorMessage();
            break;
        }
        break;
    //GET VALUES
    case 'G':
        vH = _SerialGetValue('\r');
        switch (vH.c)
        {
        case 'F':
            _SerialReturnValue('F',fanspeed);
            break;
        case 'T':
            _SerialReturnValue('T',__temperature);
            break;
        case 'P':
            _SerialReturnValue('P',_PID->get_Kp());
            break;
        case 'I':
            _SerialReturnValue('I',_PID->get_Ki());
            break;
        case 'D':
            _SerialReturnValue('D',_PID->get_Kd());
            break;
        case 'O':
            _SerialReturnValue('O',power);
            break;
        case 'S':
            _SerialReturnValue('S',_temperature_setpoint);
            break;
        default:
            _SerialErrorMessage();
            break;
        }
        break;
    //DEFAULT ERROR HANDLING
    case -1:
        break;
    default:
        _SerialErrorMessage();
        break;
    };       

    Serial.print(F("*PT"));
    Serial.print(power);
    Serial.print(F(";TV"));
    Serial.print(__temperature);
    Serial.print(F(";TS"));
    Serial.print(_temperature_setpoint);
    Serial.print(F(";FS"));
    Serial.println(fanspeed);

    
    //DETECT THERMAL RUNOUTS
    //heatValidation();

    #endif
    #if defined EXPERIMENT
    dataVals vH = _SerialGetValue();
    switch (vH.c)
    {
    case 'G':
        Triac0.set_power(vH.value);
        break;
    case 'F':
        set_fanspeed(vH.value);
        break;

    default:
        break;
    }
    #endif
}


void _hotAirGun::init(){
    Triac0.init();
    //START A TEMPERATURE OBJECT AND A PID one and Set interrupt function
    temperature = new _temperature(hotAir_thermistor_pin,0);
    _PID = new PID(0.5,0.01,0.2,10,-10,25,0);
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
                Serial.println(F("THERMAL RUNAWAY"));
            }
        }
        break;
    
    default:
        break;
    }

}