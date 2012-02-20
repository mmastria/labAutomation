#include "LabShutter.h"

LabShutter::LabShutter() {
}

void LabShutter::open() {
  _motorPtr->forward();
}

void LabShutter::close() {
  _motorPtr->reverse();
}

void LabShutter::stop() {
  _motorPtr->off();
}

void LabShutter::checkRx() {
  if (_radioPtr->available()) {
    printf("---------------------\n\r");
    bool done = false;
    while (!done) {
      done = _radioPtr->read( &command, sizeof(command) );
      if (!done) {
        printf("Rx: %s\n\r", command.getName());
      }
    }
    printf("Rx End: %s\n\r", command.getName());
    switch(command.cmd) {
    case SHUTTER_EVENT_STOP:
      stop();
      break;
    case SHUTTER_EVENT_OPEN:
      open();
      break;
    case SHUTTER_EVENT_CLOSE:
      close();
      break;
    }
    delay_ms(50);  
    command.cmd = getState();
    _radioPtr->stopListening();
    _radioPtr->write(&command, sizeof(command));
    printf("Tx: %s\n\r", command.getName());
    _radioPtr->startListening();
  }
}

void LabShutter::setMotor(LabMotor *motorPtr) {
  if (motorPtr!=NULL) {
    _motorPtr=motorPtr;
  }
}

void LabShutter::setRadio(RF24 *radioPtr) {
  if (radioPtr!=NULL) {
    _radioPtr=radioPtr;
    _radioPtr->begin();
    //_radioPtr->enablePayloads();
    _radioPtr->setRetries(15,15);
    _radioPtr->openWritingPipe(pipes[1]);
    _radioPtr->openReadingPipe(1,pipes[0]);
    _radioPtr->startListening();
    _radioPtr->printDetails();
  }
}

command_e LabShutter::getState() {
  if (_motorPtr->isSwitchReverseOn() && _motorPtr->isOff()) {
    return SHUTTER_STATE_CLOSED;
  }
  if (_motorPtr->isSwitchForwardOn() && _motorPtr->isOff()) {
    return SHUTTER_STATE_OPENED;
  }
  if (_motorPtr->isReverse()) {
    return SHUTTER_STATE_CLOSING;
  }
  if (_motorPtr->isForward()) {
    return SHUTTER_STATE_OPENING;
  }
  if (!_motorPtr->isSwitchReverseOn() && !_motorPtr->isSwitchForwardOn() && _motorPtr->isOff()) {
    return SHUTTER_STATE_SEMIOPENED;
  }
  return SHUTTER_STATE_ERROR;
}  

