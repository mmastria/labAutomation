#ifndef __LAB_COMMAND__
#define __LAB_COMMAND__

#include <Arduino.h>

typedef enum {  
  SHUTTER_EVENT = 0, SHUTTER_EVENT_STOP, SHUTTER_EVENT_OPEN, SHUTTER_EVENT_CLOSE,
  SHUTTER_STATE,     SHUTTER_STATE_SEMIOPENED, SHUTTER_STATE_CLOSED, SHUTTER_STATE_OPENED, SHUTTER_STATE_CLOSING, SHUTTER_STATE_OPENING, SHUTTER_STATE_ERROR,
  DOME_EVENT,        DOME_EVENT_STOP, DOME_EVENT_RIGHT, DOME_EVENT_LEFT,
  DOME_STATE,        DOME_STATE_STOPPED, DOME_STATE_RIGHT, DOME_STATE_LEFT, DOME_STATE_ERROR} 
command_e;

class LabCommand {

public:

  LabCommand();

  volatile command_e cmd;
  const char* getName();

};

#endif


