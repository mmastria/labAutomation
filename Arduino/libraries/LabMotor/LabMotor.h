#ifndef __LAB_MOTOR__
#define __LAB_MOTOR__

#include <Arduino.h>
#include "../LabComponent/LabComponent.h"
#include "../LabSwitch/LabSwitch.h"
#include "../LabRelay/LabRelay.h"

class LabMotor : public LabComponent {
	
	public:
	
	LabMotor();

	void forward();
	void reverse();
	void off();

	boolean isForward();
	boolean isReverse();
	boolean isOff();
	
	boolean isSwitchForwardOn();
	boolean isSwitchReverseOn();
	
	void setSwitchForward(LabSwitch *switchPtr);
	void setSwitchReverse(LabSwitch *switchPtr);
	void setRelayForward(LabRelay *relayPtr);
	void setRelayReverse(LabRelay *relayPtr);
		
	private:

	LabSwitch *_switchForwardPtr;
	LabSwitch *_switchReversePtr;
	LabRelay *_relayForwardPtr;
	LabRelay *_relayReversePtr;

};

#endif