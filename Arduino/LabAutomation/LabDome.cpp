#include "LabDome.h"

LabDome::LabDome() {
}

void LabDome::doEvent() {
  bool tx, fail, rx;
  _radioPtr->whatHappened(tx, fail, rx);
  if (tx)  {
    Serial.println("< tx - Ack Payload Sent");
  }
  if (fail) {
    Serial.println("< fail - Ack Payload Failed to Sent");
  }
  if (rx) {
    _radioPtr->read( &command, sizeof(command) );
    Serial.print("> Event: ");
    Serial.println(command.getName());
    Serial.println("");
//    switch(command.cmd) {
//      case CMD_STOP:
//        stop();
//        break;
//    }
//    _radioPtr->writeAckPayload(1, &command, sizeof(command));
  }
}

void LabDome::setRadio(RF24 *radioPtr) {
  if (radioPtr!=NULL) {
    _radioPtr=radioPtr;
    _radioPtr->begin();
    _radioPtr->enableAckPayload();
    _radioPtr->openReadingPipe(1,pipes[0]);
    _radioPtr->startListening();
  }
}

void LabDome::doTest() {

  command.cmd=SHUTTER_EVENT_OPEN;
  Serial.print("> Call: ");
  Serial.println(command.getName());
  _radioPtr->startWrite(&command, sizeof(command));
  delay(2000);

  command.cmd=SHUTTER_EVENT_STOP;
  Serial.print("> Call: ");
  Serial.println(command.getName());
  _radioPtr->startWrite(&command, sizeof(command));
  delay(2000);

  command.cmd=SHUTTER_EVENT_CLOSE;
  Serial.print("> Call: ");
  Serial.println(command.getName());
  _radioPtr->startWrite(&command, sizeof(command));
  delay(2000);

  command.cmd=SHUTTER_EVENT_STOP;
  Serial.print("> Call: ");
  Serial.println(command.getName());
  _radioPtr->startWrite(&command, sizeof(command));
  delay(2000);

}


//------------------------




//void setupRadio() {
//  radio.begin();
//  radio.enableAckPayload();
//  radio.openWritingPipe(pipes[0]);
//}

//void radioEvent() {
//  bool tx, fail, rx;
//  radio.whatHappened(tx, fail, rx);
//  //if (tx) {
//  //  Serial.println("Sent OK");
//  //}
//  //if (fail) {
//  //  Serial.println("Sent fail");
//  //}
//  if (tx || fail) {
//    radio.powerDown();
//  }
//  if (rx) {
//    radio.read(&command, sizeof(command));
//    //Serial.print("Ack:");
//    //Serial.println(command.cmd);
//  }
//}


//  command.cmd=CMD_OPEN;
//  //Serial.println("\nCMD_OPEN");
//  radio.startWrite(&command, sizeof(command));
//  delay(5000);

//  command.cmd=CMD_STOP;
//  //Serial.println("\nCMD_STOP");
//  radio.startWrite(&command, sizeof(command));
//  delay(5000);

//  command.cmd=CMD_CLOSE;
//  //Serial.println("\nCMD_CLOSE");
//  radio.startWrite(&command, sizeof(command));
//  delay(5000);

//  command.cmd=CMD_STOP;
//  Serial.println("CMD_STOP");
//  radio.write(&command, sizeof(command));
//  delay(1000);

