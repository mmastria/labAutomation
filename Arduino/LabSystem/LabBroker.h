#ifndef __LAB_BROKER__
#define __LAB_BROKER__

#include <Arduino.h>
#include <SPI.h>
#include <RF24Network.h>
#include <RF24.h>
#include "LabSystem.h"
#include "LabBeep.h"

#ifdef __CONTROLLER__
#include "LabController.h"
#endif

#ifdef __DOME__
#include "LabDome.h"
#endif

#ifdef __SHUTTER__
#include "LabShutter.h"
#endif

#ifdef __SCOPE__
#include "LabScope.h"
#endif

#define RF24_CE 9
#define RF24_CSN 10
#define RF24_CHANNEL 90

const uint16_t ADDR_CONTROLLER = 0;
const uint16_t ADDR_DOME = 1;
const uint16_t ADDR_SHUTTER = 2;
const uint16_t ADDR_SCOPE = 3;

class LabBroker { 

public:

  void begin();
  void action(payload_t payload);
  void send(uint16_t address, action_e action);
  payload_t checkNetwork();
  void beep();

  #ifdef __CONTROLLER__
    void setController(LabController *controllerPtr);
    void timer();
    int regs[MB_REGS];
  #endif
  #ifdef __DOME__
    void setDome(LabDome *domePtr);
  #endif
  #ifdef __SHUTTER__
    void setShutter(LabShutter *shutterPtr);
  #endif
  #ifdef __SCOPE__
    void setScope(LabScope *scopePtr);
  #endif
  void setBeep(LabBeep *beepPtr);
  
private:
  
  void push(payload_t payload, uint16_t address);
  void callBack(payload_t payload);
  void domeReturnState(payload_t payload);
  void domeTimer(payload_t payload);
  void shutterReturnState(payload_t payload);
  void shutterTimer(payload_t payload);
  void scopeReturnState(payload_t payload);
  void scopeTimer(payload_t payload);
  void controllerReturnState(payload_t payload);
  void controllerTimer(payload_t payload);
  void shutterSync(payload_t payload);
  void scopeSync(payload_t payload);
  void fullSync(boolean fullSync);

  #ifdef __CONTROLLER__
    void cancelFullSync();
    LabController *_controllerPtr;
    boolean _fullSync;
    byte _countDownController;
    byte _countDownDome;
    byte _countDownShutter;
    byte _countDownScope;
    unsigned int _countController;
    unsigned int _countDome;
    unsigned int _countShutter;
    unsigned int _countScope;
  #endif
  #ifdef __DOME__
    LabDome *_domePtr;
  #endif
  #ifdef __SHUTTER__
    LabShutter *_shutterPtr;
  #endif
  #ifdef __SCOPE__
    LabScope *_scopePtr;
  #endif
  LabBeep *_beepPtr;
  
};

#endif
