#include "LabSwitch.h"

LabSwitch::LabSwitch() {
}

LabSwitch::LabSwitch(byte pinSwitch) {
	_pinSwitch = pinSwitch;
	pinMode(_pinSwitch, INPUT);
}

boolean LabSwitch::isOn() {
	if (digitalRead(_pinSwitch) == HIGH)
    	return true;
  	else
    	return false;
}

boolean LabSwitch::isOff() {
	return !isOn();
}

void LabSwitch::event() {
	Serial.print("_LabSwitch::event_:_pin_");
	Serial.print(_pinSwitch, DEC);
	Serial.print("_:_read_");
	Serial.println(digitalRead(_pinSwitch));
  if (_callback)
    (*_callback)();
}

void LabSwitch::attach(callbackFunction callback)
{
	_callback = callback;
}

void LabSwitch::detach()
{
	_callback = NULL;
}
