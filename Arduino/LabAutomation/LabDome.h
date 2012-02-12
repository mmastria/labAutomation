#ifndef __LAB_DOME__
#define __LAB_DOME__

#include <Arduino.h>
#include <RF24.h>
#include "LabComponent.h"
#include "LabCommand.h"

const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL };

class LabDome : public LabComponent {
	
  public:
	
   LabDome();
   
   void doEvent();
   void doTest();
   
   void setRadio(RF24 *radioPtr);
   
private:

  LabCommand command;
  RF24 *_radioPtr;

};

#endif
