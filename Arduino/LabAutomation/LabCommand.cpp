#include "LabCommand.h"

char* command_name[] = { 
  "<event>", "Stop", "Open", "Close", "<state>", "Semi-Opened", "Closed", "Opened", "Closing", "Opening", "Error" };

LabCommand::LabCommand() {
}

char* LabCommand::getName() {
  return command_name[cmd];
}

