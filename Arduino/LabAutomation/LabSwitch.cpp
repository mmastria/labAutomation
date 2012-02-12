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

void LabSwitch::doEvent() {
  callEvent();
}

