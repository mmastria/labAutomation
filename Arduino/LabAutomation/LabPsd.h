#ifndef __LAB_PSD__
#define __LAB_PSD__

#include <Arduino.h>
#include "LabDelay.h"

class LabPsd {

public:

  LabPsd();
  LabPsd(byte pinPsd);
  
  void setReference(int reference);
  boolean isWallHit();
  
private:

  byte _pinPsd;
  int  _reference;
  LabDelay _delay;  

};

#endif

