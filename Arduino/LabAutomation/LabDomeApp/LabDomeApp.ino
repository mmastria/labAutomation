#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "IRremote.h"
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include "LabSwitch.h"
#include "LabEncoder.h"
#include "LabDome.h"
#include "LabBeep.h"
#include "printf.h"

//
// alterar IRRemote.h
// (+) #include <Arduino.h>
// (-) #include <Wprogram.h>

//             0
//             1
//RF24-IRQ     2
//IR_RECEIVER  3
//             4
//             5
//SWITCH_HOME  6
//ENCODER      7
//RF24-CE      8
//RF24-CSN     9
//BEEPER      10
//RF24-MOSI   11
//RF24-MISO   12
//RF24-SCK    13

#define SWITCH_HOME 6
#define ENCODER 7
#define IR_RECEIVER 3
#define BEEPER 10

RF24 radio(8,9);
IRrecv irrecv(IR_RECEIVER);

LabEncoder encoder(ENCODER);
LabSwitch switchHome(SWITCH_HOME);
LabDome dome;
LabBeep beep(BEEPER);

void switchHomeEvent() {
  switchHome.callEvent();
}

void encoderEvent() {
  encoder.callEvent();
}

void setupIrq() {
  PCintPort::attachInterrupt(SWITCH_HOME, switchHomeEvent, RISING);
  PCintPort::attachInterrupt(ENCODER, encoderEvent, RISING);
}

void setup()
{
  Serial.begin(57600);
  printf_begin();
  printf("\n\rLabDomeApp\n\r");
  printf("release 0.3 - 2012-feb-20\n\r");
  printf("serial log 57600,n,8,1,p\n\r\n\r");

  switchHome.setComponent(&encoder);
  
  //dome.setHome(&switchHome);
  dome.setRadio(&radio);

  setupIrq();
  irrecv.enableIRIn();

  printf("> setup OK; ready!\n\r\n\r");
  beep.play();

  delay(2000);
}

void irCheck() {
  decode_results results;
  if(irrecv.decode(&results)) {
    if(results.decode_type == NEC) {
      switch(results.value) {
        case 0xFF22DD: // [<<] Dome Left
          beep.play();
          break;
        case 0xFF02FD: // [>>] Dome Right
          beep.play();
          break;
        case 0xFFC23D: // [>||] Stop Dome
          beep.play();
          break;
        case 0xFFE01F: // [-] Close Shutter
          beep.play();
          dome.shutterClose();
          dome.checkRx();
          break;
        case 0xFFA857: // [+] Open Shutter
          beep.play();
          dome.shutterOpen();
          dome.checkRx();
          break;
        case 0xFF906F: // [EQ] Stop Shutter
          beep.play();
          dome.shutterStop();
          dome.checkRx();
          break;
        default:
          beep.play();
          delay(50);
          beep.play();
          dome.shutterState();
          dome.checkRx();
      }
    }
    irrecv.resume();
  }
}  

void loop() {
  irCheck();
}

