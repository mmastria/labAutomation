#ifndef __LAB_SWITCH__
#define __LAB_SWITCH__

#include <Arduino.h>
#include "LabComponent.h"

class LabSwitch : 
public LabComponent {

public:

  LabSwitch();
  LabSwitch(byte pinSwitch);

  boolean isOn();
  boolean isOff();

  void doEvent();

private:

  byte _pinSwitch;

};

#endif

