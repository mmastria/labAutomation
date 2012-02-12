#ifndef __LAB_SHUTTER__
#define __LAB_SHUTTER__

#include <Arduino.h>
#include <RF24.h>
#include "LabComponent.h"
#include "LabSwitch.h"
#include "LabRelay.h"
#include "LabMotor.h"
#include "LabCommand.h"

const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL };

class LabShutter : public LabComponent {
	
  public:
	
   LabShutter();
   
   void open();
   void close();
   void stop();
   
   void doEvent();
   
   void setMotor(LabMotor *motorPtr);
   void setRadio(RF24 *radioPtr);
   
   command_e getState();
	
private:

  LabMotor *_motorPtr;
  LabCommand command;
  RF24 *_radioPtr;

};

#endif
