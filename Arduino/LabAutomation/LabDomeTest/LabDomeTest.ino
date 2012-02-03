#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include "LabSwitch.h"
#include "LabEncoder.h"
#include "LabDome.h"
//#include "LabBeep.h"

#define SWITCH_HOME 6
#define ENCODER 7

//#define BEEPER 10

RF24 radio(8,9);

LabEncoder encoder(ENCODER);
LabSwitch switchHome(SWITCH_HOME);
LabDome dome;
//LabBeep beep(BEEPER);

void switchHomeEvent() {
  switchHome.callEvent();
}

void encoderEvent() {
  encoder.callEvent();
}

void domeEvent() {
//  beep.play();
  dome.callEvent();
}

void setupIrq() {
  PCintPort::attachInterrupt(SWITCH_HOME, switchHomeEvent, RISING);
  PCintPort::attachInterrupt(ENCODER, encoderEvent, RISING);
  attachInterrupt(0, domeEvent, FALLING);
}

void setup()
{
  Serial.begin(57600);
  Serial.println("");
  Serial.println("LabDomeTest");
//  beep.play();

  switchHome.setComponent(&encoder);
  
  //dome.setHome(&switchHome);
  dome.setRadio(&radio);

  setupIrq();

  delay(2000);  
}

void loop() {
}

