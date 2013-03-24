#ifndef __LAB_SCOPE__
#define __LAB_SCOPE__

#include <Arduino.h>
#include <dht.h>
#include <stdlib.h>
#include "LabIrSharp.h"
#include "LabSmotor.h"
#include "LabSystem.h"

class LabScope {

public:

  LabScope();

  void setDht(dht *dhtPtr, int dhtPin);
  void setIrSharpLeft(LabIrSharp *irSharpLeftPtr);
  void setIrSharpRight(LabIrSharp *irSharpRightPtr);
  void setSmotor(LabSmotor *sMotorPtr);
  void focusInward();
  void focusOutward();
  void focusStep(int steps);
  payload_t getState();
  payload_t getTimer();
  payload_t getSync();
  void fullSync(boolean fullSync);
  boolean fullSyncOn();
  void timer();

private:

  payload_t getData();
  LabIrSharp *_irSharpLeftPtr;
  LabIrSharp *_irSharpRightPtr;
  LabSmotor *_sMotorPtr;
  dht *_dhtPtr;
  int _dhtPin;
  int _steps;
  int _humidity;
  int _temperature;
  boolean _leftWallHit;
  boolean _rightWallHit;
  boolean _fullSync;
  byte _discards;
  
};
#endif
