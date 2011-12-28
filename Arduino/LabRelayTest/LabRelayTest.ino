#include <LabRelay.h>

#define RELAY_OPEN 4
#define RELAY_CLOSE 5

LabRelay relayOpen(RELAY_OPEN);
LabRelay relayClose(RELAY_CLOSE);

void setup()
{
}

void loop()
{
  relayOpen.on();
  delay(1000);
  relayOpen.off();
  relayClose.on();
  delay(1000);
  relayClose.off();  
}

