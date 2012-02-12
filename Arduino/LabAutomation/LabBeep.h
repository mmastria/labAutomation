#ifndef __LAB_BEEP__
#define __LAB_BEEP__

#include <Arduino.h>

class LabBeep {

public:

  LabBeep();
  LabBeep(byte pinBeep);

  void play();

private:

  void delay_ms(unsigned int time);
  byte _pinBeep;

};

#endif

