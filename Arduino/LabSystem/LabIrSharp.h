#ifndef __LAB_IRSHARP__
#define __LAB_IRSHARP__

#include <Arduino.h>

class LabIrSharp {

public:

  LabIrSharp(byte pinIrSharp, int reference);
  boolean isWallHit();
  boolean isActive();
  
private:

  byte _pinIrSharp;
  int  _reference;

};

#endif

