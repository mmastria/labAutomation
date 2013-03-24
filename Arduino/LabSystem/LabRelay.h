#ifndef __LAB_RELAY__
#define __LAB_RELAY__

#include <Arduino.h>

class LabRelay {

public:

  LabRelay(byte pinRelay);

  void on();
  void off();

  boolean isOn();
  boolean isOff();

private:

  byte _pinRelay;
  boolean _state;

};

#endif

