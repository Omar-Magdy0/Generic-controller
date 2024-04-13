#pragma once 

#include "../Config.h"
#include "../HAL/HAL.h"

struct PID{
    private:
    float _Kp;
    float _Ki;
    float _Kd;
    int last_error;
    float sum_error;
    int setpoint;
    int max_error;
    int min_error;
    int max_output;
    int min_output;

    unsigned long last_time;

    public:
    PID(float Kp, float Ki, float Kd, int max_err, int min_err, int max_out, int min_out);
    void set_setpoint(int _setpoint);
    float get_Kp();
    float get_Ki();
    float get_Kd();
    void set_Kp(float val);
    void set_Ki(float val);
    void set_Kd(float val);
    int PID_func(int current_val, unsigned long current_time);
    void reset_PID();

};