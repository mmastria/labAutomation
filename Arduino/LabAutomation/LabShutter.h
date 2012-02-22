#ifndef __LAB_SHUTTER__
#define __LAB_SHUTTER__

#include <Arduino.h>
#include <RF24.h>
#include "LabSwitch.h"
#include "LabRelay.h"
#include "LabMotor.h"
#include "LabBeep.h"
#include "LabCommand.h"

const uint64_t pipes[4] = { 
  0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL };

class LabShutter {

public:

  LabShutter();

  void open();
  void close();
  void stop();

  void checkRx();
  void doEvent();
  void setState();

  void setMotor(LabMotor *motorPtr);
  void setRadio(RF24 *radioPtr);
  void setBeeper(LabBeep *beepPtr);

private:

  command_e getState();
  LabMotor *_motorPtr;
  RF24 *_radioPtr;
  LabBeep *_beepPtr;
  volatile command_e _lastEvent;
  volatile command_e _lastState;
  volatile boolean _listenOn;

};

#endif

