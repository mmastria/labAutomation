#include "LabCommand.h"

const char* command_name[] = { 
  "<shutter-event>", "Stop", "Open", "Close", 
  "<shutter-state>", "Semi-Opened", "Closed", "Opened", "Closing", "Opening", "Shutter-Error",
  "<dome-event>", "Stop", "Go-Right", "Go-Left",
  "<dome-state>", "Stopped", "Going-Right", "Going-Left", "Dome-Error",
  "<scope-event>", "Get-TH",
  "<scope-state>", "Temp-Humid", "Scope-Error" };

LabCommand::LabCommand() {
}

const char* LabCommand::getName() {
  return command_name[cmd];
}

