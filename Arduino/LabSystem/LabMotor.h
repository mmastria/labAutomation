#ifndef __LAB_MOTOR__
#define __LAB_MOTOR__

#include <Arduino.h>
#include "LabSwitch.h"
#include "LabRelay.h"
#include "LabDelay.h"

class LabMotor {

public:

  void forward();
  void reverse();
  void off();

  boolean isForward();
  boolean isReverse();
  boolean isOff();

  boolean isSwitchForwardOn();
  boolean isSwitchReverseOn();

  void setSwitchForward(LabSwitch *switchPtr);
  void setSwitchReverse(LabSwitch *switchPtr);
  void setRelayForward(LabRelay *relayPtr);
  void setRelayReverse(LabRelay *relayPtr);

private:

  LabSwitch *_switchForwardPtr;
  LabSwitch *_switchReversePtr;
  LabRelay *_relayForwardPtr;
  LabRelay *_relayReversePtr;
  LabDelay _delay;

};

#endif

