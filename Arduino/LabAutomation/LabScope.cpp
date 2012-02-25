#include "LabScope.h"
#include "debug.h"

LabScope::LabScope() {
  _lastEvent = SCOPE_EVENT;
  _lastState = SCOPE_STATE;
  _listenOn = true;
}

void LabScope::checkRx() {
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
    LabCommand commandTx;
    if(commandRx.cmd == SCOPE_STATE) {
      commandTx.cmd = _lastState;
    }
    else {
      commandTx.cmd = SCOPE_EVENT;
    }
    _radioPtr->write(&commandTx, sizeof(commandTx));
#ifdef __DEBUG__
    printf("Tx: %s\n\r", commandTx.getName());
#endif
  }
}

void LabScope::doEvent() {
    switch(_lastEvent) {
      case SCOPE_EVENT_GETTH:
        break;
    }
    _lastEvent = SCOPE_EVENT;
}

void LabScope::setState() {
//  _lastState = getState();
  _lastState = SCOPE_STATE_TH;
  if(!_listenOn) {
    _radioPtr->startListening();
    _listenOn=true;
  }
}

void LabScope::setRadio(RF24 *radioPtr) {
  if (radioPtr!=NULL) {
    _radioPtr=radioPtr;
    _radioPtr->begin();
    _radioPtr->setRetries(15,15);
    _radioPtr->openWritingPipe(pipesDomeScope[1]);
    _radioPtr->openReadingPipe(1,pipesDomeScope[0]);
    _radioPtr->startListening();
  }
}

