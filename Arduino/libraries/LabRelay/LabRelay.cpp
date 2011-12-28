#include "LabRelay.h"

LabRelay::LabRelay() {
}

LabRelay::LabRelay(byte pinRelay) {
	_pinRelay = pinRelay;
	_state = HIGH;
	digitalWrite(_pinRelay, _state);
	pinMode(_pinRelay, OUTPUT);
}

void LabRelay::on() {
	_state = LOW;
	digitalWrite(_pinRelay, _state);
}

void LabRelay::off() {
	_state = HIGH;
	digitalWrite(_pinRelay, _state);
}

boolean LabRelay::getState() {
	return _state;
}
