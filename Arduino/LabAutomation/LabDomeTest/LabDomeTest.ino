#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "LabCommand.h"

// canais de comunicacao
const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL };
RF24 radio(8,9);

LabCommand command;

void setupRadio() {
  radio.begin();
  radio.enableAckPayload();
  radio.openWritingPipe(pipes[0]);
}

void radioEvent() {
  bool tx, fail, rx;
  radio.whatHappened(tx, fail, rx);
  //if (tx) {
  //  Serial.println("Sent OK");
  //}
  //if (fail) {
  //  Serial.println("Sent fail");
  //}
  if (tx || fail) {
    radio.powerDown();
  }
  if (rx) {
    radio.read(&command, sizeof(command));
    //Serial.print("Ack:");
    //Serial.println(command.cmd);
  }
}

void setup()
{
  Serial.begin(57600);
  Serial.println("");
  Serial.println("LabDomeTest");
  
  setupRadio();
  attachInterrupt(0, radioEvent, FALLING);
  delay(2000);  
}

void loop() {

  command.cmd=CMD_OPEN;
  //Serial.println("\nCMD_OPEN");
  radio.startWrite(&command, sizeof(command));
  delay(5000);

  command.cmd=CMD_STOP;
  //Serial.println("\nCMD_STOP");
  radio.startWrite(&command, sizeof(command));
  delay(5000);

  command.cmd=CMD_CLOSE;
  //Serial.println("\nCMD_CLOSE");
  radio.startWrite(&command, sizeof(command));
  delay(5000);

//  command.cmd=CMD_STOP;
//  Serial.println("CMD_STOP");
//  radio.write(&command, sizeof(command));
//  delay(1000);

}

