#ifndef __LAB_SHUTTER__
#define __LAB_SHUTTER__

#include <Arduino.h>
#include "LabComponent.h"
#include "LabSwitch.h"
#include "LabRelay.h"
#include "LabMotor.h"

typedef enum { SHUTTER_UNKNOWN = 0, SHUTTER_CLOSED, SHUTTER_OPENED, SHUTTER_CLOSING, SHUTTER_OPENING, SHUTTER_ERROR } shutter_state_e;
typedef enum { SHUTTER_NONE = 0, SHUTTER_STATUS, SHUTTER_CLOSE, SHUTTER_OPEN } shutter_event_e;

class LabShutter : public LabComponent {
	
  public:
	
   LabShutter();
   
   void open();
   void close();
   void stop();
   
   void setMotor(LabMotor *motorPtr);

	
private:

  LabMotor *_motorPtr;

};

#endif
