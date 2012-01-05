#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include "LabSwitch.h"
#include "LabRelay.h"
#include "LabMotor.h"
#include "LabShutter.h"
#include "LabCommand.h"

#define SWITCH_OPENED 6
#define SWITCH_CLOSED 7

#define RELAY_OPEN 4
#define RELAY_CLOSE 5

const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL };
RF24 radio(8,9);

LabSwitch switchOpened(SWITCH_OPENED);
LabSwitch switchClosed(SWITCH_CLOSED);
LabRelay relayOpen(RELAY_OPEN);
LabRelay relayClose(RELAY_CLOSE);
LabMotor motor;
LabShutter shutter;
LabCommand command;

void setupIrq() {
  PCintPort::attachInterrupt(SWITCH_OPENED, eventSwitchOpened, RISING);
  PCintPort::attachInterrupt(SWITCH_CLOSED, eventSwitchClosed, RISING);
}

void eventSwitchOpened() {
  switchOpened.callEvent();
}

void eventSwitchClosed() {
  switchClosed.callEvent();
}

void setupRadio() {
  radio.begin();
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening();
}

void setup() {
  Serial.begin(57600);
  Serial.println("");
  Serial.println("LabShutterTest");

  switchOpened.setComponent(&relayOpen);
  switchClosed.setComponent(&relayClose);

  motor.setSwitchForward(&switchOpened);
  motor.setSwitchReverse(&switchClosed);
  motor.setRelayForward(&relayOpen);
  motor.setRelayReverse(&relayClose);

  shutter.setMotor(&motor);

  setupIrq();
  setupRadio();

  delay(2000);
}


void loop() {
  while( !radio.available() );
  radio.read( &command, sizeof(command) );
  switch(command.cmd) {
    case CMD_STOP:
      shutter.stop();
      break;
    case CMD_OPEN:
      shutter.open();
      break;
    case CMD_CLOSE:
      shutter.close();
      break;
  }
}



