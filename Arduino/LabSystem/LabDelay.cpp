#include "LabDelay.h"
#include <util/delay.h>

void LabDelay::wait(unsigned int time) { 
  while (time--) 
    _delay_ms(1); 
} 
