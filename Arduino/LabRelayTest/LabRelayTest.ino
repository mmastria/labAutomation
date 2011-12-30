#include <LabRelay.h>
#include <LabSwitch.h>

#define RELAY_OPEN 4
#define RELAY_CLOSE 5

LabRelay relayOpen(RELAY_OPEN);
LabRelay relayClose(RELAY_CLOSE);

void setup()
{
  Serial.begin(57600);
  Serial.println("LabRelayTest");
}

void loop()
{
  relayOpen.on();
  delay(3000);
  relayOpen.off();
  relayClose.on();
  delay(3000);
  relayClose.off();  
}

