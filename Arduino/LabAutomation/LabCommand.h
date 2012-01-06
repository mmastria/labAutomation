#ifndef __LAB_COMMAND__
#define __LAB_COMMAND__

#include <Arduino.h>

typedef enum {  CMD_STOP = 0, CMD_OPEN, CMD_CLOSE,
                SHUTTER_STATE, SHUTTER_STATE_UNKNOWN, SHUTTER_STATE_CLOSED, SHUTTER_STATE_OPENED, SHUTTER_STATE_CLOSING, SHUTTER_STATE_OPENING, SHUTTER_STATE_ERROR} command_e;

//const char* command_name[] = { "Stop", "Open", "Close", "<Shutter>", "Unknown", "Closed", "Opened", "Closing", "Opening", "Error" };

class LabCommand {

  public:
  
  LabCommand();

  command_e cmd;

};

#endif
