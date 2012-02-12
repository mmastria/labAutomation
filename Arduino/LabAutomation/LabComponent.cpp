#include "LabComponent.h"
#include <util/delay.h>

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
  else {
    doEvent();
  }
}

void LabComponent::doEvent() {
  //DUMMY
}

void LabComponent::delay_ms(unsigned int time) { 
  while (time--) 
    _delay_ms(1); 
} 

