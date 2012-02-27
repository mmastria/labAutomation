#include "LabPsd.h"

LabPsd::LabPsd() {
}

LabPsd::LabPsd(byte pinPsd) {
  _pinPsd = pinPsd;
  pinMode(_pinPsd, INPUT);
}

void LabPsd::setReference(int reference) {
  _reference = reference;
}

boolean LabPsd::isWallHit() {
  int ir1 = analogRead(_pinPsd);
  _delay.wait(20);  
  int ir2 = analogRead(_pinPsd);
  _delay.wait(20);  
  int ir3 = analogRead(_pinPsd);
  if ((ir1+ir2+ir3 / 3) <= _reference) {
    return true;
  }
  else {
    return false;
  }
}
