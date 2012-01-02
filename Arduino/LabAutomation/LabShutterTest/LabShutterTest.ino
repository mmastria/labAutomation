#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include "LabSwitch.h"
#include "LabRelay.h"
#include "LabMotor.h"
#include "LabShutter.h"

#define RELAY_OPEN 4
#define RELAY_CLOSE 5

#define SWITCH_OPENED 6
#define SWITCH_CLOSED 7

// canais de comunicacao
const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL };

RF24 radio(8,9);

LabRelay relayOpen(RELAY_OPEN);
LabRelay relayClose(RELAY_CLOSE);

LabSwitch switchOpened(SWITCH_OPENED);
LabSwitch switchClosed(SWITCH_CLOSED);

LabShutter shutter(relayOpen, relayClose, switchOpened, switchClosed);

void setup() {
  Serial.begin(57600);
  switchesIrqSetup();
  radioSetup();
  delay(500);
}

void loop() {
  while( !radio.available() );
  radio.read( &shutter, sizeof(shutter) );
  shutter.doEvent();
}

void eventOpen() {
  if(switchOpened.isOn()) {
    switchOpened.event();
  }
}

void eventClose() {
  if(switchClosed.isOn()) {
    switchClosed.event();
  }
}

void switchesIrqSetup() {
  PCintPort::attachInterrupt(SWITCH_OPENED, eventOpen, RISING);
  PCintPort::attachInterrupt(SWITCH_CLOSED, eventClose, RISING);
}

void radioSetup() {
  radio.begin();
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening();
}

