#include "LabDome.h"
#ifdef __DOME__

LabDome::LabDome() {
  _fullSync=false;
  _leftHit=false;
  _leftHited=false;
  _rightHit=false;
  _rightHited=false;
  _lastTurnLeft=false;
  _closed=true; // block sync
  _opened=false;
}

void LabDome::right() {
  #ifdef __DEBUG__
  Serial.println("right");
  #endif
  _motorPtr->forward();
}

void LabDome::left() {
  #ifdef __DEBUG__
  Serial.println("left");
  #endif
  _motorPtr->reverse();
}

void LabDome::stop() {
  #ifdef __DEBUG__
  Serial.println("stop");
  #endif
  _motorPtr->off();
}

void LabDome::home() {
  #ifdef __DEBUG__
  Serial.println("home");
  #endif
  _encoderPtr->reset();
}

void LabDome::change() {
  if(_motorPtr->isForward()) {
    _encoderPtr->add();
  }
  if(_motorPtr->isReverse()) {
    _encoderPtr->subtract();
  }
}

void LabDome::setMotor(LabMotor *motorPtr) {
  _motorPtr=motorPtr;
}

void LabDome::setEncoder(LabEncoder *encoderPtr) {
  _encoderPtr=encoderPtr;
}

void LabDome::setSwitchHome(LabSwitch *switchHomePtr) {
  _switchHomePtr=switchHomePtr;
}

void LabDome::setSwitch220v(LabSwitch *switch220vPtr) {
  _switch220vPtr=switch220vPtr;
}

void LabDome::timer() {
}

payload_t LabDome::getState() {
  #ifdef __DEBUG__
  Serial.println("getState");
  #endif
  payload_t payload;
  payload=getData();
  payload.action=DOME_RETURNSTATE;
  return payload;
}
  
payload_t LabDome::getTimer() {
  #ifdef __DEBUG__
  Serial.println("getTimer");
  #endif
  payload_t payload;
  payload=getData();
  payload.action=DOME_TIMER;
  return payload;
}
  
payload_t LabDome::getData() {
  payload_t r;
  r.b1=_motorPtr->isForward();     // OnRight
  r.b2=_motorPtr->isReverse();     // OnLeft
  r.b3=_switchHomePtr->isOn();     // OnHome
  r.b4=_switch220vPtr->isOn();     // 220v
  r.i1=(_encoderPtr->getValueDeg()*10); // Azimute
  return r;
}

void LabDome::startDelay() {
  #ifdef __DEBUG__
  Serial.println("startDelay");
  #endif
  _switch220vPtr->startDelay();
}

boolean LabDome::checkDelay() {
  return _switch220vPtr->checkDelay();
}

void LabDome::fullSync(boolean fullSync) {
  #ifdef __DEBUG__
  Serial.println("fullSync");
  #endif
  _fullSync=fullSync;
}

boolean LabDome::fullSyncOn() {
  return _fullSync;
}

void LabDome::scopeSync(payload_t payload) {
  _leftHit=(boolean)payload.b1;
  _rightHit=(boolean)payload.b2;
}

void LabDome::shutterSync(payload_t payload) {
  _closed=(boolean)payload.b4;
  _opened=(boolean)payload.b3;
}

void LabDome::checkSync() {
  boolean leftHit;
  boolean rightHit;
  boolean leftEnabled;
  boolean rightEnabled;
  if(_fullSync) {

    #ifdef __DEBUG__
      Serial.print(" leftHit:");
      Serial.print(_leftHit);
      Serial.print(" reverse:");
      Serial.print(_motorPtr->isReverse());
      Serial.print("  rightHit:");
      Serial.print(_rightHit);
      Serial.print(" forward:");
      Serial.print(_motorPtr->isForward());
      Serial.print(" closed:");
      Serial.println(_closed);
      Serial.flush();
      delay(20);
    #endif

    if(_closed) {
      if(!_motorPtr->isOff())
        _motorPtr->off();
    }
    else {
      leftHit=_leftHit;
      rightHit=_rightHit;
  
      // nenhum - desligar motor
      if(!leftHit and !rightHit) {
        if(!_motorPtr->isOff())
          _motorPtr->off();
      }
      else
      {
        // ambos - define o ultimo valido
        if(leftHit and rightHit) {
          if(_lastTurnLeft) {
            leftEnabled=true;
            rightEnabled=false;
          }
          else {
            leftEnabled=false;
            rightEnabled=true;
          }
        }
        else {
            rightEnabled=true;
            leftEnabled=true;
        }      
    
        // esquerda
        if(leftHit and leftEnabled) {
          if(_leftHited) {
            _lastTurnLeft=true;
            _motorPtr->reverse();
          }
          else
            _leftHited=true;
        }
        else
          _leftHited=false;
    
        // direita
        if(rightHit and rightEnabled) {
          if(_rightHited) {
            _lastTurnLeft=false;
            _motorPtr->forward();
          }
          else
            _rightHited=true;
        }
        else
          _rightHited=false;
      }
    }
  }
}

#endif


