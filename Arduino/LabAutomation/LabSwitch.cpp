#include "LabSwitch.h"

LabSwitch::LabSwitch() {
}

LabSwitch::LabSwitch(byte pinSwitch) {
  _pinSwitch = pinSwitch;
  pinMode(_pinSwitch, INPUT);
}

boolean LabSwitch::isOn() {
  if (digitalRead(_pinSwitch) == HIGH) {
    return true;
  }
  else {
    return false;
  }
}

boolean LabSwitch::isOff() {
  return !isOn();
}


void LabSwitch::setRelay(LabRelay *relayPtr) {
  if (relayPtr!=NULL) {
    _relayPtr=relayPtr;
  }
}

void LabSwitch::relayOff() {
  _relayPtr->off();
}

void LabSwitch::setEncoder(LabEncoder *encoderPtr) {
  if (encoderPtr!=NULL) {
    _encoderPtr=encoderPtr;
  }
}

void LabSwitch::encoderReset() {
  _encoderPtr->reset();
}


