#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "IRremote.h"
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include "LabSwitch.h"
#include "LabRelay.h"
#include "LabMotor.h"
#include "LabEncoder.h"
#include "LabDome.h"
#include "LabBeep.h"
#include "LabDelay.h"
#include "LabCommand.h"
#include "printf.h"
#include "debug.h"

//
// alterar IRRemote.h
// (+) #include <Arduino.h>
// (-) #include <Wprogram.h>

//             0
//             1
//RF24-IRQ     2
//IR_RECEIVER  3
//RELAY_LEFF   4
//RELAY_RIGHT  5
//SWITCH_HOME  6
//ENCODER      7
//RF24-CE      8
//RF24-CSN     9
//BEEPER      10
//RF24-MOSI   11
//RF24-MISO   12
//RF24-SCK    13

#define SWITCH_HOME 6

#define RELAY_LEFT 4
#define RELAY_RIGHT 5

#define ENCODER 7
#define IR_RECEIVER 3
#define BEEPER 10

RF24 radio(8,9);
IRrecv irrecv(IR_RECEIVER);

LabBeep beep(BEEPER);
LabEncoder encoder(ENCODER);
LabSwitch switchHome(SWITCH_HOME);
LabRelay relayLeft(RELAY_LEFT);
LabRelay relayRight(RELAY_RIGHT);
LabMotor motor;
LabDome dome;
LabDelay _delay;

void switchHomeEvent() {
#ifdef __DEBUG__
  printf("Switch Home Event\n\r");
#endif
  switchHome.encoderReset();
}

void encoderEvent() {
  encoder.add();
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
  printf("release 0.5 - 2012-feb-22\n\r");
  printf("serial log 57600,n,8,1,p\n\r\n\r");
#ifdef __DEBUG__
  printf("debug ON\r\n\r\n");
#else
  printf("debug OFF\r\n\r\n");
#endif

  switchHome.setEncoder(&encoder);

  motor.setRelayForward(&relayRight);
  motor.setRelayReverse(&relayLeft);
  
  dome.setMotor(&motor);
  dome.setRadio(&radio);

  setupIrq();
  irrecv.enableIRIn();

  printf("> setup OK; ready!\n\r\n\r");
  beep.play();

  _delay.wait(2000);
}

void irCheck() {
  LabCommand commandRx;
  decode_results results;
  if(irrecv.decode(&results)) {
    if(results.decode_type == NEC) {
      switch(results.value) {
        case 0xFF22DD: // [<<] Dome Left
          beep.play();
          printf("> Call: dome.left\n\r");
          dome.left();
          break;
        case 0xFF02FD: // [>>] Dome Right
          beep.play();
          printf("> Call: dome.right\n\r");
          dome.right();
          break;
        case 0xFFC23D: // [>||] Stop Dome
          beep.play();
          printf("> Call: dome.stop\n\r");
          dome.stop();
          break;
        case 0xFFE01F: // [-] Close Shutter
          beep.play();
          printf("> Call: shutterClose\n\r");
          dome.shutterClose();
          commandRx.cmd = dome.checkRx();
          printf("  Rx: %s\n\r", commandRx.getName());
          break;
        case 0xFFA857: // [+] Open Shutter
          beep.play();
          printf("> Call: shutterOpen\n\r");
          dome.shutterOpen();
          commandRx.cmd = dome.checkRx();
          printf("  Rx: %s\n\r", commandRx.getName());
          break;
        case 0xFF906F: // [EQ] Stop Shutter
          beep.play();
          printf("> Call: shutterStop\n\r");
          dome.shutterStop();
          commandRx.cmd = dome.checkRx();
          printf("  Rx: %s\n\r", commandRx.getName());
          break;
        case 0xFFFFFFFF: // discard
          break;
        default:
#ifdef __DEBUG__
          printf("\n\rCode: %X\n\r", results.value);
#endif
          beep.play();
          _delay.wait(10);
          beep.play();
          printf("> Call: shutterState\n\r");
          dome.shutterState();
          commandRx.cmd = dome.checkRx();
          printf("  Rx: %s\n\r", commandRx.getName());
      }
    }
    irrecv.resume();
  }
}  

void loop() {
  irCheck();
}

