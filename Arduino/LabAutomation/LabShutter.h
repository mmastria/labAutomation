#ifndef __LAB_SHUTTER__
#define __LAB_SHUTTER__

#include <Arduino.h>
#include <RF24.h>
#include "LabComponent.h"
#include "LabSwitch.h"
#include "LabRelay.h"
#include "LabMotor.h"
#include "LabCommand.h"

typedef enum { SHUTTER_UNKNOWN = 0, SHUTTER_CLOSED, SHUTTER_OPENED, SHUTTER_CLOSING, SHUTTER_OPENING, SHUTTER_ERROR } shutter_state_e;
typedef enum { SHUTTER_NONE = 0, SHUTTER_STATUS, SHUTTER_CLOSE, SHUTTER_OPEN } shutter_event_e;

//const char* shutter_state_name[] = { "Unknown", "Closed", "Opened", "Closing", "Opening", "Error" };
//const char* shutter_event_name[] = { "None", "Status", "Close", "Open" };

const uint64_t pipes[4] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL };

class LabShutter : public LabComponent {
	
  public:
	
   LabShutter();
   
   void open();
   void close();
   void stop();
   
   void doEvent();
   
   void setMotor(LabMotor *motorPtr);
   void setRadio(RF24 *radioPtr);
   
   byte getState();
	
private:

  LabMotor *_motorPtr;
  LabCommand command;
  RF24 *_radioPtr;

};

#endif
