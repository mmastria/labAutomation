#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include <LabTrapeira.h>
#include <LabSwitch.h>
#include <LabRelay.h>

#define RELAY_OPEN 4
#define RELAY_CLOSE 5

#define SWITCH_OPENED 6
#define SWITCH_CLOSED 7

LabRelay relayOpen(RELAY_OPEN);
LabRelay relayClose(RELAY_CLOSE);

LabSwitch switchOpened(SWITCH_OPENED);
LabSwitch switchClosed(SWITCH_CLOSED);

LabTrapeira trapeira(relayOpen, relayClose, switchOpened, switchClosed);

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
  if(switchOpened.getState()==1) {
    switchOpened.event();
  }
}

void eventClose() {
  if(switchClosed.getState()==1) {
    switchClosed.event();
  }
}
