#include "LabComponent.h"

LabComponent::LabComponent() {
}

void LabComponent::setComponent(LabComponent *componentPtr) {
	if (componentPtr!=NULL) {
		_componentPtr=componentPtr;
	}
}

void LabComponent::callEvent() {
	if (_componentPtr!=NULL) {
		_componentPtr->doEvent();
	}
}

void LabComponent::doEvent() {
	//DUMMY
}
