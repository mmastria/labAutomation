#include "LabSmotor.h"

LabSmotor::LabSmotor(byte pinDir, byte pinStep, byte pinEnable) {
  _pinDir = pinDir;
  _pinStep = pinStep;
  _pinEnable = pinEnable;
  pinMode(_pinDir, OUTPUT);
  pinMode(_pinStep, OUTPUT);
  pinMode(_pinEnable, OUTPUT);
  digitalWrite(_pinEnable, HIGH);
}

void LabSmotor::rotate(int steps, float speed){
  //rotate a specific number of microsteps (8 microsteps per step) - (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  int dir = (steps > 0)? HIGH:LOW;
  steps = abs(steps);

  digitalWrite(_pinDir,dir); 

  float usDelay = (1/speed) * 70;

  for(int i=0; i < steps; i++){
    digitalWrite(_pinStep, HIGH);
    delayMicroseconds(usDelay); 

    digitalWrite(_pinStep, LOW);
    delayMicroseconds(usDelay);
  }
} 

void LabSmotor::rotateDeg(float deg, float speed){
  //rotate a specific number of degrees (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  int dir = (deg > 0)? HIGH:LOW;
  digitalWrite(_pinDir,dir); 

  int steps = abs(deg)*(1/0.225);
  float usDelay = (1/speed) * 70;

  for(int i=0; i < steps; i++){
    digitalWrite(_pinStep, HIGH);
    delayMicroseconds(usDelay); 

    digitalWrite(_pinStep, LOW);
    delayMicroseconds(usDelay);
  }
}

void LabSmotor::enable() {
  digitalWrite(_pinEnable, LOW);
}

void LabSmotor::disable() {
  digitalWrite(_pinEnable, HIGH);
}
  
