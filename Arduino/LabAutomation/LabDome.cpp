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

void LabDome::setIRReceiver(LabIRReceiver *irReceiverPtr) {
  if (irReceiverPtr!=NULL) {
    _irReceiverPtr=irReceiverPtr;
  }
}

void LabDome::doTest(int i) {
  switch(i) {
    case 1: command.cmd=SHUTTER_EVENT_OPEN; break;     // Opening, Opened
    case 2: command.cmd=SHUTTER_STATE; break;
    case 3: command.cmd=SHUTTER_EVENT_STOP; break;     // Semi-Opened, Opened, Closed
    case 4: command.cmd=SHUTTER_STATE; break;
    case 5: command.cmd=SHUTTER_EVENT_CLOSE; break;    // Closing, Closed
    case 6: command.cmd=SHUTTER_STATE; break;
    case 7: command.cmd=SHUTTER_EVENT_STOP; break;     // Semi-Opened, Closed, Opened
    case 8: command.cmd=SHUTTER_STATE; break;
  }
  printf("\n\r> Call: %s\n\r", command.getName());
  _radioPtr->stopListening();
  _radioPtr->write(&command, sizeof(command));
  _radioPtr->startListening();
}

