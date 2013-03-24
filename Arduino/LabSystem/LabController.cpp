#include "LabController.h"

LabController::LabController() {
  #ifdef __CONTROLLER__
  _countDown=DISPLAY_INTERVAL;
  _arsecCycles=DES_CYCLES_SLEEP;
  _desbrCycles=DES_CYCLES_SLEEP;
  _deswtCycles=DES_CYCLES_SLEEP;
  #endif
  _autoDes=true;
  _lastHumidity=0;
  _pingController=false;   
  _pingDome=false;
  _pingShutter=false;
  _pingScope=false;
  _fullSync=false;
}

void LabController::fullSync(boolean fullSync) {
  _fullSync=fullSync;
}

void LabController::setLcd(LiquidCrystal *lcdPtr) {
  _lcdPtr=lcdPtr;
}

void LabController::setRelayArsec(LabRelay *relayArsecPtr) {
  _relayArsecPtr=relayArsecPtr;
}

void LabController::setRelayDesBr(LabRelay *relayDesBrPtr) {
  _relayDesBrPtr=relayDesBrPtr;
}

void LabController::setRelayDesWt(LabRelay *relayDesWtPtr) {
  _relayDesWtPtr=relayDesWtPtr;
}

void LabController::setRelaySysPower(LabRelay *relaySysPowerPtr) {
  _relaySysPowerPtr=relaySysPowerPtr;
}

void LabController::timer() {
  _arsecCycles++;
  _desbrCycles++;
  _deswtCycles++;
  if(_countDown>0) {
    _countDown--;
    if(_countDown==0) {
      _lcdPtr->clear();
      #ifndef __DEBUG__
        _lcdPtr->setCursor(0,0);
        _lcdPtr->print("CNTR:");
        _lcdPtr->setCursor(8,0);
        _lcdPtr->print("DOME:");
        _lcdPtr->setCursor(0,1);
        _lcdPtr->print("SHUT:");
        _lcdPtr->setCursor(8,1);
        _lcdPtr->print("SCOP:");
      #endif
    }
  }
}

void LabController::lcdClear() {
  _lcdPtr->clear();
}

void LabController::lcdSetCursor(uint8_t col, uint8_t row) {
  _lcdPtr->setCursor(col, row);
}

void LabController::lcdPrint(const char c[]) {
  #ifdef __CONTROLLER__
  _countDown=DISPLAY_INTERVAL;
  _lcdPtr->print(c);
  #endif
}

void LabController::lcdPrint(int i, int j) {
  #ifdef __CONTROLLER__
  _countDown=DISPLAY_INTERVAL;
  _lcdPtr->print(i, j);
  #endif
};

void LabController::lcdPrint(double d, int i) {
  #ifdef __CONTROLLER__
  _countDown=DISPLAY_INTERVAL;
  _lcdPtr->print(d, i);
  #endif
};

void LabController::lcdPrint(char c) {
  #ifdef __CONTROLLER__
  _countDown=DISPLAY_INTERVAL;
  _lcdPtr->print(c);
  #endif
};

void LabController::lcdPrint(unsigned char c, int i) {
  #ifdef __CONTROLLER__
  _countDown=DISPLAY_INTERVAL;
  _lcdPtr->print(c, i);
  #endif
};

void LabController::lcdPrint(unsigned int i, int j) {
  #ifdef __CONTROLLER__
  _countDown=DISPLAY_INTERVAL;
  _lcdPtr->print(i, j);
  #endif
};

void LabController::lcdPrint(long l, int i) {
  #ifdef __CONTROLLER__
  _countDown=DISPLAY_INTERVAL;
  _lcdPtr->print(l, i);
  #endif
};

void LabController::lcdPrint(unsigned long l, int i) {
  #ifdef __CONTROLLER__
  _countDown=DISPLAY_INTERVAL;
  _lcdPtr->print(l, i);
  #endif
};

/*
124 - pipe
126 - seta direita
127 - seta esquerda
162 - diagonal superior esquerda
163 - diagonal inferior direita
165 - quadrado pequeno
219 - quadrado grande
255 - quadrado full
*/

void LabController::lcdPingController(boolean live) {
  if(_countDown==0) {
    _pingController=!_pingController;
    #ifndef __DEBUG__
      _lcdPtr->setCursor(6,0);
      if(live)
        _lcdPtr->print(_pingController ? (char) 165 : (char) 219);
      else
        _lcdPtr->print('X');
    #else
      _lcdPtr->setCursor(0,0);
      _lcdPtr->print(_arsecCycles);
      _lcdPtr->print(' ');
      _lcdPtr->setCursor(8,0);
      _lcdPtr->print(_desbrCycles);
      _lcdPtr->print(' ');
      _lcdPtr->setCursor(0,1);
      _lcdPtr->print(_deswtCycles);
      _lcdPtr->print(' ');
    #endif
  }
};

void LabController::lcdPingDome(boolean live) {
  if(_countDown==0) {
    _pingDome=!_pingDome;
    #ifndef __DEBUG__
      _lcdPtr->setCursor(14,0);
      if(live)
        _lcdPtr->print(_pingDome ? (char) 165 : (char) 219);
      else
        _lcdPtr->print('X');
      if(_fullSync)
        _lcdPtr->print(_pingDome ? (char) 126 : (char) 127);
      else
        _lcdPtr->print(' ');
    #endif
  }
};

void LabController::lcdPingShutter(boolean live) {
  if(_countDown==0) {
    _pingShutter=!_pingShutter;
    #ifndef __DEBUG__
      _lcdPtr->setCursor(6,1);
      if(live)
        _lcdPtr->print(_pingShutter ? (char) 165 : (char) 219);
      else
        _lcdPtr->print('X');
    #endif
  }
};

void LabController::lcdPingScope(boolean live) {
  if(_countDown==0) {
    _pingScope=!_pingScope;
    #ifndef __DEBUG__
      _lcdPtr->setCursor(14,1);
      if(live)
        _lcdPtr->print(_pingScope ? (char) 165 : (char) 219);
      else
        _lcdPtr->print('X');
    #endif
  }
};

void LabController::desarsecChange() {
  _autoDes=false;
  _arsecCycles=0;
  if(_relayArsecPtr->isOn())
    _relayArsecPtr->off();
  else
    _relayArsecPtr->on();
};

void LabController::desbrownChange() {
  _autoDes=false;
  _desbrCycles=0;
  if(_relayDesBrPtr->isOn())
    _relayDesBrPtr->off();
  else
    _relayDesBrPtr->on();
};

void LabController::deswhiteChange() {
  _autoDes=false;
  _deswtCycles=0;
  if(_relayDesWtPtr->isOn())
    _relayDesWtPtr->off();
  else
    _relayDesWtPtr->on();
};

void LabController::autodesChange() {
  _autoDes=!_autoDes;
}

void LabController::syspowerChange() {
  if(_relaySysPowerPtr->isOn())
    _relaySysPowerPtr->off();
  else
    _relaySysPowerPtr->on();
};

payload_t LabController::getState() {
  payload_t payload;
  payload=getData();
  payload.action=CONTROLLER_RETURNSTATE;
  return payload;
}

payload_t LabController::getTimer() {
  payload_t payload;
  payload=getData();
  payload.action=CONTROLLER_TIMER;
  return payload;
}
  
payload_t LabController::getData() {
  payload_t r;
  r.b1=_relayArsecPtr->isOn(); // ArsecOn
  r.b2=_relayDesBrPtr->isOn(); // DesBrOn
  r.b3=_relayDesWtPtr->isOn(); // DesWtOn
  r.b4=_relaySysPowerPtr->isOn(); // SysPowerOn
  r.i1=_autoDes; // AutoDes
  return r;
}

void LabController::setLastHumidity(int lastHumidity) {
  _lastHumidity=lastHumidity;
};

void LabController::checkAutodes() {
  #ifdef __CONTROLLER__
  LabRelay *desA;
  LabRelay *desB;
  LabRelay *desC;
  unsigned int *cyclesA;
  unsigned int *cyclesB;
  unsigned int *cyclesC;
  if(_autoDes) {

    // SORT
    if(_arsecCycles<_desbrCycles) {
      if(_desbrCycles<_deswtCycles) {
        // _arsecCycles < _desbrCycles < _deswtCycles
        desA=_relayArsecPtr;
        desB=_relayDesBrPtr;
        desC=_relayDesWtPtr;
        cyclesA=&_arsecCycles;
        cyclesB=&_desbrCycles;
        cyclesC=&_deswtCycles;
      }
      else {
        if(_arsecCycles<_deswtCycles) {
          // _arsecCycles < _deswtCycles < _desbrCycles
          desA=_relayArsecPtr;
          desB=_relayDesWtPtr;
          desC=_relayDesBrPtr;
          cyclesA=&_arsecCycles;
          cyclesB=&_deswtCycles;
          cyclesC=&_desbrCycles;
        }
        else {
          // _deswtCycles < _arsecCycles < _desbrCycles
          desA=_relayDesWtPtr;
          desB=_relayArsecPtr;
          desC=_relayDesBrPtr;
          cyclesA=&_deswtCycles;
          cyclesB=&_arsecCycles;
          cyclesC=&_desbrCycles;
        }
      }
    }
    else {
      if(_arsecCycles<_deswtCycles) {
        // _desbrCycles < _arsecCycles < _deswtCycles
        desA=_relayDesBrPtr;
        desB=_relayArsecPtr;
        desC=_relayDesWtPtr;
        cyclesA=&_desbrCycles;
        cyclesB=&_arsecCycles;
        cyclesC=&_deswtCycles;
      }
      else {
        if(_deswtCycles<_desbrCycles) {
          // _deswtCycles < _desbrCycles < _arsecCycles
          desA=_relayDesWtPtr;
          desB=_relayDesBrPtr;
          desC=_relayArsecPtr;
          cyclesA=&_deswtCycles;
          cyclesB=&_desbrCycles;
          cyclesC=&_arsecCycles;
        }
        else {
          // _desbrCycles < _arsecCycles < _deswtCycles
          desA=_relayDesBrPtr;
          desB=_relayArsecPtr;
          desC=_relayDesWtPtr;
          cyclesA=&_desbrCycles;
          cyclesB=&_arsecCycles;
          cyclesC=&_deswtCycles;
        }
      }
    }
  
    // CHECK MAX
    if(_relayArsecPtr->isOn() and _arsecCycles>DES_CYCLES_MAX) {
      _arsecCycles=0;
      _relayArsecPtr->off();
    }
    if(_relayDesBrPtr->isOn() and _desbrCycles>DES_CYCLES_MAX) {
      _desbrCycles=0;
      _relayDesBrPtr->off();
    }
    if(_relayDesWtPtr->isOn() and _deswtCycles>DES_CYCLES_MAX) {
      _deswtCycles=0;
      _relayDesWtPtr->off();
    }
    
    // 3 DESUMIDIFICADRES LIGADOS
    if(_lastHumidity>=HUMIDITY_3) {
      if(_relayArsecPtr->isOff() and _arsecCycles>DES_CYCLES_SLEEP) {
        _arsecCycles=0;
        _relayArsecPtr->on();
      }
      if(_relayDesBrPtr->isOff() and _desbrCycles>DES_CYCLES_SLEEP) {
        _desbrCycles=0;
        _relayDesBrPtr->on();
      }
      if(_relayDesWtPtr->isOff() and _deswtCycles>DES_CYCLES_SLEEP) {
        _deswtCycles=0;
        _relayDesWtPtr->on();
      }
    }
    else {

      // 2 DESUMIDIFICADORES LIGADOS / 1 DESLIGADO
      if(_lastHumidity>=HUMIDITY_2) {
        switch ((_relayArsecPtr->isOn() ? 1 : 0) + (_relayDesBrPtr->isOn() ? 1 : 0) + (_relayDesWtPtr->isOn() ? 1 : 0)) {
          case 0: // LIGAR 2
            if(*cyclesC>DES_CYCLES_SLEEP) {
              *cyclesC=0;
              desC->on();
            }
            if(*cyclesB>DES_CYCLES_SLEEP) {
              *cyclesB=0;
              desB->on();
            }
            break;
          case 1: // LIGAR 1
            if(desC->isOff() and *cyclesC>DES_CYCLES_SLEEP) {
              *cyclesC=0;
              desC->on();
            }
            else {
              if(desB->isOff() and *cyclesB>DES_CYCLES_SLEEP) {
                *cyclesB=0;
                desB->on();
              }
            }
            break;
          case 2: // OK
            break;
          case 3: // DESLIGAR 1
            if(*cyclesC>DES_CYCLES_LOCK) {
              *cyclesC=0;
              desC->off();
            }
            break;
        }
      }
      else {
        
        // 1 DESUMIDIFICADOR LIGADO / 2 DESLIGADOS
        if(_lastHumidity>=HUMIDITY_1) {
          switch ((_relayArsecPtr->isOn() ? 1 : 0) + (_relayDesBrPtr->isOn() ? 1 : 0) + (_relayDesWtPtr->isOn() ? 1 : 0)) {
            case 0: // LIGAR 1
              if(*cyclesC>DES_CYCLES_SLEEP) {
                *cyclesC=0;
                desC->on();
              }
              break;
            case 1: // OK
              break;
            case 2: // DESLIGAR 1
              if(desC->isOn() and *cyclesC>DES_CYCLES_LOCK) {
                *cyclesC=0;
                desC->off();
              }
              else {
                if(desB->isOn() and *cyclesB>DES_CYCLES_LOCK) {
                  *cyclesB=0;
                  desB->off();
                }
              }
              break;
            case 3: // DESLIGAR 2
              if(*cyclesC>DES_CYCLES_LOCK) {
                *cyclesC=0;
                desC->off();
              }
              if(*cyclesB>DES_CYCLES_LOCK) {
                *cyclesB=0;
                desB->off();
              }
              break;
          }
        }
        
        // 3 DESUMIDIFICADORES DESLIGADOS
        else {
          if(_relayArsecPtr->isOn() and _arsecCycles>DES_CYCLES_LOCK) {
            _arsecCycles=0;
            _relayArsecPtr->off();
          }
          if(_relayDesBrPtr->isOn() and _desbrCycles>DES_CYCLES_LOCK) {
            _desbrCycles=0;
            _relayDesBrPtr->off();
          }
          if(_relayDesWtPtr->isOn() and _deswtCycles>DES_CYCLES_LOCK) {
            _deswtCycles=0;
            _relayDesWtPtr->off();
          }
        }
      }
    }
  }
  #endif
}


