#include "LabDome.h"

LabDome::LabDome() {
}

void LabDome::doEvent() {
  bool tx, fail, rx;
  _radioPtr->whatHappened(tx, fail, rx);
  if (tx)  {
    printf("< tx - Ack Payload Sent\n\r");
  }
  if (fail) {
    printf("< fail - Ack Payload Failed to Sent\n\r");
  }
  if (rx) {
    _radioPtr->read( &command, sizeof(command) );
    printf("> Event: %s\n\r", command.getName());
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
  printf("> Call: %s\n\r", command.getName());
  _radioPtr->startWrite(&command, sizeof(command));
  delay_ms(4000);

  command.cmd=SHUTTER_EVENT_STOP;
  printf("> Call: %s\n\r", command.getName());
  _radioPtr->startWrite(&command, sizeof(command));
  delay_ms(4000);

  command.cmd=SHUTTER_EVENT_CLOSE;
  printf("> Call: %s\n\r", command.getName());
  _radioPtr->startWrite(&command, sizeof(command));
  delay_ms(4000);

  command.cmd=SHUTTER_STATE;
  printf("> Call: %s\n\r", command.getName());
  _radioPtr->startWrite(&command, sizeof(command));
  delay_ms(4000);

  command.cmd=SHUTTER_EVENT_STOP;
  printf("> Call: %s\n\r", command.getName());
  _radioPtr->startWrite(&command, sizeof(command));
  delay_ms(4000);

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

