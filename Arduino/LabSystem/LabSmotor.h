#ifndef __LAB_SMOTOR__
#define __LAB_SMOTOR__

#include <Arduino.h>

class LabSmotor {

public:

  LabSmotor(byte pinDir, byte pinStep, byte pinEnable);
  void rotate(int steps, float speed);
  void rotateDeg(float deg, float speed);
  void enable();
  void disable();

private:

  byte _pinDir;
  byte _pinStep;
  byte _pinEnable;

};

#endif

