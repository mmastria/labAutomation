#include "LabScope.h"
#include "debug.h"

LabScope::LabScope() {
  _temperature = 999.99;
  _humidity = 999.99;
  _listenOn = true;
}

void LabScope::checkRx() {
  if (_radioPtr->available()) {
    printf("---------------------\n\r");
    LabCommand commandRx;
    _radioPtr->read( &commandRx, sizeof(commandRx) );
    _radioPtr->stopListening();
    _listenOn = false;
    printf("Rx: %s\n\r", commandRx.getName());
    LabCommand commandTx;
    if(commandRx.cmd == SCOPE_EVENT_GETTH) {
      commandTx.cmd = SCOPE_STATE_TH;
      commandTx.temperature = _temperature;
      commandTx.humidity = _humidity;
    }
    else {
      commandTx.cmd = SCOPE_EVENT;
    }
    char humidityBuffer[10];
    char temperatureBuffer[10];
    dtostrf(commandTx.humidity, 6,  2,humidityBuffer);
    dtostrf(commandTx.temperature, 6, 2, temperatureBuffer);
    printf("TX: %s - H:%s / T:%s\n\r", commandTx.getName(), humidityBuffer, temperatureBuffer);
    _radioPtr->write(&commandTx, sizeof(commandTx));
  }
}

void LabScope::setState() {
  if(_dhtPtr!=NULL) {
    _delay.wait(20);
    if(_dhtPtr->read22(_dhtPin)==0) {
      _humidity=_dhtPtr->humidity;
      _temperature=_dhtPtr->temperature;
    }
  }
  if(!_listenOn) {
    _radioPtr->startListening();
    _listenOn=true;
  }
}

void LabScope::setRadio(RF24 *radioPtr) {
  if (radioPtr!=NULL) {
    _radioPtr=radioPtr;
    _radioPtr->begin();
    _radioPtr->setRetries(15,15);
    _radioPtr->openWritingPipe(pipesDomeScope[1]);
    _radioPtr->openReadingPipe(1,pipesDomeScope[0]);
    _radioPtr->startListening();
  }
}

void LabScope::setDht(dht *dhtPtr, int dhtPin) {
  if (dhtPtr!=NULL) {
    _dhtPtr=dhtPtr;
    _dhtPin=dhtPin;
  }
}


