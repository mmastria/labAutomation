#ifndef __LAB_DOME__
#define __LAB_DOME__

#include <Arduino.h>
#include <RF24.h>
#include "LabMotor.h"
#include "LabCommand.h"

const uint64_t pipesDomeShutter[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
const uint64_t pipesDomeScope[2] = { 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL };

// { 0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL, 0xF0F0F0F0A5LL, 0xF0F0F0F096LL };
// { 0x3A3A3A3AD2LL, 0x3A3A3A3AC3LL, 0x3A3A3A3AB4LL, 0x3A3A3A3AA5LL, 0x3A3A3A3A96LL };


class LabDome {
	
  public:
	
  LabDome();

  void right();
  void left();
  void stop();

  void setMotor(LabMotor *motorPtr);
  void setRadio(RF24 *radioPtr);

  command_e checkRx();
  
  void shutterOpen();
  void shutterStop();
  void shutterClose();
  void shutterState();
  
  void getTH();
  
  command_e getState();
  
private:

  LabMotor *_motorPtr;
  RF24 *_radioPtr;
  void sendEventShutter(LabCommand *commandTx, long size);
  void sendEventScope(LabCommand *commandTx, long size);
  void sendEvent(LabCommand *commandTx, long size);

};

#endif
