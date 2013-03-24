#include "LabEncoder.h"

LabEncoder::LabEncoder(byte pinEncoder, long maxValue) {
  _value=-1;
  _reached=_value;
  _maxValue=maxValue;
  _pinEncoder = pinEncoder;
  pinMode(_pinEncoder, INPUT);
}

long LabEncoder::getValue() {
  return _value;
}

long LabEncoder::getReached() {
  return _reached;
}

double LabEncoder::getValueDeg() {
  if(_value<0)
    return -1.0;
  else
// modified - using max reached  
//    return ((_value * 360.0) / _maxValue);
    return ((_value * 360.0) / (_reached>_maxValue ? _reached : _maxValue));
}

void LabEncoder::add() {
  if(_value>=0) {
    _value++;
    if(_value>_reached)
      _reached=_value;
// removed to obtain max reached
// reset only by home sensor
//    if(_value>_maxValue) {
//      _value=0;
//    }
  }
}

void LabEncoder::subtract() {
  if(_value>0) {
    _value--;
  }
  else {
// modified - using max reached
//    _value=_maxValue;
    _value=(_reached>_maxValue ? _reached : _maxValue);
  }
}

void LabEncoder::reset() {
  _value=0;
}
