#ifndef __LAB_SWITCH__
#define __LAB_SWITCH__

#include <Arduino.h>
#include <../LabRelay/LabRelay.h>

class LabSwitch {
	
	public:
	
	LabSwitch();
	LabSwitch(byte pinSwitch);
	
	boolean isOn();
	boolean isOff();
	void event();
	
	void setRelay(LabRelay *relayPtr);
	
	private:
	
	byte _pinSwitch;
	LabRelay * _relayPtr;
	
};

#endif