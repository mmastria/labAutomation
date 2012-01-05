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
  radio.openWritingPipe(pipes[0]);
}

void setup()
{
  Serial.begin(57600);
  Serial.println("");
  Serial.println("LabDomeTest");
  
  setupRadio();
  delay(2000);  
}

void loop() {

  command.cmd=CMD_OPEN;
  Serial.println("CMD_OPEN");
  radio.write(&command, sizeof(command));
  delay(3000);

  command.cmd=CMD_STOP;
  Serial.println("CMD_STOP");
  radio.write(&command, sizeof(command));
  delay(1000);

  command.cmd=CMD_CLOSE;
  Serial.println("CMD_CLOSE");
  radio.write(&command, sizeof(command));
  delay(3000);

//  command.cmd=CMD_STOP;
//  Serial.println("CMD_STOP");
//  radio.write(&command, sizeof(command));
//  delay(1000);

}

