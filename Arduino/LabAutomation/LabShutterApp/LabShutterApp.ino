#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include "LabSwitch.h"
#include "LabRelay.h"
#include "LabMotor.h"
#include "LabShutter.h"
#include "printf.h"

//              0
//              1
//RF24-IRQ      2
//              3
//RELAY_OPEN    4
//RELAY_CLOSE   5
//SWITCH_OPENED 6
//SWITCH_CLOSED 7
//RF24-CE       8
//RF24-CSN      9
//             10
//RF24-MOSI    11
//RF24-MISO    12
//RF24-SCK     13

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

void switchOpenedEvent() {
  switchOpened.callEvent();
}

void switchClosedEvent() {
  switchClosed.callEvent();
}

void setupIrq() {
  PCintPort::attachInterrupt(SWITCH_OPENED, switchOpenedEvent, RISING);
  PCintPort::attachInterrupt(SWITCH_CLOSED, switchClosedEvent, RISING);
}

void setup() {
  Serial.begin(57600);
  printf_begin();
  printf("\n\rLabShutterApp\n\r");
  printf("release 0.3 - 2012-feb-20\n\r");
  printf("serial log 57600,n,8,1,p\n\r\n\r");

  switchOpened.setComponent(&relayOpen);
  switchClosed.setComponent(&relayClose);

  motor.setSwitchForward(&switchOpened);
  motor.setSwitchReverse(&switchClosed);
  motor.setRelayForward(&relayOpen);
  motor.setRelayReverse(&relayClose);

  shutter.setMotor(&motor);
  shutter.setRadio(&radio);

  setupIrq();

  printf("> setup OK; ready!\n\r\n\r");

  delay(2000);
}


void loop() {
  shutter.checkRx();
}

