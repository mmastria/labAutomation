#include <PString.h>
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include <LabSwitch.h>

#define SWITCH_OPENED 6
#define SWITCH_CLOSED 7

LabSwitch switchOpened(SWITCH_OPENED);
LabSwitch switchClosed(SWITCH_CLOSED);

void setup()
{
  Serial.begin(57600);
  PCintPort::attachInterrupt(SWITCH_OPENED, eventOpen, RISING);
  PCintPort::attachInterrupt(SWITCH_CLOSED, eventClose, RISING);
}

void loop()
{
}

void eventOpen() {
  if(switchOpened.isOff()) {
    switchOpened.event();
  }
}

void eventClose() {
  if(switchClosed.isOff()) {
    switchClosed.event();
  }
}

