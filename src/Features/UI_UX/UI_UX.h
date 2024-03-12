#pragma once

#include "../../Config.h"
#include "../../Pins/pins.h"

struct screen_wrap {
    void init();
    void sleep();
    void display(const char*);
    void display();
    void display_funcArray();
};





#if display == 1
#include "SSD1306_128x64/SSD1306_128x64.h"
#endif


extern screen_wrap screen;

