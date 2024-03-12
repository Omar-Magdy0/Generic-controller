#include "SSD1306_128x64.h"

lightDisplay lightScreen = lightDisplay(128,64);
#define screen_adress 0x3C
const unsigned char* initScreen;


void screen_wrap::init()
{
    lightScreen.begin(SSD1306_SWITCHCAPVCC,0x3C);
    lightScreen.drawBitMap(initScreen,0,0,128,64,WHITE,true);
}