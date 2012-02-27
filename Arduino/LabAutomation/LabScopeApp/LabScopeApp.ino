#include <SPI.h>
#include <PString.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "dht.h"
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include "LabScope.h"
#include "LabPsd.h"
#include "LabDelay.h"
#include "LabCommand.h"
#include "printf.h"
#include "debug.h"

//PSD-LEFT    A0
//PSD-RIGHT   A1

//             0
//             1
//RF24-IRQ     2
//             3
//             4
//DHT22        5
//             6
//             7
//RF24-CE      8
//RF24-CSN     9
//            10
//RF24-MOSI   11
//RF24-MISO   12
//RF24-SCK    13

#define DHT22       5
#define PSD_LEFT    0
#define PSD_RIGHT   1

RF24 radio(8,9);
dht dht22;

LabScope scope;
LabPsd psdLeft(PSD_LEFT);
LabPsd psdRight(PSD_RIGHT);
LabDelay _delay;
int cycle;
boolean leftBefore;
boolean leftNow;
boolean rightBefore;
boolean rightNow;

void setup()
{
  Serial.begin(57600);
  printf_begin();
  printf("\n\rLabScopeApp\n\r");
  printf("release 0.6 - 2012-feb-25\n\r");
  printf("serial log 57600,n,8,1,p\n\r\n\r");
#ifdef __DEBUG__
  printf("debug ON\r\n\r\n");
#else
  printf("debug OFF\r\n\r\n");
#endif

  psdLeft.setReference(180);
  psdRight.setReference(180);
  scope.setRadio(&radio);
  scope.setDht(&dht22, DHT22);
  

  cycle=0;
  leftBefore=!psdLeft.isWallHit();
  rightBefore=!psdRight.isWallHit();
  
  printf("> setup OK; ready!\n\r\n\r");
  _delay.wait(1000);
}

void loop() {
  switch(cycle) {
    case 0: scope.checkRx(); cycle++; break;
    case 1: scope.setState(); cycle=0; break;
  }
  leftNow=psdLeft.isWallHit();
  rightNow=psdRight.isWallHit();
  if(leftNow!=leftBefore) {
    Serial.print("Left Wall Hit: ");
    Serial.println(leftNow);
    leftBefore=leftNow;
  }
  if(rightNow!=rightBefore) {
    Serial.print("Right Wall Hit: ");
    Serial.println(rightNow);
    rightBefore=rightNow;
  }
}

