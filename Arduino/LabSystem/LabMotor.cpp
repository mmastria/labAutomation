#include "LabMotor.h"

void LabMotor::forward() {
  if (!isForward() && !isSwitchForwardOn()) {
    off();
    _relayForwardPtr->on();
    _delay.wait(100);
  }
}

void LabMotor::reverse() {
  if (!isReverse() && !isSwitchReverseOn()) {
    off();
    _relayReversePtr->on();
    _delay.wait(100);
  }
}

void LabMotor::off() {
  if (isForward()) {
    _relayForwardPtr->off();
    _delay.wait(400);
  }
  if (isReverse()) {
    _relayReversePtr->off();
    _delay.wait(400);
  }
}

boolean LabMotor::isForward() {
  if (_relayForwardPtr!=NULL) {
    return _relayForwardPtr->isOn();
  }
  return false;
}

boolean LabMotor::isReverse() {
  if (_relayReversePtr!=NULL) {
    return _relayReversePtr->isOn();
  }
  return false;
}

boolean LabMotor::isOff() {
  return !isForward() && !isReverse();
}

boolean LabMotor::isSwitchForwardOn() {
  if (_switchForwardPtr!=NULL) {
    return _switchForwardPtr->isOn();
  }
  return false;
};

boolean LabMotor::isSwitchReverseOn() {
  if (_switchReversePtr!=NULL) {
    return _switchReversePtr->isOn();
  }
  return false;
};

void LabMotor::setSwitchForward(LabSwitch *switchPtr) {
  if (switchPtr!=NULL) {
    _switchForwardPtr=switchPtr;
  }
}

void LabMotor::setSwitchReverse(LabSwitch *switchPtr) {
  if (switchPtr!=NULL) {
    _switchReversePtr=switchPtr;
  }
}

void LabMotor::setRelayForward(LabRelay *relayPtr) {
  if (relayPtr!=NULL) {
    _relayForwardPtr=relayPtr;
  }
}

void LabMotor::setRelayReverse(LabRelay *relayPtr) {
  if (relayPtr!=NULL) {
    _relayReversePtr=relayPtr;
  }
}


