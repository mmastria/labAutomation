#include "LabRelay.h"

LabRelay::LabRelay(byte pinRelay) {
  _pinRelay = pinRelay;
  _state = HIGH;
  digitalWrite(_pinRelay, _state);
  pinMode(_pinRelay, OUTPUT);
}

void LabRelay::on() {
  _state = LOW;
  digitalWrite(_pinRelay, _state);
}

void LabRelay::off() {
  _state = HIGH;
  digitalWrite(_pinRelay, _state);
}

boolean LabRelay::isOn() {
  if (_state==LOW) {
    return true;
  }
  else {
    return false;
  }
}

boolean LabRelay::isOff() {
  return !isOn();
}

