#ifndef __LAB_SCOPE__
#define __LAB_SCOPE__

#include <Arduino.h>
#include <RF24.h>
#include <dht.h>
#include <stdlib.h>
#include "LabCommand.h"
#include "LabDelay.h"

const uint64_t pipesDomeScope[2] = { 
  0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL };

class LabScope {

public:

  LabScope();

  void checkRx();
  void setState();

  void setRadio(RF24 *radioPtr);
  void setDht(dht *dhtPtr, int dhtPin);

private:

  RF24 *_radioPtr;
  dht *_dhtPtr;
  int _dhtPin;
  volatile boolean _listenOn; 
  volatile double _temperature;
  volatile double _humidity;
  LabDelay _delay;
  
};
#endif


