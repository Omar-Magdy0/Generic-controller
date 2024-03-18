#include "setup_init.h"
#include "../Config.h"
#include "../Features/Features.h"

void  setup_init(){
    Serial.begin(115200);
    _delay_ms(50);
    
    #if _display_ > 0
    screen.init();
    
    #endif



}

