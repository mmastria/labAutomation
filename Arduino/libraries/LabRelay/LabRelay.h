#ifndef __LAB_RELAY__
#define __LAB_RELAY__

#include <Arduino.h>
#include "../LabComponent/LabComponent.h"

class LabRelay : public LabComponent {
	
	public:
	
	LabRelay();
	LabRelay(byte pinRelay);

	void on();
	void off();

	boolean isOn();
	boolean isOff();
	
	void doEvent();
			
	private:
	
	byte _pinRelay;
	boolean _state;

};

#endif