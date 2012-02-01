#include "LabEncoder.h"

LabEncoder::LabEncoder() {
  _value=-1;
}

LabEncoder::LabEncoder(byte pinEncoder) {
  _value=-1;
  _pinEncoder = pinEncoder;
  pinMode(_pinEncoder, INPUT);
}

long LabEncoder::getValue() {
  return _value;
}

void LabEncoder::doEvent() {
  if(_value>=0) {
    _value++;
  }
}

void LabEncoder::reset() {
  _value=0;
}
