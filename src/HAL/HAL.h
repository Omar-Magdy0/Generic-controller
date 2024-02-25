#pragma once

#define XSTR(V...) #V

#ifdef __AVR__
  #define HAL_PATH(PATH, NAME) XSTR(PATH/HAL/Atmega328/NAME)
#endif

#include HAL_PATH(..,HAL.h)

