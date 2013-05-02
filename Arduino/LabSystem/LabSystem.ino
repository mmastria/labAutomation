#include <Arduino.h>
#include <SPI.h>
#include <RF24Network.h>
#include <RF24.h>
#include <QueueList.h>
#include "LabSystem.h"

#ifdef __CONTROLLER__
#include <LiquidCrystal.h>
#include <IRremote.h>
#include <ModbusSlave.h>
#endif

#ifdef __DOME__
#include <PinChangeInt.h>
#endif

#ifdef __SHUTTER__
#include <PinChangeInt.h>
#endif

#ifdef __SCOPE__
#include <dht.h>
#endif

//#include "LabBeep.h"
#include "LabBroker.h"

//
// alterar IRremoteInt.h
//
// (-) #include <Wprogram.h>
// (+) #include <Arduino.h>
//

// DOME             SHUTTER         SCOPE           CONTROLLER         
//              0                 0 RS232_RX      0 RS232_RX     0
//              1                 1 RS232_TX      1 RS232_TX     1
// ENCODER      2                 2 SMOTOR_DIR    2 LCD_D3       2
// SWITCH_220V  3                 3 SMOTOR_STEP   3 LCD_D2       3
//              4                 4               4 LCD_D1       4
//              5   SWITCH_OPENED 5 SMOTOR_ENABLE 5 LCD_D0       5
// SWITCH_HOME  6   SWITCH_CLOSED 6               6 LCD_ENABLE   6
// RELAY_LEFF   7   RELAY_OPEN    7               7 LCD_RS       7
// RELAY_RIGHT  8   RELAY_CLOSE   8 DHT22         8 IR_RECV      8
// RF24-CE      9   RF24-CE       9 RF24-CE       9 RF24-CE      9
// RF24-CSN    10   RF24-CSN     10 RF24-CSN     10 RF24-CSN    10
// RF24-MOSI   11   RF24-MOSI    11 RF24-MOSI    11 RF24-MOSI   11
// RF24-MISO   12   RF24-MISO    12 RF24-MISO    12 RF24-MISO   12
// RF24-SCK    13   RF24-SCK     13 RF24-SCK     13 RF24-SCK    13
//             14                14              14 RELAY_ARSEC 14
//             15                15              15 RELAY_DESBR 15
//             16                16              16 RELAY_DESWT 16
//             17                17              17 RELAY_AUX   17
//             18                18              18             18
// BEEPER      19   BEEPER       19 BEEPER       19 BEEPER      19
//             A0                A0 IRS-LEFT     A0             A0
//             A1                A1 IRS-RIGHT    A1             A1
//             A2                A2              A2             A2
//             A3                A3              A3             A3
//             A4                A4              A4             A4
//             A5                A5              A5             A5


// PINS AND DEFS


//COMMON
#define BEEPER 19
#define RF24_CE 9
#define RF24_CSN 10
#define RF24_CHANNEL 90

#ifdef __CONTROLLER__
#define IR_RECV 8
#define LCD_RS 7
#define LCD_ENABLE 6
#define LCD_D0 5
#define LCD_D1 4
#define LCD_D2 3
#define LCD_D3 2
#define RELAY_ARSEC 14
#define RELAY_DESBR 15
#define RELAY_DESWT 16
#define RELAY_SYSPOWER 17
#endif

#ifdef __DOME__
#define ENCODER 2
#define SWITCH_220V 3
#define SWITCH_HOME 6
#define RELAY_LEFT 7
#define RELAY_RIGHT 8
#define ENCODER_MAX_VALUE 10000
#endif

#ifdef __SHUTTER__
#define SWITCH_OPENED 5
#define SWITCH_CLOSED 6
#define RELAY_OPEN 7
#define RELAY_CLOSE 8
#endif

#ifdef __SCOPE__
#define DHT22 8
#define IRSHARP_LEFT 0
#define IRSHARP_RIGHT 1
#define IRSHARP_REF_VALUE 180
#define SMOTOR_DIR 2
#define SMOTOR_STEP 3
#define SMOTOR_ENABLE 5
#endif


// DEVICES


//COMMON
LabBeep beep(BEEPER);
QueueList <payload_t> queue;
boolean abortEv=false;
LabBroker broker;
unsigned long millisTimer;

#ifdef __CONTROLLER__
LabController controller;
LabRelay relayArsec(RELAY_ARSEC);
LabRelay relayDesBr(RELAY_DESBR);
LabRelay relayDesWt(RELAY_DESWT);
LabRelay relaySysPower(RELAY_SYSPOWER);
LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D0, LCD_D1, LCD_D2, LCD_D3);
IRrecv irrecv(IR_RECV);
ModbusSlave mbs;
int regs[MB_REGS];
#endif

#ifdef __DOME__
LabDome dome;
LabRelay relayLeft(RELAY_LEFT);
LabRelay relayRight(RELAY_RIGHT);
LabSwitch switchHome(SWITCH_HOME);
LabEncoder encoder(ENCODER, ENCODER_MAX_VALUE);
LabSwitch switch220v(SWITCH_220V);
LabMotor domeMotor;
#endif

#ifdef __SHUTTER__
LabShutter shutter;
LabRelay relayClose(RELAY_CLOSE);
LabRelay relayOpen(RELAY_OPEN);
LabSwitch switchClosed(SWITCH_CLOSED);
LabSwitch switchOpened(SWITCH_OPENED);
LabMotor shutterMotor;
#endif

#ifdef __SCOPE__
LabScope scope;
dht dht22;
LabIrSharp irSharpLeft(IRSHARP_LEFT, IRSHARP_REF_VALUE);
LabIrSharp irSharpRight(IRSHARP_RIGHT, IRSHARP_REF_VALUE);
LabSmotor sMotor(SMOTOR_DIR, SMOTOR_STEP, SMOTOR_ENABLE);
#endif


// EVENTS


#ifdef __DOME__
void switchHomeEvent() {
  queue.push((payload_t){DOME_SENSORHOME});
}

void switch220vEvent() {
  dome.startDelay();
}

void encoderEvent() {
  dome.change();
}
#endif

#ifdef __SHUTTER__
void switchOpenedEvent() {
  abortEv=true;
  while (!queue.isEmpty()) {
    queue.pop();
  }
  queue.push((payload_t){SHUTTER_SENSOROPENED});
}

void switchClosedEvent() {
  abortEv=true;
  while (!queue.isEmpty()) {
    queue.pop();
  }
  queue.push((payload_t){SHUTTER_SENSORCLOSED});
}
#endif

void timer() {
  if(!abortEv) {
    millisTimer=millis();
    #ifdef __CONTROLLER__
      broker.timer();
      controller.setLastHumidity(broker.regs[MB_SCOPE_HUMIDITY]);
      controller.timer();
      controller.checkAutodes();
      queue.push((payload_t){CONTROLLER_GETTIMER});
    #endif
    #ifdef __DOME__
      dome.timer();
      dome.checkSync();
      queue.push((payload_t){DOME_GETTIMER});
      if(dome.checkDelay())
        queue.push((payload_t){DOME_SENSOR220V});
    #endif
    #ifdef __SHUTTER__
      shutter.timer();
      queue.push((payload_t){SHUTTER_GETTIMER});
      if(shutter.fullSyncOn()) {
        queue.push((payload_t){SHUTTER_SENDSYNC});
      }
    #endif
    #ifdef __SCOPE__
      scope.timer();
      queue.push((payload_t){SCOPE_GETTIMER});
      if(scope.fullSyncOn()) {
        queue.push((payload_t){SCOPE_SENDSYNC});
      }
    #endif
  }
}

// COMMANDS

#ifdef __CONTROLLER__

void checkIR() {
  if(!abortEv) {
    decode_results results;
    if(irrecv.decode(&results)) {
      if(results.decode_type == NEC) {
        switch(results.value) {
        case 0xFFC23D: queue.push((payload_t){DOME_STOP}); break;           // [>||] Stop Dome
        case 0xFF02FD: queue.push((payload_t){DOME_RIGHT}); break;          // [>>] Dome Right
        case 0xFF22DD: queue.push((payload_t){DOME_LEFT}); break;           // [<<] Dome Left
        case 0xFF906F: queue.push((payload_t){SHUTTER_STOP}); break;        // [EQ] Stop Shutter
        case 0xFFA857: queue.push((payload_t){SHUTTER_OPEN}); break;        // [+] Open Shutter
        case 0xFFE01F: queue.push((payload_t){SHUTTER_CLOSE}); break;       // [-] Close Shutter
        case 0xFF629D: queue.push((payload_t){FULL_SYNC}); break;           // [CH] Scope/Shutter/Dome Sync/Stop Sync
        case 0xFFE21D: queue.push((payload_t){FOCUS_INWARD}); break;        // [CH+] Focus +
        case 0xFFA25D: queue.push((payload_t){FOCUS_OUTWARD}); break;       // [CH-] Focus -
        case 0xFF6897: queue.push((payload_t){FOCUS_1}); break;             // [0] Focus 1
        case 0xFF9867: queue.push((payload_t){FOCUS_10}); break;            // [100+] Focus 10
        case 0xFFB04F: queue.push((payload_t){FOCUS_100}); break;           // [200+] Focus 100
        case 0xFF30CF: queue.push((payload_t){DESARSEC_CHANGE}); break;     // [1] Desumidificador Arsec On/Off
        case 0xFF18E7: queue.push((payload_t){DESBROWN_CHANGE}); break;     // [2] Desumidificador Desidrat Brown On/Off
        case 0xFF7A85: queue.push((payload_t){DESWHITE_CHANGE}); break;     // [3] Desumidificador Desidrat White On/Off
        case 0xFF10EF: queue.push((payload_t){SYSPOWER_CHANGE}); break;     // [4] Power System On/Off
        case 0xFF38C7: queue.push((payload_t){AUTODES_CHANGE}); break;      // [5] Auto control - Desumidificadores
        case 0xFF5AA5: queue.push((payload_t){CONTROLLER_GETSTATE}); break; // [6] Controller - GetState
        case 0xFF42BD: queue.push((payload_t){DOME_GETSTATE}); break;       // [7] Dome - GetState
        case 0xFF4AB5: queue.push((payload_t){SHUTTER_GETSTATE}); break;    // [8] Shutter - GetState
        case 0xFF52AD: queue.push((payload_t){SCOPE_GETSTATE}); break;      // [9] Scope - GetState
        }
      }
      irrecv.resume();
    }
  }
}

void checkModBus() {
  if(!abortEv) {
    for(byte i=0; i<MB_REGS; i++)
      regs[i]=broker.regs[i];
    if(mbs.update(regs, MB_REGS)>4) {
      if(regs[MB_CONTROLLER_ARSEC]!=broker.regs[MB_CONTROLLER_ARSEC]) queue.push((payload_t){DESARSEC_CHANGE});
      if(regs[MB_CONTROLLER_DESBR]!=broker.regs[MB_CONTROLLER_DESBR]) queue.push((payload_t){DESBROWN_CHANGE});
      if(regs[MB_CONTROLLER_DESWT]!=broker.regs[MB_CONTROLLER_DESWT]) queue.push((payload_t){DESWHITE_CHANGE});
      if(regs[MB_CONTROLLER_AUTODES]!=broker.regs[MB_CONTROLLER_AUTODES]) queue.push((payload_t){AUTODES_CHANGE});
      if(regs[MB_CONTROLLER_FULLSYNC]!=broker.regs[MB_CONTROLLER_FULLSYNC]) queue.push((payload_t){FULL_SYNC});
      if(regs[MB_CONTROLLER_SYSPOWER]!=broker.regs[MB_CONTROLLER_SYSPOWER]) queue.push((payload_t){SYSPOWER_CHANGE});
      if(regs[MB_DOME_ON_RIGHT]!=broker.regs[MB_DOME_ON_RIGHT] and regs[MB_DOME_ON_RIGHT]>0) queue.push((payload_t){DOME_RIGHT});
      if(regs[MB_DOME_ON_LEFT]!=broker.regs[MB_DOME_ON_LEFT] and regs[MB_DOME_ON_LEFT]>0) queue.push((payload_t){DOME_LEFT});
      if(regs[MB_DOME_ON_RIGHT]!=broker.regs[MB_DOME_ON_RIGHT] and regs[MB_DOME_ON_RIGHT]==0) queue.push((payload_t){DOME_STOP});
      if(regs[MB_DOME_ON_LEFT]!=broker.regs[MB_DOME_ON_LEFT] and regs[MB_DOME_ON_LEFT]==0) queue.push((payload_t){DOME_STOP});
      if(regs[MB_SCOPE_STEPS]!=broker.regs[MB_SCOPE_STEPS] and regs[MB_SCOPE_STEPS]==1) queue.push((payload_t){FOCUS_1});
      if(regs[MB_SCOPE_STEPS]!=broker.regs[MB_SCOPE_STEPS] and regs[MB_SCOPE_STEPS]==10) queue.push((payload_t){FOCUS_10});
      if(regs[MB_SCOPE_STEPS]!=broker.regs[MB_SCOPE_STEPS] and regs[MB_SCOPE_STEPS]==100) queue.push((payload_t){FOCUS_100});
      if(regs[MB_SHUTTER_OPENING]!=broker.regs[MB_SHUTTER_OPENING] and regs[MB_SHUTTER_OPENING]>0) queue.push((payload_t){SHUTTER_OPEN});
      if(regs[MB_SHUTTER_CLOSING]!=broker.regs[MB_SHUTTER_CLOSING] and regs[MB_SHUTTER_CLOSING]>0) queue.push((payload_t){SHUTTER_CLOSE});
      if(regs[MB_SHUTTER_OPENING]!=broker.regs[MB_SHUTTER_OPENING] and regs[MB_SHUTTER_OPENING]==0) queue.push((payload_t){SHUTTER_STOP});
      if(regs[MB_SHUTTER_CLOSING]!=broker.regs[MB_SHUTTER_CLOSING] and regs[MB_SHUTTER_CLOSING]==0) queue.push((payload_t){SHUTTER_STOP});
      if(regs[MB_STP_FOCUS_INWARD]) queue.push((payload_t){FOCUS_INWARD});
      if(regs[MB_STP_FOCUS_OUTWARD]) queue.push((payload_t){FOCUS_OUTWARD});
    }
  }
}
#endif

void checkNetwork() {
  if(!abortEv) {
    payload_t payload=broker.checkNetwork();
    if(payload.action!=NOTHING)
      queue.push(payload);
  }
}

//INTERRUPTS

#ifdef __DOME__
void setupIrqDome() {
  PCintPort::attachInterrupt(SWITCH_220V, switch220vEvent, RISING);
  PCintPort::attachInterrupt(SWITCH_HOME, switchHomeEvent, RISING);
  PCintPort::attachInterrupt(ENCODER, encoderEvent, CHANGE);
}
#endif

#ifdef __SHUTTER__
void setupIrqShutter() {
  PCintPort::attachInterrupt(SWITCH_OPENED, switchOpenedEvent, RISING);
  PCintPort::attachInterrupt(SWITCH_CLOSED, switchClosedEvent, RISING);
}
#endif

//SETUP
void setup() {
  #ifdef __CONTROLLER__
    lcd.begin(16, 2);
    controller.setLcd(&lcd);
    controller.setRelayArsec(&relayArsec);
    controller.setRelayDesBr(&relayDesBr);
    controller.setRelayDesWt(&relayDesWt);
    controller.setRelaySysPower(&relaySysPower);
    broker.setController(&controller);
    mbs.configure(1, 115200, 'n', 0);
    for(byte i=0; i<MB_REGS; i++)
      regs[i]=0;    
  #endif
  #ifdef __DOME__
    domeMotor.setRelayForward(&relayRight);
    domeMotor.setRelayReverse(&relayLeft);
    dome.setMotor(&domeMotor);
    dome.setEncoder(&encoder);
    dome.setSwitchHome(&switchHome);
    switch220v.setDelayStart(SWITCH_DELAY);
    dome.setSwitch220v(&switch220v);
    broker.setDome(&dome);
    setupIrqDome();
  #endif
  #ifdef __SHUTTER__
    switchOpened.setRelay(&relayOpen);
    switchClosed.setRelay(&relayClose);
    shutterMotor.setSwitchForward(&switchOpened);
    shutterMotor.setSwitchReverse(&switchClosed);
    shutterMotor.setRelayForward(&relayOpen);
    shutterMotor.setRelayReverse(&relayClose);
    shutter.setMotor(&shutterMotor);
    broker.setShutter(&shutter);
    setupIrqShutter();
  #endif
  #ifdef __SCOPE__
    scope.setIrSharpLeft(&irSharpLeft);
    scope.setIrSharpRight(&irSharpRight);
    scope.setSmotor(&sMotor);
    scope.setDht(&dht22, DHT22);
    broker.setScope(&scope);
  #endif
  broker.setBeep(&beep);
  broker.begin();
  #ifdef __CONTROLLER__
    irrecv.enableIRIn();
    controller.lcdPrint("LabSystem r:");
    controller.lcdPrint(RELEASE);
    controller.lcdSetCursor(0,1);
    controller.lcdPrint("(c)2012, Mastria");
  #else
    #ifdef __DEBUG__
      Serial.begin(9600);
      Serial.print("LabSystem r:");
      Serial.println(RELEASE);
      queue.setPrinter(Serial);
    #endif
  #endif
  millisTimer=millis();
  broker.beep();
  delay(50);
  broker.beep();
  delay(50);
  broker.beep();
  delay(100);
}

void loop() {
  if(!abortEv) {
    checkNetwork();
    if(millis()<millisTimer)
      timer();
    else
      if(millis()>(millisTimer+(TIMER_INTERVAL)))
        timer();
    #ifdef __CONTROLLER__
      checkIR();
      checkModBus();
    #endif
  }
  while (!queue.isEmpty()) {
    noInterrupts();
    payload_t payload=queue.pop();
    interrupts();
    #ifndef __CONTROLLER__
    #ifdef __DEBUG__
    switch(payload.action) {
      case CONTROLLER_GETTIMER:
      case DOME_GETTIMER:
      case SHUTTER_GETTIMER:
      case SCOPE_GETTIMER:
        break;
      default:
        Serial.print("action: ");
        Serial.print(payload.action);
        Serial.print(" - ");
        Serial.println(action_desc[payload.action]);
    }
    #endif
    #endif
    broker.action(payload);
    abortEv=false;
  }
}


