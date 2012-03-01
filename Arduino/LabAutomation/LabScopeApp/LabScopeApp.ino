#include <SPI.h>
#include <PString.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "dht.h"
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include "LabScope.h"
#include "LabIrSharp.h"
#include "LabDelay.h"
#include "LabCommand.h"
#include "printf.h"
#include "debug.h"

//IRS-LEFT    A0
//IRS-RIGHT   A1

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
#define IRSHARP_LEFT    0
#define IRSHARP_RIGHT   1

RF24 radio(8,9);
dht dht22;

LabScope scope;
LabIrSharp irSharpLeft(IRSHARP_LEFT);
LabIrSharp irSharpRight(IRSHARP_RIGHT);
LabDelay _delay;
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

  irSharpLeft.setReference(180);
  irSharpRight.setReference(180);
  scope.setRadio(&radio);
  scope.setDht(&dht22, DHT22);

  leftBefore=!irSharpLeft.isWallHit();
  rightBefore=!irSharpRight.isWallHit();
  
  printf("> setup OK; ready!\n\r\n\r");
  _delay.wait(1000);
}

void loop() {
  scope.checkRx(); 
  scope.setState();

  leftNow=irSharpLeft.isWallHit();
  rightNow=irSharpRight.isWallHit();
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
