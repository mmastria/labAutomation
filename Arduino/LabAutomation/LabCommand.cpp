#include "LabCommand.h"

const char* command_name[] = { 
  "<event>", "Stop", "Open", "Close", 
  "<state>", "Semi-Opened", "Closed", "Opened", "Closing", "Opening", "Error",
  "<event>", "Stop", "Go-Right", "Go-Left",
  "<state>", "Stopped", "Going-Right", "Going-Left" };

LabCommand::LabCommand() {
}

const char* LabCommand::getName() {
  return command_name[cmd];
}

