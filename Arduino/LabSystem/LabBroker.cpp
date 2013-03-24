#include "LabBroker.h"

RF24 radio(RF24_CE,RF24_CSN);
RF24Network network(radio);

void LabBroker::begin() {
  SPI.begin();
  radio.begin();
  #ifdef __CONTROLLER__
    _fullSync=false;
    for(byte i=0; i<MB_REGS; i++)
      regs[i]=0;    
    network.begin(RF24_CHANNEL, ADDR_CONTROLLER);
    _countDownController=PING_INTERVAL;
    _countDownDome=PING_INTERVAL;
    _countDownShutter=PING_INTERVAL;
    _countDownScope=PING_INTERVAL;
    _countController=0;
    _countDome=0;
    _countShutter=0;
    _countScope=0;
  #endif
  #ifdef __DOME__
    network.begin(RF24_CHANNEL, ADDR_DOME);
  #endif
  #ifdef __SHUTTER__
    network.begin(RF24_CHANNEL, ADDR_SHUTTER);
  #endif
  #ifdef __SCOPE__
    network.begin(RF24_CHANNEL, ADDR_SCOPE);
  #endif
}

#ifdef __CONTROLLER__
void LabBroker::timer() {
  if(_countDownController>0) {
    _countDownController--;
    _countController++;
  }
  else
    _controllerPtr->lcdPingController(false);
  if(_countDownDome>0) {
    _countDownDome--;
    _countDome++;
  }
  else
    _controllerPtr->lcdPingDome(false);
  if(_countDownShutter>0) {
    _countDownShutter--;
    _countShutter++;
  }
  else
    _controllerPtr->lcdPingShutter(false);
  if(_countDownScope>0) {
    _countDownScope--;
    _countScope++;
  }
  else
    _controllerPtr->lcdPingScope(false);
}

void LabBroker::setController(LabController *controllerPtr) {
  _controllerPtr=controllerPtr;
}
#endif

#ifdef __DOME__
void LabBroker::setDome(LabDome *domePtr) {
  _domePtr=domePtr;
}
#endif

#ifdef __SHUTTER__
void LabBroker::setShutter(LabShutter *shutterPtr) {
  _shutterPtr=shutterPtr;
}
#endif

#ifdef __SCOPE__
void LabBroker::setScope(LabScope *scopePtr) {
  _scopePtr=scopePtr;
}
#endif

void LabBroker::setBeep(LabBeep *beepPtr) {
  _beepPtr=beepPtr;
}

void LabBroker::beep() {
  _beepPtr->play();
}

void LabBroker::send(uint16_t address, action_e action) {
  payload_t payload = {action};
  #ifdef __CONTROLLER__
    payload.b1=_fullSync;
  #endif
  RF24NetworkHeader header(address);
  network.write(header,&payload,sizeof(payload));
}

#ifdef __CONTROLLER__
void LabBroker::cancelFullSync() {
  if(_fullSync) {
    _fullSync=!_fullSync;
    _controllerPtr->fullSync(_fullSync);
    send(ADDR_DOME, FULL_SYNC);
    send(ADDR_SHUTTER, FULL_SYNC);
    send(ADDR_SCOPE, FULL_SYNC); 
  }
}
#else
void LabBroker::push(payload_t payload, uint16_t address) {
  RF24NetworkHeader header(address);
  network.write(header,&payload,sizeof(payload));
}

void LabBroker::callBack(payload_t payload) {
  push(payload, ADDR_CONTROLLER);
}  
#endif

payload_t LabBroker::checkNetwork() {
  network.update();
  if(network.available()) {
    RF24NetworkHeader header;
    payload_t payload;
    network.read(header,&payload,sizeof(payload));
    return payload;
  }
  else
    return (payload_t){NOTHING};
}

void LabBroker::action(payload_t payload) {
  switch(payload.action) {
// --------------------------------
  #ifdef __CONTROLLER__
// --------------------------------
    case DOME_STOP:
      cancelFullSync();
      send(ADDR_DOME, DOME_STOP);
      break;
    case DOME_RIGHT:
      cancelFullSync();
      send(ADDR_DOME, DOME_RIGHT);
      break;
    case DOME_LEFT:
      cancelFullSync();
      send(ADDR_DOME, DOME_LEFT);
      break;
    case DOME_GETSTATE:
      send(ADDR_DOME, DOME_GETSTATE); 
      break;
    case DOME_RETURNSTATE:
      domeReturnState(payload);
      break;
    case DOME_TIMER:
      domeTimer(payload);
      break;
    case SHUTTER_STOP:
      cancelFullSync();
      send(ADDR_SHUTTER, SHUTTER_STOP); 
      break;
    case SHUTTER_OPEN:
      cancelFullSync();
      send(ADDR_SHUTTER, SHUTTER_OPEN);
      break;
    case SHUTTER_CLOSE:
      cancelFullSync();
      send(ADDR_SHUTTER, SHUTTER_CLOSE);
      break;
    case SHUTTER_GETSTATE:
      send(ADDR_SHUTTER, SHUTTER_GETSTATE); 
      break;
    case SHUTTER_RETURNSTATE:
      shutterReturnState(payload); 
      break;
    case SHUTTER_TIMER:
      shutterTimer(payload);
      break;
    case SCOPE_GETSTATE:
      send(ADDR_SCOPE, SCOPE_GETSTATE); 
      break;
    case SCOPE_RETURNSTATE:
      scopeReturnState(payload);
      break;
    case SCOPE_TIMER:
      scopeTimer(payload);
      break;
    case FOCUS_INWARD:
      send(ADDR_SCOPE, FOCUS_INWARD); 
      break;
    case FOCUS_OUTWARD:
      send(ADDR_SCOPE, FOCUS_OUTWARD); 
      break;
    case FOCUS_1:
      send(ADDR_SCOPE, FOCUS_1); 
      break;
    case FOCUS_10:
      send(ADDR_SCOPE, FOCUS_10); 
      break;
    case FOCUS_100:
      send(ADDR_SCOPE, FOCUS_100); 
      break;
    case CONTROLLER_GETSTATE:
      _beepPtr->play();
      controllerReturnState(_controllerPtr->getState());
      break;
    case CONTROLLER_RETURNSTATE:
      controllerReturnState(payload); 
      break;
    case CONTROLLER_GETTIMER:
      controllerTimer(_controllerPtr->getTimer());
      break;
    case CONTROLLER_TIMER:
      controllerTimer(payload);
      break;
    case DESARSEC_CHANGE:
      _beepPtr->play();
      _controllerPtr->desarsecChange();
      break;
    case DESBROWN_CHANGE:
      _beepPtr->play();
      _controllerPtr->desbrownChange();
      break;
    case DESWHITE_CHANGE:
      _beepPtr->play();
      _controllerPtr->deswhiteChange();
      break;
    case AUTODES_CHANGE:
      _beepPtr->play();
      _controllerPtr->autodesChange();
      break;
    case SYSPOWER_CHANGE:
      _beepPtr->play();
      _controllerPtr->syspowerChange();
      break;
    case FULL_SYNC:
      _beepPtr->play();
      _fullSync=!_fullSync;
      _controllerPtr->fullSync(_fullSync);
      send(ADDR_DOME, FULL_SYNC);
      send(ADDR_SHUTTER, FULL_SYNC);
      send(ADDR_SCOPE, FULL_SYNC); 
      break;
    case NOTHING:
      break;
// --------------------------------
  #endif
  #ifdef __DOME__
// --------------------------------
    case DOME_STOP:
      _beepPtr->play();
      _domePtr->stop();
      break;
    case DOME_RIGHT:
      _beepPtr->play();
      _domePtr->right();
      break;
    case DOME_LEFT:
      _beepPtr->play();
      _domePtr->left();
      break;
    case DOME_SENSORHOME:
      _beepPtr->play();
      _domePtr->home();
      break;
    case DOME_SENSOR220V:
      send(ADDR_SHUTTER, DOME_SENSOR220V);
      break;
    case DOME_GETSTATE:
      _beepPtr->play();
      callBack(_domePtr->getState());
      break;
    case DOME_GETTIMER:
      callBack(_domePtr->getTimer());
      break;
    case SHUTTER_SYNC:
      shutterSync(payload);
      break;
    case SCOPE_SYNC:
      scopeSync(payload);
      break;
    case FULL_SYNC:
      _beepPtr->play();
      fullSync(payload.b1);
      break;
    case NOTHING:
      break;
// --------------------------------
  #endif
  #ifdef __SHUTTER__
// --------------------------------
    case SHUTTER_STOP:
      _beepPtr->play();
      _shutterPtr->stop();
      break;
    case SHUTTER_OPEN:
      _beepPtr->play();
      _shutterPtr->open();
      break;
    case SHUTTER_CLOSE:
      _beepPtr->play();
      _shutterPtr->close();
      break;
    case SHUTTER_SENSOROPENED:
      _beepPtr->play();
      _shutterPtr->stop();
      break;
    case SHUTTER_SENSORCLOSED:
      _beepPtr->play();
      _shutterPtr->stop();
      break;
    case SHUTTER_GETSTATE:
      _beepPtr->play();
      callBack(_shutterPtr->getState());
      break;
    case SHUTTER_GETTIMER:
      callBack(_shutterPtr->getTimer());
      break;
    case SHUTTER_SENDSYNC:
      push(_shutterPtr->getSync(), ADDR_DOME);
      break;
    case DOME_SENSOR220V:
      _beepPtr->play();
      _shutterPtr->close();
      break;
    case FULL_SYNC:
      _beepPtr->play();
      fullSync(payload.b1);
      break;
    case NOTHING:
      break;
// --------------------------------
  #endif
  #ifdef __SCOPE__
// --------------------------------
    case SCOPE_GETSTATE:
      _beepPtr->play();
      callBack(_scopePtr->getState());
      break;
    case SCOPE_GETTIMER:
      callBack(_scopePtr->getTimer());
      break;
    case SCOPE_SENDSYNC:
      push(_scopePtr->getSync(), ADDR_DOME);
      break;
    case FOCUS_INWARD:
      _beepPtr->play();
      _scopePtr->focusInward();
      break;
    case FOCUS_OUTWARD:
      _beepPtr->play();
      _scopePtr->focusOutward();
      break;
    case FOCUS_1:
      _beepPtr->play();
      _scopePtr->focusStep(1);
      break;
    case FOCUS_10:
      _beepPtr->play();
      _scopePtr->focusStep(10);
      break;
    case FOCUS_100:
      _beepPtr->play();
      _scopePtr->focusStep(100);
      break;
    case FULL_SYNC:
      _beepPtr->play();
      fullSync(payload.b1);
      break;
    case NOTHING:
      break;
// -------------------------------------------
  #endif
// -------------------------------------------
  }
}

// -------------------------------------------
  #ifdef __CONTROLLER__
// -------------------------------------------

void LabBroker::domeReturnState(payload_t payload) {
  _controllerPtr->lcdClear();
  _controllerPtr->lcdPrint("RG:");
  _controllerPtr->lcdPrint(payload.b1);
  _controllerPtr->lcdPrint(" LF:");
  _controllerPtr->lcdPrint(payload.b2);
  _controllerPtr->lcdPrint(" HOME:");
  _controllerPtr->lcdPrint(payload.b3);
  _controllerPtr->lcdSetCursor(0,1);
  _controllerPtr->lcdPrint("220v:");
  _controllerPtr->lcdPrint(payload.b4);
  _controllerPtr->lcdPrint(" AZM:");
  _controllerPtr->lcdPrint(payload.i1/10.0);
}

void LabBroker::shutterReturnState(payload_t payload) {
  _controllerPtr->lcdClear();
  _controllerPtr->lcdPrint("OPENg:");
  _controllerPtr->lcdPrint(payload.b1);
  _controllerPtr->lcdPrint(" CLOSEg:");
  _controllerPtr->lcdPrint(payload.b2);
  _controllerPtr->lcdSetCursor(0,1);
  _controllerPtr->lcdPrint("OPENd:");
  _controllerPtr->lcdPrint(payload.b3);
  _controllerPtr->lcdPrint(" CLOSEd:");
  _controllerPtr->lcdPrint(payload.b4);
}

void LabBroker::scopeReturnState(payload_t payload) {
  _controllerPtr->lcdClear();
  _controllerPtr->lcdPrint("WL:");
  _controllerPtr->lcdPrint(payload.b1);
  _controllerPtr->lcdPrint(" WR:");
  _controllerPtr->lcdPrint(payload.b2);
  _controllerPtr->lcdPrint(" ST:");
  _controllerPtr->lcdPrint(payload.b3);
  _controllerPtr->lcdSetCursor(0,1);
  _controllerPtr->lcdPrint("H:");
  _controllerPtr->lcdPrint(payload.b4);
  _controllerPtr->lcdPrint("% T:");
  _controllerPtr->lcdPrint(payload.i1/10.0);
  _controllerPtr->lcdPrint("C");
}

void LabBroker::controllerReturnState(payload_t payload) {
  _controllerPtr->lcdClear();
  _controllerPtr->lcdPrint("ARS:");
  _controllerPtr->lcdPrint(payload.b1);
  _controllerPtr->lcdPrint(" DBR:");
  _controllerPtr->lcdPrint(payload.b2);
  _controllerPtr->lcdPrint(" AD:");
  _controllerPtr->lcdPrint((byte)payload.i1);
  _controllerPtr->lcdSetCursor(0,1);
  _controllerPtr->lcdPrint("DWT:");
  _controllerPtr->lcdPrint(payload.b3);
  _controllerPtr->lcdPrint(" PWR:");
  _controllerPtr->lcdPrint(payload.b4);
  _controllerPtr->lcdPrint(" SY:");
  _controllerPtr->lcdPrint(_fullSync);
}

void LabBroker::domeTimer(payload_t payload) {
  regs[MB_DOME_220V]=payload.b4;
  regs[MB_DOME_AZIMUTE]=payload.i1;
  regs[MB_DOME_ON_HOME]=payload.b3;
  regs[MB_DOME_ON_LEFT]=payload.b2;
  regs[MB_DOME_ON_RIGHT]=payload.b1;
  regs[MB_DOME_PING_ON]=(_countDownDome > 0 ? 1 : 0);
  _countDownDome=PING_INTERVAL;
  _controllerPtr->lcdPingDome(true);
}

void LabBroker::shutterTimer(payload_t payload) {
  regs[MB_SHUTTER_CLOSED]=payload.b4;
  regs[MB_SHUTTER_CLOSING]=payload.b2;
  regs[MB_SHUTTER_OPENED]=payload.b3;
  regs[MB_SHUTTER_OPENING]=payload.b1;
  regs[MB_SHUTTER_PING_ON]=(_countDownShutter > 0 ? 1 : 0);
  _countDownShutter=PING_INTERVAL;
  _controllerPtr->lcdPingShutter(true);
}

void LabBroker::scopeTimer(payload_t payload) {
  regs[MB_SCOPE_HUMIDITY]=payload.b4;
  regs[MB_SCOPE_PING_ON]=(_countDownScope > 0 ? 1 : 0);
  regs[MB_SCOPE_STEPS]=payload.b3;
  regs[MB_SCOPE_TEMPERATURE]=payload.i1;
  regs[MB_SCOPE_WALL_LEFT]=payload.b1;
  regs[MB_SCOPE_WALL_RIGHT]=payload.b2;
  _countDownScope=PING_INTERVAL;
  _controllerPtr->lcdPingScope(true);
}

void LabBroker::controllerTimer(payload_t payload) {
  regs[MB_CONTROLLER_ARSEC]=payload.b1;
  regs[MB_CONTROLLER_SYSPOWER]=payload.b4;
  regs[MB_CONTROLLER_DESBR]=payload.b2;
  regs[MB_CONTROLLER_DESWT]=payload.b3;
  regs[MB_CONTROLLER_AUTODES]=payload.i1;
  regs[MB_CONTROLLER_FULLSYNC]=_fullSync;
  regs[MB_CONTROLLER_PING_ON]=(_countDownController > 0 ? 1 : 0);
  regs[MB_CONTROLLER_TIMER_COUNT]=_countController;
  regs[MB_DOME_TIMER_COUNT]=_countDome;
  regs[MB_SHUTTER_TIMER_COUNT]=_countShutter;
  regs[MB_SCOPE_TIMER_COUNT]=_countScope;
  _countDownController=PING_INTERVAL;
  _controllerPtr->lcdPingController(true);
}

// -------------------------------------------
  #else
// -------------------------------------------

void LabBroker::fullSync(boolean fullSync) {
  #ifdef __DOME__
    _domePtr->fullSync(fullSync);
  #endif
  #ifdef __SHUTTER__
    _shutterPtr->fullSync(fullSync);
  #endif
  #ifdef __SCOPE__
    _scopePtr->fullSync(fullSync);
  #endif
}

// -------------------------------------------
  #endif
  #ifdef __DOME__
// -------------------------------------------

void LabBroker::shutterSync(payload_t payload) {
  _domePtr->shutterSync(payload);
}

void LabBroker::scopeSync(payload_t payload) {
  _domePtr->scopeSync(payload);
}

// -------------------------------------------
  #endif
// -------------------------------------------

