#ifndef __LAB_DOME__
#define __LAB_DOME__

#include <Arduino.h>
#include "LabMotor.h"
#include "LabEncoder.h"
#include "LabSystem.h"

class LabDome {
	
public:
	
  LabDome();

  void right();
  void left();
  void stop();
  void home();
  void change();
  payload_t getState();
  payload_t getTimer();
  void fullSync(boolean fullSync);  
  boolean fullSyncOn();
  void scopeSync(payload_t payload);
  void shutterSync(payload_t payload);

  void setMotor(LabMotor *motorPtr);
  void setEncoder(LabEncoder *encoderPtr);
  void setSwitchHome(LabSwitch *switchHomePtr);
  void setSwitch220v(LabSwitch *switch220vPtr);
  
  boolean checkDelay();
  void startDelay();
  
  void timer();
  void checkSync();

  
private:

  payload_t getData();
  LabMotor *_motorPtr;
  LabEncoder *_encoderPtr;
  LabSwitch *_switchHomePtr;
  LabSwitch *_switch220vPtr;
  boolean _fullSync;
  boolean _leftHit;
  boolean _leftHited;
  boolean _rightHit;
  boolean _rightHited;
  boolean _lastTurnLeft;
  boolean _closed;
  boolean _opened;

};

#endif
