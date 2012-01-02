#include "LabShutter.h"

LabShutter::LabShutter() {
}

LabShutter::LabShutter(LabRelay relayOpen, LabRelay relayClose, LabSwitch switchOpened, LabSwitch switchClosed) {
	_relayOpen = relayOpen;
	_relayClose = relayClose;
	_switchOpened = switchOpened;
	_switchClosed = switchClosed;
	_event = SHUTTER_NONE;
	_state = SHUTTER_UNKNOWN;
	if (_switchClosed.isOn()) {
		_state = SHUTTER_CLOSED;
	}
	else if(_switchOpened.isOn()) {
		_state = SHUTTER_OPENED;
	}
}

void LabShutter::callEvent(shutter_event_e event) {
	_event = event;
}

void LabShutter::doEvent() {
	if (_event!=SHUTTER_NONE) {
		switch(_event) {
			case SHUTTER_CLOSE:
				doClose();
				break;
			case SHUTTER_OPEN:
				doOpen();
				break;
		}
	}
	_event = SHUTTER_NONE;
}

void LabShutter::doClose() {
	Serial.println("_LabShutter::doClose_");
	_relayOpen.off();
	if (_state!=SHUTTER_CLOSED) {
		_relayClose.on();
	}	
}

void LabShutter::doOpen() {
	Serial.println("_LabShutter::doOpen_");
	_relayClose.off();
	if(_state!=SHUTTER_OPENED) {
		_relayOpen.on();
	}
}

void LabShutter::doStop() {
	Serial.println("_LabShutter::doStop_");
	_relayOpen.off();
	_relayClose.off();
}	