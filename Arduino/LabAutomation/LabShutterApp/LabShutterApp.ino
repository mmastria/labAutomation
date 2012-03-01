#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include "LabSwitch.h"
#include "LabRelay.h"
#include "LabMotor.h"
#include "LabShutter.h"
#include "LabBeep.h"
#include "LabDelay.h"
#include "printf.h"
#include "debug.h"

//              0
//              1
//RF24-IRQ      2
//              3
//RELAY_CLOSE   4
//RELAY_OPEN    5
//SWITCH_CLOSED 6
//SWITCH_OPENED 7
//RF24-CE       8
//RF24-CSN      9
//BEEPER       10
//RF24-MOSI    11
//RF24-MISO    12
//RF24-SCK     13

#define SWITCH_CLOSED 6
#define SWITCH_OPENED 7

#define RELAY_CLOSE 4
#define RELAY_OPEN 5

#define BEEPER 10

RF24 radio(8,9);

LabSwitch switchOpened(SWITCH_OPENED);
LabSwitch switchClosed(SWITCH_CLOSED);
LabRelay relayOpen(RELAY_OPEN);
LabRelay relayClose(RELAY_CLOSE);
LabMotor motor;
LabShutter shutter;
LabBeep beep(BEEPER);
LabDelay _delay;

void switchOpenedEvent() {
  switchOpened.relayOff();
}

void switchClosedEvent() {
  switchClosed.relayOff();
}

void setupIrq() {
  PCintPort::attachInterrupt(SWITCH_OPENED, switchOpenedEvent, RISING);
  PCintPort::attachInterrupt(SWITCH_CLOSED, switchClosedEvent, RISING);
}

void setup() {
  Serial.begin(9600);
  printf_begin();
  printf("\n\rLabShutterApp\n\r");
  printf("release 0.6 - 2012-feb-25\n\r");
  printf("serial log 9600,n,8,1,p\n\r\n\r");
  printf("debug ON\r\n\r\n");
  printf("debug OFF\r\n\r\n");

  switchOpened.setRelay(&relayOpen);
  switchClosed.setRelay(&relayClose);

  motor.setSwitchForward(&switchOpened);
  motor.setSwitchReverse(&switchClosed);
  motor.setRelayForward(&relayOpen);
  motor.setRelayReverse(&relayClose);

  shutter.setMotor(&motor);
  shutter.setRadio(&radio);
  shutter.setBeeper(&beep);

  setupIrq();

  printf("> setup OK; ready!\n\r\n\r");
  beep.play();

  _delay.wait(1000);
}

void loop() {
  shutter.checkRx();
  shutter.doEvent();
  shutter.setState();
}

