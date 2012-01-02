#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <LabSwitch.h>
#include <LabRelay.h>
#include <LabShutter.h>

#define RELAY_OPEN 4
#define RELAY_CLOSE 5

#define SWITCH_OPENED 6
#define SWITCH_CLOSED 7

// canais de comunicacao
const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL };

RF24 radio(8,9);

LabRelay relayOpen(RELAY_OPEN);
LabRelay relayClose(RELAY_CLOSE);

LabSwitch switchOpened(SWITCH_OPENED);
LabSwitch switchClosed(SWITCH_CLOSED);

LabShutter shutter(relayOpen, relayClose, switchOpened, switchClosed);

void setup(void)
{
  Serial.begin(57600);
  radioSetup();
  delay(500);  
}

void loop(void) {
  shutter.callEvent(SHUTTER_OPEN);
  radio.write( &shutter, sizeof(shutter) );
  Serial.println("abrir");
  delay(3000);
  shutter.callEvent(SHUTTER_CLOSE);
  radio.write( &shutter, sizeof(shutter) );
  Serial.println("fechar");
  delay(3000);
}

void radioSetup() {
  radio.begin();
  radio.openWritingPipe(pipes[0]);
}
