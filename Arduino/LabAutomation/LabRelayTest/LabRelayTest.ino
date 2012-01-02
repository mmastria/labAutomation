#include "LabRelay.h"

#define RELAY_OPEN 4
#define RELAY_CLOSE 5

LabRelay relayOpen(RELAY_OPEN);
LabRelay relayClose(RELAY_CLOSE);

void setup()
{
  Serial.begin(57600);
  Serial.println("");
  Serial.println("LabRelayTest");
  delay(2000);
}

void loop()
{
  relayOpen.on();
  delay(2000);
  relayOpen.off();
  relayClose.on();
  delay(2000);
  relayClose.off();  
}

