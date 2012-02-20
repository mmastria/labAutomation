#include "LabIRReceiver.h"

LabIRReceiver::LabIRReceiver() {
}

LabIRReceiver::LabIRReceiver(byte pinIRReceiver) {
  _pinIRReceiver = pinIRReceiver;
  IRrecv irrecv(_pinIRReceiver);
  _irrecvPtr = &irrecv;
  _irrecvPtr->enableIRIn();
}

boolean LabIRReceiver::decode() {
  if(_irrecvPtr->decode(&results)) {
    translateIR(); 
    _irrecvPtr->resume();
    return true;
  }
  else {
    return false;
  }
}

void LabIRReceiver::translateIR() {
  if(results.decode_type == NEC) {
    printf("NEC: ");
    switch(results.value) {
      case 0xFF22DD:
        printf("[<<] Dome Left\n\r");
        break;
      case 0xFF02FD:
        printf("[>>] Dome Right\n\r");
        break;
      case 0xFFC23D:
        printf("[>||] Stop Dome\n\r");
        break;
      case 0xFFE01F:
        printf("[-] Close Shutter\n\r");
        break;
      case 0xFFA857:
        printf("[+] Open Shutter\n\r");
        break;
      case 0xFF906F:
        printf("[EQ] Stop Shutter\n\r");
        break;
      default:
        printf("IR: %X\n\r", results.value);
    }
  }
  else
    printf("Other Type: %u / %X\n\r", results.value, results.value);
}

// NEC
//
// CH-    = FFA25D
// CH     = FF629D
// CH+    = FFE21D
// <<     = FF22DD
// >>     = FF02FD
// >||    = FFC23D
// -      = FFE01F
// +      = FFA857
// EQ     = FF906F
// 0      = FF6897
// 100+   = FF9867
// 200+   = FFB04F
// 1      = FF30CF
// 2      = FF18E7
// 3      = FF7A85
// 4      = FF10EF
// 5      = FF38C7
// 6      = FF5AA5
// 7      = FF42BD
// 8      = FF4AB5
// 9      = FF52AD
