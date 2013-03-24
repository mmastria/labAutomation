#include "LabScope.h"
#ifdef __SCOPE__

LabScope::LabScope() {
  _temperature=0;
  _humidity=0;
  _leftWallHit=false;
  _rightWallHit=false;
  _steps=1;
  _fullSync=false;
  _discards=TEMPERATURE_MAX_DISCARDS;
}

void LabScope::timer() {
  int temperature;
  int humidity;
  if(_dhtPtr->read22(_dhtPin)==0) {
    humidity=_dhtPtr->humidity;
    temperature=_dhtPtr->temperature*10;
    if(humidity>0 and humidity<=100)
      _humidity=humidity;
    if((abs(_temperature-temperature)>(TEMPERATURE_MAX_DEV*10)) and _discards<TEMPERATURE_MAX_DISCARDS) {
      _discards++;
    }
    else {
      _discards=0;
      _temperature=temperature;
    }
  }
  _leftWallHit=_irSharpLeftPtr->isWallHit(); // WallLeft
  _rightWallHit=_irSharpRightPtr->isWallHit(); // WallRight
}

void LabScope::setIrSharpLeft(LabIrSharp *irSharpLeftPtr) {
  _irSharpLeftPtr=irSharpLeftPtr;
}

void LabScope::setIrSharpRight(LabIrSharp *irSharpRightPtr) {
  _irSharpRightPtr=irSharpRightPtr;
}

void LabScope::setSmotor(LabSmotor *sMotorPtr) {
  _sMotorPtr=sMotorPtr;
}

void LabScope::setDht(dht *dhtPtr, int dhtPin) {
  _dhtPtr=dhtPtr;
  _dhtPin=dhtPin;
}

payload_t LabScope::getState() {
  #ifdef __DEBUG__
  Serial.println("getState");
  #endif
  payload_t payload;
  payload=getData();
  payload.action=SCOPE_RETURNSTATE;
  return payload;
}

payload_t LabScope::getTimer() {
  #ifdef __DEBUG__
  Serial.println("getTimer");
  #endif
  payload_t payload;
  payload=getData();
  payload.action=SCOPE_TIMER;
  return payload;
}

payload_t LabScope::getSync() {
  #ifdef __DEBUG__
  Serial.println("getSync");
  #endif
  payload_t payload;
  payload=getData();
  payload.action=SCOPE_SYNC;
  return payload;
}

payload_t LabScope::getData() {
  payload_t r;
  r.b1=_leftWallHit; // WallLeft
  r.b2=_rightWallHit; // WallRight
  r.b3=_steps; // Steps
  r.b4=_humidity; // humidity
  r.i1=_temperature; // temperature
  return r;
}

void LabScope::focusInward() {
  #ifdef __DEBUG__
  Serial.println("focusInward");
  #endif
  _sMotorPtr->enable();
  _sMotorPtr->rotate(_steps, .01);
  _sMotorPtr->disable();
}

void LabScope::focusOutward() {
  #ifdef __DEBUG__
  Serial.println("focusOutward");
  #endif
  _sMotorPtr->enable();
  _sMotorPtr->rotate((-1*_steps), .01);
  _sMotorPtr->disable();
}

void LabScope::focusStep(int steps) {
  #ifdef __DEBUG__
  Serial.println("focusStep");
  #endif
  _steps=steps;
}

void LabScope::fullSync(boolean fullSync) {
  _fullSync=fullSync;
}

boolean LabScope::fullSyncOn() {
  return _fullSync;
}

#endif
