#ifndef __LAB_CONTROLLER__
#define __LAB_CONTROLLER__

#include <LiquidCrystal.h>
#include "LabRelay.h"
#include "LabSystem.h"

class LabController {

public:

  LabController();
  void timer();
  void setLcd(LiquidCrystal *lcdPtr);
  void setRelayArsec(LabRelay *relayArsecPtr);
  void setRelayDesBr(LabRelay *relayDesBrPtr);
  void setRelayDesWt(LabRelay *relayDesWtPtr);
  void setRelaySysPower(LabRelay *relaySysPowerPtr);
  void fullSync(boolean fullSync);  
  
  void lcdClear();
  void lcdSetCursor(uint8_t col, uint8_t row);
  
  void desarsecChange();
  void desbrownChange();
  void deswhiteChange();
  void autodesChange();
  void syspowerChange();

  void lcdPrint(const char[]);
  void lcdPrint(int, int = DEC);
  void lcdPrint(double, int = 1);
  void lcdPrint(char);
  void lcdPrint(unsigned char, int = DEC);
  void lcdPrint(unsigned int, int = DEC);
  void lcdPrint(long, int = DEC);
  void lcdPrint(unsigned long, int = DEC);
  //void lcdPrint(const String &s);
  //void lcdPrint(const __FlashStringHelper *);
  //void lcdPrint(const Printable&);
  
  void lcdPingController(boolean live);
  void lcdPingDome(boolean live);
  void lcdPingShutter(boolean live);
  void lcdPingScope(boolean live);

  payload_t getState();
  payload_t getTimer();
  
  void setLastHumidity(int lastHumidity);
  void checkAutodes();
    
private:

  payload_t getData();
  LiquidCrystal *_lcdPtr;
  LabRelay *_relayArsecPtr;
  LabRelay *_relayDesBrPtr;
  LabRelay *_relayDesWtPtr;
  LabRelay *_relaySysPowerPtr;
  boolean _autoDes;
  int _lastHumidity;
  unsigned int _arsecCycles;
  unsigned int _desbrCycles;
  unsigned int _deswtCycles;
  int _countDown;
  boolean _pingController;
  boolean _pingDome;
  boolean _pingShutter;
  boolean _pingScope;
  boolean _fullSync;
  
};

#endif

