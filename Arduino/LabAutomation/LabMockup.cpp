#include "LabMockup.h"

LabMockup::LabMockup() {
  _value=0;
}

int LabMockup::getValue() {
  return _value;
}

void LabMockup::doEvent() {
  _value++;
}
