#ifndef __LAB_SHUTTER__
#define __LAB_SHUTTER__

#include <Arduino.h>
#include "../LabRelay/LabRelay.h"
#include "../LabSwitch/LabSwitch.h"

typedef enum { SHUTTER_UNKNOWN = 0, SHUTTER_CLOSED, SHUTTER_OPENED, SHUTTER_CLOSING, SHUTTER_OPENING, SHUTTER_ERROR } shutter_state_e;
typedef enum { SHUTTER_NONE = 0, SHUTTER_STATUS, SHUTTER_CLOSE, SHUTTER_OPEN } shutter_event_e;

class LabShutter {
	
	public:
	
	LabShutter();
	LabShutter(LabRelay relayOpen, LabRelay relayClose, LabSwitch switchOpened, LabSwitch switchClosed);
	void callEvent(shutter_event_e event);
	void doEvent();
	void doStop();
	
	private:
	
	LabRelay _relayOpen;
	LabRelay _relayClose;
	
	LabSwitch _switchOpened;
	LabSwitch _switchClosed;
	
	shutter_state_e _state;
	shutter_event_e _event;
	
	void doClose();
	void doOpen();
};

#endif