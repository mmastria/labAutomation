#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include "LabSwitch.h"
#include "LabRelay.h"
#include "LabMotor.h"
#include "LabShutter.h"
//#include "LabBeep.h"

#define SWITCH_OPENED 6
#define SWITCH_CLOSED 7

#define RELAY_OPEN 4
#define RELAY_CLOSE 5

//#define BEEPER 10

RF24 radio(8,9);

LabSwitch switchOpened(SWITCH_OPENED);
LabSwitch switchClosed(SWITCH_CLOSED);
LabRelay relayOpen(RELAY_OPEN);
LabRelay relayClose(RELAY_CLOSE);
LabMotor motor;
LabShutter shutter;
//LabBeep beep(BEEPER);

void switchOpenedEvent() {
  switchOpened.callEvent();
}

void switchClosedEvent() {
  switchClosed.callEvent();
}

void shutterEvent() {
//  beep.play();
  shutter.callEvent();
}

void setupIrq() {
  PCintPort::attachInterrupt(SWITCH_OPENED, switchOpenedEvent, RISING);
  PCintPort::attachInterrupt(SWITCH_CLOSED, switchClosedEvent, RISING);
  attachInterrupt(0, shutterEvent, FALLING);
}

void setup() {
  Serial.begin(57600);
  Serial.println("");
  Serial.println("LabShutterTest");
//  beep.play();

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
//  shutter.doEvent();
}


