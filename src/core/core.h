#pragma once

#include "setup_init.h"

struct dataVals{
    char c;
    int value;   
};

dataVals _SerialGetValue();
#define TEST(n,b) (!!((n)&_BV(b)))