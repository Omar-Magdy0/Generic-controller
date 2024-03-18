#include "SSD1306_128x64.h"
#include "../UI_UX.h"



lightDisplay lightScreen = lightDisplay(128,64);
#define screen_adress 0x3C

void _init_screen1(){
    lightScreen.drawBitMap(initScreen1,0,0,128,64,WHITE,true);
}


void screen_wrap::init()
{  
    lightScreen.begin();
    lightScreen.wholeScreenClearDisplay();
    lightScreen.displayFunctionGroupOpt(_init_screen1);
    _delay_ms(300);
}

