#include "LabDome.h"

LabDome::LabDome() {
}

void LabDome::right() {
  _motorPtr->forward();
}

void LabDome::left() {
  _motorPtr->reverse();
}

void LabDome::stop() {
  _motorPtr->off();
}

command_e LabDome::checkRx() {
  command_e r = DOME_STATE_ERROR;  
  unsigned long started_waiting_at = millis();
  bool timeout = false;
  while (!_radioPtr->available() && ! timeout )
    if (millis() - started_waiting_at > 3000 )
      timeout = true;
  if ( !timeout ) {
    LabCommand commandRx;
    _radioPtr->read( &commandRx, sizeof(commandRx) );
    r = commandRx.cmd;
  }
  return r;
}

void LabDome::setMotor(LabMotor *motorPtr) {
  if (motorPtr!=NULL) {
    _motorPtr=motorPtr;
  }
}

void LabDome::setRadio(RF24 *radioPtr) {
  if (radioPtr!=NULL) {
    _radioPtr=radioPtr;
    _radioPtr->begin();
    _radioPtr->setRetries(15,15);
    _radioPtr->openWritingPipe(pipes[0]);
    _radioPtr->openReadingPipe(1,pipes[1]);
    _radioPtr->startListening();
  }
}

void LabDome::sendEvent(LabCommand *commandTx, long size) {
  _radioPtr->stopListening();
  _radioPtr->write(commandTx, size);
  _radioPtr->startListening();
}

void LabDome::shutterOpen() {
  LabCommand commandTx;
  commandTx.cmd=SHUTTER_EVENT_OPEN;
  sendEvent(&commandTx, sizeof(commandTx));
}

void LabDome::shutterStop() {
  LabCommand commandTx;
  commandTx.cmd=SHUTTER_EVENT_STOP;
  sendEvent(&commandTx, sizeof(commandTx));
}

void LabDome::shutterClose() {
  LabCommand commandTx;
  commandTx.cmd=SHUTTER_EVENT_CLOSE;
  sendEvent(&commandTx, sizeof(commandTx));
}

void LabDome::shutterState() {
  LabCommand commandTx;
  commandTx.cmd=SHUTTER_STATE;
  sendEvent(&commandTx, sizeof(commandTx));
}

command_e LabDome::getState() {
  int state = 0;
  command_e r = DOME_STATE_ERROR;
  if(_motorPtr->isOff()) state += 1;
  if(_motorPtr->isForward()) state += 2;
  if(_motorPtr->isReverse()) state += 4;
  switch(state) {
    case 1: // isOff=1  isForward=0  isReverse=0
      r = DOME_STATE_STOPPED;
      break;
    case 2: // isOff=0  isForward=1  isReverse=0
      r = DOME_STATE_RIGHT;
      break;
    case 4: // isOff=0  isForward=0  isReverse=1
      r = DOME_STATE_LEFT;
      break;
    default:
      r = DOME_STATE_ERROR;
  }
  return r;
}

