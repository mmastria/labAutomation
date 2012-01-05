#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include "LabSwitch.h"
#include "LabRelay.h"
#include "LabMotor.h"
#include "LabShutter.h"

#define SWITCH_OPENED 6
#define SWITCH_CLOSED 7

#define RELAY_OPEN 4
#define RELAY_CLOSE 5

RF24 radio(8,9);

LabSwitch switchOpened(SWITCH_OPENED);
LabSwitch switchClosed(SWITCH_CLOSED);
LabRelay relayOpen(RELAY_OPEN);
LabRelay relayClose(RELAY_CLOSE);
LabMotor motor;
LabShutter shutter;

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
  shutter.setRadio(&radio);

  setupIrq();

  delay(2000);
}


void loop() {
  shutter.doEvent();
}


