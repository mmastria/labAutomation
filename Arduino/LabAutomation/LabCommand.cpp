#include "LabCommand.h"

char* command_name[] = { "<event>", "Stop", "Open", "Close", "<state>", "Unknown", "Closed", "Opened", "Closing", "Opening" };

LabCommand::LabCommand() {
}

char* LabCommand::getName() {
  return command_name[cmd];
}
