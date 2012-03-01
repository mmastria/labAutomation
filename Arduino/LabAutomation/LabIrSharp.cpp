#include "LabIrSharp.h"

LabIrSharp::LabIrSharp() {
}

LabIrSharp::LabIrSharp(byte pinIrSharp) {
  _pinIrSharp = pinIrSharp;
  pinMode(_pinIrSharp, INPUT);
}

void LabIrSharp::setReference(int reference) {
  _reference = reference;
}

boolean LabIrSharp::isWallHit() {
  int ir1 = analogRead(_pinIrSharp);
  _delay.wait(20);  
  int ir2 = analogRead(_pinIrSharp);
  _delay.wait(20);  
  int ir3 = analogRead(_pinIrSharp);
  if ((ir1+ir2+ir3 / 3) <= _reference) {
    return true;
  }
  else {
    return false;
  }
}

void LabIrSharp::activate() {
  _active = true;
}

void LabIrSharp::deactivate() {
  _active = false;
}

boolean LabIrSharp::isActive() {
  return _active;
}
