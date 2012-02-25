#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>
#include "LabScope.h"
#include "LabDelay.h"
#include "LabCommand.h"
#include "printf.h"
#include "debug.h"

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

#define DHT22 5

RF24 radio(8,9);

LabScope scope;
LabDelay _delay;
int cycle;

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

  scope.setRadio(&radio);

  cycle=0;
  
  printf("> setup OK; ready!\n\r\n\r");
  _delay.wait(1000);
}

void loop() {
  switch(cycle) {
    case 0: scope.checkRx(); cycle++; break;
    case 1: scope.doEvent(); cycle++; break;
    case 2: scope.setState(); cycle=0; break;
  }
}

