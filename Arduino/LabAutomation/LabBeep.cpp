#include "LabBeep.h"

LabBeep::LabBeep() {
}

LabBeep::LabBeep(byte pinBeep) {
  _pinBeep = pinBeep;
  pinMode(_pinBeep, OUTPUT);
}

void LabBeep::play() {
  analogWrite(_pinBeep, 200);
  _delay.wait(50);
  analogWrite(_pinBeep, 0);  
}
