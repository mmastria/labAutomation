#ifndef __LAB_COMPONENT__
#define __LAB_COMPONENT__

#include <Arduino.h>

class LabComponent {

public:

  LabComponent();

  void setComponent(LabComponent *componentPtr);
  void callEvent();
  void delay_ms(unsigned int time);
  virtual void doEvent();

private:
  LabComponent *_componentPtr;

};

#endif

