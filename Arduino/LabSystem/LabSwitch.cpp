#include "LabSwitch.h"

LabSwitch::LabSwitch(byte pinSwitch) {
  _pinSwitch = pinSwitch;
  pinMode(_pinSwitch, INPUT);
  _delayStatus=false;
  _delayStart=-1;
  _delayCounter=-1;
  //digitalWrite(_pinSwitch, HIGH); // NAO HABILITAR - SOMENTE SE MONTADO SEM O RESISTOR NO SENSOR
}

void LabSwitch::setDelayStart(long delayStart) {
  _delayStart = delayStart;
  _delayCounter = _delayStart;
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

void LabSwitch::startDelay() {
  _delayStatus = true;
  _delayCounter = _delayStart;
}

boolean LabSwitch::checkDelay() {
  if(_delayCounter==-1)
    return false;
  else {
    if(!_delayStatus) {
      _delayCounter=_delayStart;
      return false;
    }
    else {
      if(_delayCounter>0) {
        if(isOn())
          _delayCounter--;
        else {
          _delayStatus=false;
          _delayCounter=_delayStart;
        }
        return false;
      }
      else {
        if(isOn())
          return _delayStatus;
        else {
          _delayStatus=false;
          _delayCounter=_delayStart;
          return false;
        }
      }
    }
  }
}


