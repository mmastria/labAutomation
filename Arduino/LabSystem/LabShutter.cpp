#include "LabShutter.h"
#ifdef __SHUTTER__

LabShutter::LabShutter() {
  _fullSync=false;
}

void LabShutter::open() {
  #ifdef __DEBUG__
  Serial.println("open");
  #endif
  _motorPtr->forward();
}

void LabShutter::close() {
  #ifdef __DEBUG__
  Serial.println("close");
  #endif
  _motorPtr->reverse();
}

void LabShutter::stop() {
  #ifdef __DEBUG__
  Serial.println("stop");
  #endif
  _motorPtr->off();
}

void LabShutter::setMotor(LabMotor *motorPtr) {
  _motorPtr=motorPtr;
}

void LabShutter::timer() {
}

payload_t LabShutter::getState() {
  #ifdef __DEBUG__
  Serial.println("getState");
  #endif
  payload_t payload;
  payload=getData();
  payload.action=SHUTTER_RETURNSTATE;
  return payload;
}

payload_t LabShutter::getTimer() {
  #ifdef __DEBUG__
  Serial.println("getTimer");
  #endif
  payload_t payload;
  payload=getData();
  payload.action=SHUTTER_TIMER;
  return payload;
}

payload_t LabShutter::getSync() {
  payload_t payload;
  payload=getData();
  payload.action=SHUTTER_SYNC;
  return payload;
}

payload_t LabShutter::getData() {
  payload_t r;
  r.b1=_motorPtr->isForward();         // Opening
  r.b2=_motorPtr->isReverse();         // Closing
  r.b3=_motorPtr->isSwitchForwardOn(); // Opened
  r.b4=_motorPtr->isSwitchReverseOn(); // Closed
  return r;
}

void LabShutter::fullSync(boolean fullSync) {
  _fullSync=fullSync;
}

boolean LabShutter::fullSyncOn() {
  return _fullSync;
}

#endif
