#include "PID.h"


PID::PID(float Kp, float Ki, float Kd,int max_err ,int min_err, int max_out, int min_out){
    _Kp = Kp;
    _Ki = Ki;
    _Kd = Kd;
    max_error = max_err;
    min_error = min_err;
    min_output = min_out;
    max_output = max_out;
}

void PID::reset_PID(){
    sum_error = 0;
    last_error = 0;
    last_time = 0;
}

int PID::PID_func(int current_val, unsigned long current_time){
        int error = current_val - setpoint;
        int32_t output;
        if(error > max_error){
            reset_PID();
            output = min_output;
        }else if(error < min_error){
            reset_PID();
            output = max_output;
        }else {
        int P = _Kp * error;
        sum_error += _Ki*error;
        float D = _Kd*(float(error - last_error)/(current_time - last_time));
        output = P + sum_error/*I term*/ + D;
        if(output > max_output){
            reset_PID();
            output = max_output;
        }else if(output < min_output){
            reset_PID();
            output = min_output;
        }

        }
    last_error = error;
    last_time = current_time;
    return output;
}

void PID::set_setpoint(int _setpoint){
    setpoint = _setpoint;
}