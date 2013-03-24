#include "LabSwitch.h"

LabSwitch::LabSwitch(byte pinSwitch) {
  _pinSwitch = pinSwitch;
  pinMode(_pinSwitch, INPUT);
  //digitalWrite(_pinSwitch, HIGH); // NAO HABILITAR - SOMENTE SE MONTADO SEM O RESISTOR NO SENSOR
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
  _relayPtr=relayPtr;
}

void LabSwitch::relayOff() {
  _relayPtr->off();
}

void LabSwitch::setEncoder(LabEncoder *encoderPtr) {
  _encoderPtr=encoderPtr;
}

void LabSwitch::encoderReset() {
  _encoderPtr->reset();
}

