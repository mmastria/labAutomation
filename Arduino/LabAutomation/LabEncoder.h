#ifndef __LAB_ENCODER__
#define __LAB_ENCODER__

#include <Arduino.h>

class LabEncoder {

  public:

  LabEncoder();
  LabEncoder(byte pinEncoder);

  void reset();
  void add();
  long getValue();

  private:
	
  byte _pinEncoder;
  volatile long _value;

};

#endif
