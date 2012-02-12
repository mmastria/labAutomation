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
  //if (tx)   Ack Payload Sent
  //if (fail) Ack Payload Failed to Sent
  if (rx) {
    _radioPtr->read( &command, sizeof(command) );
    Serial.print("> Event: ");
    Serial.println(command.getName());
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
      // any other, only return state
    }
    command.cmd = getState();
    Serial.print("> State: ");
    Serial.println(command.getName());
    Serial.println("");
    _radioPtr->writeAckPayload(1, &command, sizeof(command));
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
  return SHUTTER_STATE_UNKNOWN;
}  

