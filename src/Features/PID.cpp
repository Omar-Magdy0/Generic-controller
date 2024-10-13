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
        int error = setpoint - current_val;
        float output;
        if(error > max_error){
            //Saturate output
            reset_PID();
            output = max_output;
        }else if(error < min_error){
            //Saturate output
            reset_PID();
            output = min_output;
        }else {
        sum_error += float(_Ki*error);
        float P = _Kp * error;
        float I = sum_error*(current_time - last_time);
        float D = _Kd*(float(error - last_error)/(current_time - last_time));
        output = P + I + D;
        if(output > max_output){
            //Saturate output
            reset_PID();
            output = max_output;
        }else if(output < min_output){
            //Saturate output
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



float PID::get_Kp(){
    return _Kp;   
}
float PID::get_Ki(){
    return _Ki;
}
float PID::get_Kd(){
    return _Kd;
}
float PID::get_Maxout(){
    return max_output;
}
void PID::set_Kp(float val){
    _Kp = val;
}
void PID::set_Ki(float val){
    _Ki = val;
}
void PID::set_Kd(float val){
    _Kd = val;
}
void PID::set_Maxout(float val){
    max_output = val;
}
