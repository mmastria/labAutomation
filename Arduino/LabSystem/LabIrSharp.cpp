#include "LabIrSharp.h"
#include "LabDelay.h"

LabIrSharp::LabIrSharp(byte pinIrSharp, int reference) {
  _pinIrSharp = pinIrSharp;
  _reference = reference;
  pinMode(_pinIrSharp, INPUT);
}

boolean LabIrSharp::isWallHit() {
  LabDelay _delay;
  _delay.wait(20);  
  int ir1 = analogRead(_pinIrSharp);
  _delay.wait(20);  
  int ir2 = analogRead(_pinIrSharp);
  _delay.wait(20);  
  int ir3 = analogRead(_pinIrSharp);
  if ((ir1+ir2+ir3 / 3) > _reference) {
    return true;
  }
  else {
    return false;
  }
}

//  double mm = 30431 * pow (analogRead(_pinIrSharp),-1.169);
