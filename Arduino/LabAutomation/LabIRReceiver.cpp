#include "LabIRReceiver.h"

LabIRReceiver::LabIRReceiver() {
}

LabIRReceiver::LabIRReceiver(byte pinIRReceiver) {
  _pinIRReceiver = pinIRReceiver;
  IRrecv irrecv(_pinIRReceiver);
  _irrecv = &irrecv;
}

boolean LabIRReceiver::decode() {
  if(_irrecv->decode(&results)) {
    translateIR(); 
    _irrecv->resume();
    return true;
  }
  else {
    return false;
  }
}

void LabIRReceiver::translateIR() {
  switch(results.value) {
    case 0xFFA25D:
      printf("CH-\n\r");
      break;
  }
}



