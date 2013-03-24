#ifndef __LAB_SHUTTER__
#define __LAB_SHUTTER__

#include <Arduino.h>
#include "LabMotor.h"
#include "LabSystem.h"

class LabShutter {

public:

  LabShutter();

  void open();
  void close();
  void stop();
  payload_t getState();
  payload_t getTimer();
  payload_t getSync();
  void fullSync(boolean fullSync);  
  boolean fullSyncOn();

  void setMotor(LabMotor *motorPtr);
  
  
  void timer();  

private:

  payload_t getData();
  LabMotor *_motorPtr;
  boolean _fullSync;

};

#endif

