#ifndef __LAB_COMMAND__
#define __LAB_COMMAND__

#include <Arduino.h>

typedef enum {  SHUTTER_EVENT = 0, SHUTTER_EVENT_STOP, SHUTTER_EVENT_OPEN, SHUTTER_EVENT_CLOSE,
                SHUTTER_STATE,     SHUTTER_STATE_UNKNOWN, SHUTTER_STATE_CLOSED, SHUTTER_STATE_OPENED, SHUTTER_STATE_CLOSING, SHUTTER_STATE_OPENING} command_e;

class LabCommand {

  public:
  
  LabCommand();

  command_e cmd;
  char* getName();

};

#endif

