#ifndef __LAB_COMMAND__
#define __LAB_COMMAND__

#include <Arduino.h>

typedef enum { CMD_STOP = 0, CMD_OPEN, CMD_CLOSE } command_e;

class LabCommand {

  public:
  
  LabCommand();

  command_e cmd;

};

#endif
