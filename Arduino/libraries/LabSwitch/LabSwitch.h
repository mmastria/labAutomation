#ifndef __LAB_SWITCH__
#define __LAB_SWITCH__

#include <Arduino.h>

extern "C" {
    typedef void (*callbackFunction)(void);
}

class LabSwitch {
	
	public:
	
	LabSwitch();
	LabSwitch(byte pinSwitch);
	boolean isOn();
	boolean isOff();
	void event();
	void attach(callbackFunction callback);
  void detach();
	
	private:
	
	byte _pinSwitch;
  callbackFunction _callback;

};

#endif