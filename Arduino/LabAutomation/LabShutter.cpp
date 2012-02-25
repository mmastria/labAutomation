#include "LabShutter.h"
#include "debug.h"

LabShutter::LabShutter() {
  _lastEvent = SHUTTER_EVENT;
  _lastState = SHUTTER_STATE;
  _listenOn = true;
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
#ifdef __DEBUG__
    printf("---------------------\n\r");
#endif
    LabCommand commandRx;
    _radioPtr->read( &commandRx, sizeof(commandRx) );
    _radioPtr->stopListening();
    _listenOn = false;
#ifdef __DEBUG__
    printf("Rx: %s\n\r", commandRx.getName());
#endif
    _lastEvent = commandRx.cmd;
    _beepPtr->play();
    LabCommand commandTx;
    if(commandRx.cmd == SHUTTER_STATE) {
      commandTx.cmd = _lastState;
    }
    else {
      commandTx.cmd = SHUTTER_EVENT;
    }
    _radioPtr->write(&commandTx, sizeof(commandTx));
#ifdef __DEBUG__
    printf("Tx: %s\n\r", commandTx.getName());
#endif
  }
}

void LabShutter::doEvent() {
    switch(_lastEvent) {
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
    _lastEvent = SHUTTER_EVENT;
}

void LabShutter::setState() {
  _lastState = getState();
  if(!_listenOn) {
    _radioPtr->startListening();
    _listenOn=true;
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
    _radioPtr->setRetries(15,15);
    _radioPtr->openWritingPipe(pipesDomeShutter[1]);
    _radioPtr->openReadingPipe(1,pipesDomeShutter[0]);
    _radioPtr->startListening();
  }
}

void LabShutter::setBeeper(LabBeep *beepPtr) {
  if (beepPtr!=NULL) {
    _beepPtr=beepPtr;
  }
}

command_e LabShutter::getState() {
  int state = 0;
  command_e r = SHUTTER_STATE_ERROR;
  if(_motorPtr->isOff()) state += 1;
  if(_motorPtr->isForward()) state += 2;
  if(_motorPtr->isReverse()) state += 4;
  if(_motorPtr->isSwitchForwardOn()) state += 8;
  if(_motorPtr->isSwitchReverseOn()) state += 16;
  switch(state) {
    case 1: // isOff=1  isForward=0  isReverse=0  isSwitchForwardOn=0  isSwitchReverseOn=0
      r = SHUTTER_STATE_SEMIOPENED;
      break;
    case 2: // isOff=0  isForward=1  isReverse=0  isSwitchForwardOn=0  isSwitchReverseOn=0
      r = SHUTTER_STATE_OPENING;
      break;
    case 4: // isOff=0  isForward=0  isReverse=1  isSwitchForwardOn=0  isSwitchReverseOn=0
      r = SHUTTER_STATE_CLOSING;
      break;
    case 9: // isOff=1  isForward=0  isReverse=0  isSwitchForwardOn=1  isSwitchReverseOn=0
      r = SHUTTER_STATE_OPENED;
      break;
    case 17: // isOff=1  isForward=0  isReverse=0  isSwitchForwardOn=0  isSwitchReverseOn=1
      r = SHUTTER_STATE_CLOSED;
      break;
    default:
      r = SHUTTER_STATE_ERROR;
  }
  return r;
}

