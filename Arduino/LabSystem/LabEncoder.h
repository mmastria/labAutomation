#ifndef __LAB_ENCODER__
#define __LAB_ENCODER__

#include <Arduino.h>

class LabEncoder {

  public:

  LabEncoder(byte pinEncoder, long maxValue);

  void reset();
  void add();
  void subtract();
  long getValue();
  long getReached();
  double getValueDeg();

  private:
	
  byte _pinEncoder;
  long _value;
  long _maxValue;
  long _reached;

};

#endif
