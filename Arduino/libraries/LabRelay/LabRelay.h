#ifndef __LAB_RELAY__
#define __LAB_RELAY__

#include <Arduino.h>

class LabRelay {
	
	public:
	
	LabRelay();
	LabRelay(byte pinRelay);
	void on();
	void off();
	boolean getState();
		
	private:
	
	byte _pinRelay;
	boolean _state;
};

#endif