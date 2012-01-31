#ifndef __LAB_ENCODER__
#define __LAB_ENCODER__

#include <Arduino.h>
#include "LabComponent.h"

class LabEncoder : public LabComponent {
	
	public:
	
	LabEncoder();
	LabEncoder(byte pinEncoder);

	void doEvent();
	void reset();

	long getValue();

	private:
	
	byte _pinEncoder;
	volatile long _value;

};

#endif
