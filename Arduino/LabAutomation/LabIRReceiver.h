#ifndef __LAB_IRRECEIVER__
#define __LAB_IRRECEIVER__

#include <Arduino.h>
#include <IRremote.h>
//#include <IRremoteInt.h>
#include "LabComponent.h"

class LabIRReceiver : public LabComponent {

  public:

  LabIRReceiver();
  LabIRReceiver(byte pinIRReceiver);
  boolean decode();

  private:
	
  void translateIR();
  byte _pinIRReceiver;
  IRrecv *_irrecv;
  decode_results results;

};

#endif
