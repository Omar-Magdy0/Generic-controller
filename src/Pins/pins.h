#pragma once

#include "../Config.h"

#define XSTR(V...) #V

#ifdef __AVR__
  #define PINS_PATH(PATH, NAME) XSTR(PATH/Pins/AVR/NAME)
#endif
#include PINS_PATH(..,ATSTATION_7.h)