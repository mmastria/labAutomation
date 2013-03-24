#ifndef __LAB_BEEP__
#define __LAB_BEEP__

#include <Arduino.h>
#include "LabDelay.h"

class LabBeep {

public:

  LabBeep(byte pinBeep);
  void play();

private:

  byte _pinBeep;
  LabDelay _delay;

};

#endif

