#pragma once

#include "setup_init.h"

#define TEST(n,b) (!!((n)&_BV(b)))

struct dataVals{
    char c;
    float value;   
};

dataVals _SerialGetValue(unsigned char c);
void _SerialReturnValue(char c,float val);
void _SerialValidateMessage();
void _SerialErrorMessage();