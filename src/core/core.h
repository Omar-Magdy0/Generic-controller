#pragma once

#include "setup_init.h"

struct dataVals{
    char c;
    int value;   
};

dataVals _SerialGetValue(unsigned char c);
#define TEST(n,b) (!!((n)&_BV(b)))