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

void LabShutter::doEvent() {
  bool tx, fail, rx;
  _radioPtr->whatHappened(tx, fail, rx);
  if (tx) {
    printf("<tx> Ack Payload Sent (State: %s)\n\r", command.getName());
  }
  if (fail) {
    printf("<fail> Ack Payload Failed to Sent\n\r");
  }
  if (rx) {
    unsigned long started_waiting_at = millis();
    bool timeout = false;
    bool done = false;
    while (!_radioPtr->available() && !timeout) {
      if (millis() - started_waiting_at > 250) {
        timeout = true;
      }
    }
    if (!timeout) {
      while(!done) {
        done = _radioPtr->read( &command, sizeof(command) );
        if (!done) {
          printf("\n\r<rx> Event: %s\n\r", command.getName());
        }
      }
      printf("\n\r<rx> Last Event: %s\n\r", command.getName());
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
//////      _radioPtr->stopListening();
      _radioPtr->writeAckPayload(1, &command, sizeof(command));
//////      _radioPtr->startListening();
    }
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
    _radioPtr->enableAckPayload();
    _radioPtr->openReadingPipe(1,pipes[0]);
    _radioPtr->startListening();
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

