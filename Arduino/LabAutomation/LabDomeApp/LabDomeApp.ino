#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "IRremote.h"
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include "LabSwitch.h"
#include "LabEncoder.h"
#include "LabIrReceiver.h"
#include "LabDome.h"
#include "LabBeep.h"
#include "printf.h"

//
// alterar IRRemote.h
// (+) #include <Arduino.h>
// (-) #include <Wprogram.h>

//             0
//             1
//RF24-IRQ     2
//IR_RECEIVER  3
//             4
//             5
//SWITCH_HOME  6
//ENCODER      7
//RF24-CE      8
//RF24-CSN     9
//BEEPER      10
//RF24-MOSI   11
//RF24-MISO   12
//RF24-SCK    13

#define SWITCH_HOME 6
#define ENCODER 7
#define IR_RECEIVER 3
#define BEEPER 10

RF24 radio(8,9);

LabEncoder encoder(ENCODER);
LabSwitch switchHome(SWITCH_HOME);
LabDome dome;
LabBeep beep(BEEPER);
LabIRReceiver irReceiver(IR_RECEIVER);

void switchHomeEvent() {
  switchHome.callEvent();
}

void encoderEvent() {
  encoder.callEvent();
}

void setupIrq() {
  PCintPort::attachInterrupt(SWITCH_HOME, switchHomeEvent, RISING);
  PCintPort::attachInterrupt(ENCODER, encoderEvent, RISING);
}

void setup()
{
  Serial.begin(57600);
  printf_begin();
  printf("\n\rLabDomeApp\n\r");
  printf("release 0.2 - 2012-feb-20\n\r");
  printf("serial log 57600,n,8,1,p\n\r\n\r");

  switchHome.setComponent(&encoder);
  irReceiver.setComponent(&dome);
  
  //dome.setHome(&switchHome);
  dome.setRadio(&radio);
  dome.setIRReceiver(&irReceiver);

  setupIrq();

  printf("> setup OK; ready!\n\r\n\r");
  beep.play();

  delay(2000);
}

int i = 1;

void loop() {
  irReceiver.decode();
//  i++;
//  if(i>=9) {
//    i=1;
//    printf("\n\r--------------------\r\n");
//  }
//  dome.doTest(i);
//  dome.checkRx();
//  delay(500);
}

