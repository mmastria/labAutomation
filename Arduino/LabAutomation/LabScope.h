#ifndef __LAB_SCOPE__
#define __LAB_SCOPE__

#include <Arduino.h>
#include <RF24.h>
#include "LabCommand.h"

const uint64_t pipesDomeScope[2] = { 
  0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL };

class LabScope {

public:

  LabScope();

  void checkRx();
  void doEvent();
  void setState();

  void setRadio(RF24 *radioPtr);

private:

  RF24 *_radioPtr;
  volatile command_e _lastEvent;
  volatile command_e _lastState;
  volatile boolean _listenOn;  

};
#endif


