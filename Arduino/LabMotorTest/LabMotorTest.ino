#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include "LabMotor.h"
#include "LabSwitch.h"
#include "LabRelay.h"
#include "LabComponent.h"

#define SWITCH_FORWARD 6
#define SWITCH_REVERSE 7

#define RELAY_FORWARD 4
#define RELAY_REVERSE 5

LabSwitch switchForward(SWITCH_FORWARD);
LabSwitch switchReverse(SWITCH_REVERSE);
LabRelay relayForward(RELAY_FORWARD);
LabRelay relayReverse(RELAY_REVERSE);
LabMotor motorShutter;

char r=0;

void setupIrq() {
  PCintPort::attachInterrupt(SWITCH_FORWARD, eventSwitchForward, RISING);
  PCintPort::attachInterrupt(SWITCH_REVERSE, eventSwitchReverse, RISING);
}

void eventSwitchForward() {
  switchForward.callEvent();
}

void eventSwitchReverse() {
  switchReverse.callEvent();
}

void setup()
{
  Serial.begin(57600);
  Serial.println("");
  Serial.println("LabMotorTest");

  switchForward.setComponent(&relayForward);
  switchReverse.setComponent(&relayReverse);

  motorShutter.setSwitchForward(&switchForward);
  motorShutter.setSwitchReverse(&switchReverse);
  motorShutter.setRelayForward(&relayForward);
  motorShutter.setRelayReverse(&relayReverse);

  setupIrq();

  delay(2000);
}

void loop()
{
  motorShutter.forward();
  delay(1000);
  motorShutter.reverse();
  delay(1000);
}

