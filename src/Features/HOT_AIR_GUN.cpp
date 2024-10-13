#include "HOT_AIR_GUN.H"
#include "stdio.h"

_hotAirGun HOTAIR_0;


void _hotAirGun::set_temperature(int t){
    _temperature_setpoint = t;
    _PID->set_setpoint(t);
}

void _hotAirGun::set_fanspeed(uint8_t f){
    fanspeed = f;
    WRITE(hotAir_Fan_pin,f);
}


void _hotAirGun::loop_func(){
    //GET TEMPERATURE VALUE
    int __temperature = (temperature->get_temperature_val());



    //GET OUTPUT POWER FROM PID FUNCTION and SET IT AT approx 10HZ frequency (non critical parameter)
    static timedEvent PIDFunction = timedEvent(100);

    if(PIDFunction.TRIGGERED()){
        int power = _PID->PID_func(__temperature,globalTime);
        Triac0.set_power(power);
        PIDFunction.RESTART();
    }
    
    //OCCASIONAL message with the following
    static timedEvent occassionalMessage = timedEvent(1000);

    if(occassionalMessage.TRIGGERED()){
        //communication part
        set_getFrom_COM();

        Serial.print(F("*PT"));
        Serial.print(Triac0.get_power());    
        Serial.print(F(";TV"));
        Serial.print(__temperature);
        Serial.print(F(";TS"));
        Serial.print(_temperature_setpoint);
        Serial.print(F(";FS"));
        Serial.println(fanspeed);
        occassionalMessage.RESTART();
    }
    



    //DETECT THERMAL RUNOUTS
    //heatValidation();
}





// INITIALIZE HOT AIR GUN OBJECT
void _hotAirGun::init(){
    Triac0.init();
    PWM_PIN(hotAir_Fan_pin);
    //START A TEMPERATURE OBJECT AND A PID one and Set interrupt function
    temperature = new _temperature(hotAir_thermistor_pin,0);
    float A;
    _PID = new PID(EEPROM.get(0,A),EEPROM.get(4,A),EEPROM.get(8,A),40,-40,EEPROM.get(12,A),0);
    TICK =  interrupt_tick;
    TICK_INIT();
}

// INTERRUPT REQUIRED FUNCTIONS INTERRUPT RUNS AT 500HZ frequency
void _hotAirGun::interrupt_tick(){
        HOTAIR_0.interrupt_tick_count++;

        if(!(HOTAIR_0.interrupt_tick_count%5)){
        triac0_irq();
        HOTAIR_0.temperature->get_adc_val();
        }
}


//SET OR GET VALURE FROM COMMUNICATION WRAPPER
void _hotAirGun::set_getFrom_COM(){
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
        case 'M':
            _PID->set_Maxout(vH.value);
            _SerialValidateMessage();
            break;
        case 'X':
            EEPROM.put(0,_PID->get_Kp());
            EEPROM.put(4,_PID->get_Ki());
            EEPROM.put(8,_PID->get_Kd());
            EEPROM.put(12,_PID->get_Maxout());
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
            _SerialReturnValue('T',temperature->get_temperature_val());
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
            _SerialReturnValue('O',Triac0.get_power());
            break;
        case 'S':
            _SerialReturnValue('S',_temperature_setpoint);
            break;
        case 'M':
            _SerialReturnValue('M',_PID->get_Maxout());
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
}



//TEMPERATURE VALIDATION
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