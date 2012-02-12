#include "LabBeep.h"
#include <util/delay.h>

LabBeep::LabBeep() {
}

LabBeep::LabBeep(byte pinBeep) {
  _pinBeep = pinBeep;
  pinMode(_pinBeep, OUTPUT);
}

void LabBeep::play() {
  analogWrite(_pinBeep, 200);
  delay_ms(50);
  analogWrite(_pinBeep, 0);  
}

void LabBeep::delay_ms(unsigned int time) { 
  while (time--) 
    _delay_ms(1); 
} 

