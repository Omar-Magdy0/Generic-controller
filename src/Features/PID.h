#pragma once 

#include "../Config.h"
#include "../HAL/HAL.h"

struct PID{
    private:
    int8_t _Kp;
    int8_t _Ki;
    float _Kd;
    int last_error;
    int sum_error;
    int setpoint;
    int max_error;
    int min_error;
    int max_output;
    int min_output;

    unsigned long last_time;

    public:
    PID(float Kp, float Ki, float Kd, int max_err, int min_err, int max_out, int min_out);
    void set_setpoint(int _setpoint);
    int get_Kp();
    int get_Ki();
    int get_Kd();
    int PID_func(int current_val, unsigned long current_time);
    void reset_PID();

};