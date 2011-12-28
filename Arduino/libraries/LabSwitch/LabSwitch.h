#ifndef __LAB_SWITCH__
#define __LAB_SWITCH__

#include <Arduino.h>

class LabSwitch {
	
	public:
	
	LabSwitch();
	LabSwitch(byte pinSwitch);
	boolean isOn();
	boolean isOff();
	void event();
	
	private:
	
	byte _pinSwitch;
};

#endif