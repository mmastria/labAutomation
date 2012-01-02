#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include "LabSwitch.h"
#include "LabMockup.h"

#define SWITCH_OPENED 6
#define SWITCH_CLOSED 7

LabSwitch switchOpened(SWITCH_OPENED);
LabSwitch switchClosed(SWITCH_CLOSED);

LabMockup mockup;

void setup() {
  Serial.begin(57600);
  Serial.println("");
  Serial.println("LabSwitchTest");
  switchOpened.setComponent(&mockup);
  switchClosed.setComponent(&mockup);
  setupIrq();
  delay(2000);
}

void loop() {
  Serial.print("SwitchOpened: ");
  Serial.print(switchOpened.isOn());
  Serial.print("\tSwitchClosed: ");
  Serial.print(switchClosed.isOn());
  Serial.print("\tState: ");
  Serial.println(mockup.getValue());
  delay(2000);
}

void setupIrq() {
  PCintPort::attachInterrupt(SWITCH_OPENED, eventOpen, RISING);
  PCintPort::attachInterrupt(SWITCH_CLOSED, eventClose, RISING);
}


void eventOpen() {
  if(switchOpened.isOn()) {
    switchOpened.callEvent();
  }
}

void eventClose() {
  if(switchClosed.isOn()) {
    switchClosed.callEvent();
  }
}

