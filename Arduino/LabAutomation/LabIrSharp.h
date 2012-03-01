#ifndef __LAB_IRSHARP__
#define __LAB_IRSHARP__

#include <Arduino.h>
#include "LabDelay.h"

class LabIrSharp {

public:

  LabIrSharp();
  LabIrSharp(byte pinIrSharp);
  
  void setReference(int reference);
  boolean isWallHit();
  boolean isActive();
  
  void activate();
  void deactivate();
  
private:

  byte _pinIrSharp;
  int  _reference;
  LabDelay _delay; 
  boolean _active;

};

#endif

