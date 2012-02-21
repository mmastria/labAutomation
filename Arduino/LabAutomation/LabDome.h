#ifndef __LAB_DOME__
#define __LAB_DOME__

#include <Arduino.h>
#include <RF24.h>
#include "LabComponent.h"
#include "LabMotor.h"
#include "LabCommand.h"

const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL };

class LabDome : public LabComponent {
	
  public:
	
  LabDome();

  void right();
  void left();
  void stop();

  void setMotor(LabMotor *motorPtr);
  void setRadio(RF24 *radioPtr);

  void checkRx();
  void shutterOpen();
  void shutterStop();
  void shutterClose();
  void shutterState();
  
  command_e getState();
  
private:

  LabMotor *_motorPtr;
  LabCommand command;
  RF24 *_radioPtr;
  void sendEvent();

};

#endif
