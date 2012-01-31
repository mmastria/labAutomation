#include "LabBeep.h"

#define BEEPER 10

LabBeep beep(BEEPER);

void setup() {
}


void loop() {
  beep.play();
  delay(3000);
}


