#pragma once

#include "../../Config.h"
#include "../../Pins/pins.h"
#include <stdlib.h>
#include <stdint.h>


struct UI_container {
    void progress_bar(int8_t currentVal,int8_t maxVal);
    void update_number(int16_t Val);
    void display();
    void boundingRect();
    const char* side_text;
    int8_t type;
    UI_container();

};

struct UI_input {
    


};


struct menu{
    void menu_index(int8_t);
    uint8_t main_menu_index;
    UI_container *UI_cont_ptr;
    void init_containers(uint8_t num);
    void remove_containers();

};

struct screen_wrap {
    void init();
    void loadingScreen1();
    void loadingScreen2();
    void sleep();

};






#if display == 1
#include "SSD1306_128x64/SSD1306_128x64.h"
#endif


extern screen_wrap screen;

