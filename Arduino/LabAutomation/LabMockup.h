#ifndef __LAB_MOCKUP__
#define __LAB_MOCKUP__

#include <Arduino.h>
#include "LabComponent.h"

class LabMockup : public LabComponent {
	
	public:
	
	LabMockup();

	int getValue();
	
	void doEvent();
			
	private:
	
	int _value;

};

#endif
