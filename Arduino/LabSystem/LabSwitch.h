#ifndef __LAB_SWITCH__
#define __LAB_SWITCH__

#include <Arduino.h>
#include "LabRelay.h"
#include "LabEncoder.h"

class LabSwitch {

public:

  LabSwitch(byte pinSwitch);
  void setRelay(LabRelay *relayPtr);
  void setEncoder(LabEncoder *encoderPtr);
  void relayOff();
  void encoderReset();
  void setDelayStart(long delayStart);
  
  boolean isOn();
  boolean isOff();
  
  void startDelay();
  boolean checkDelay();

private:

  byte _pinSwitch;
  LabRelay *_relayPtr;
  LabEncoder *_encoderPtr;

  boolean _delayStatus;
  long _delayCounter;
  long _delayStart;

};

#endif

