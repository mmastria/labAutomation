#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include "LabSwitch.h"
#include "LabEncoder.h"
#include "LabDome.h"
#include "LabBeep.h"

#define SWITCH_ENCODER 6
#define ENCODER 7

#define BEEPER 10

RF24 radio(8,9);

LabEncoder encoder(ENCODER);
LabSwitch switchEncoder(SWITCH_ENCODER);
LabBeep beep(BEEPER);
LabDome dome;

void switchEncoderEvent() {
  switchEncoder.callEvent();
}

void encoderEvent() {
  encoder.callEvent();
}

void domeEvent() {
  beep.play();
  dome.callEvent();
}

void setupIrq() {
  PCintPort::attachInterrupt(SWITCH_ENCODER, switchEncoderEvent, RISING);
  PCintPort::attachInterrupt(ENCODER, encoderEvent, RISING);
  attachInterrupt(0, domeEvent, FALLING);
}



void setup()
{
  Serial.begin(57600);
  Serial.println("");
  Serial.println("LabDomeTest");
  beep.play();

  dome.setRadio(&radio);

  setupIrq();

  delay(2000);  
}

void loop() {
}

