#include "LabDome.h"

LabDome::LabDome() {
}

void LabDome::checkRx() {
  unsigned long started_waiting_at = millis();
  bool timeout = false;
  while (!_radioPtr->available() && ! timeout )
    if (millis() - started_waiting_at > 2000 )
      timeout = true;
  if ( timeout ) {
    printf("Failed, response timed out.\n\r");
  }
  else {
    _radioPtr->read( &command, sizeof(command) );
    printf("Got response %s\n\r", command.getName());
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
    _radioPtr->printDetails();
  }
}

void LabDome::sendEvent() {
  printf("\n\r> Call: %s\n\r", command.getName());
  _radioPtr->stopListening();
  _radioPtr->write(&command, sizeof(command));
  _radioPtr->startListening();
}

void LabDome::shutterOpen() {
  command.cmd=SHUTTER_EVENT_OPEN;
  sendEvent();
}

void LabDome::shutterStop() {
  command.cmd=SHUTTER_EVENT_STOP;
  sendEvent();
}

void LabDome::shutterClose() {
  command.cmd=SHUTTER_EVENT_CLOSE;
  sendEvent();
}

void LabDome::shutterState() {
  command.cmd=SHUTTER_STATE;
  sendEvent();
}

