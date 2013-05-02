#ifndef __LAB_SYSTEM__
#define __LAB_SYSTEM__

#include "Arduino.h"

#define __DEBUG__
//#define __CONTROLLER__  // Serial 1
#define __DOME__        // Serial 2
//#define __SHUTTER__     // Serial 3
//#define __SCOPE__       // Serial 4

#define RELEASE 13
// 01-May-2013

#define TIMER_INTERVAL 500 // 0.5 second

#ifdef __DOME__
#define SWITCH_DELAY 60 // cycles of TIMER_INTERVAL
#endif

#ifdef __SCOPE__
#define TEMPERATURE_MAX_DEV 2
#define TEMPERATURE_MAX_DISCARDS 5
#endif

#ifdef __CONTROLLER__

#define DISPLAY_INTERVAL 16 // cycles of TIMER_INTERVAL
#define PING_INTERVAL 10    // cycles of TIMER_INTERVAL

#define HUMIDITY_1 47
#define HUMIDITY_2 52
#define HUMIDITY_3 57
#define DES_SLEEP 240
#define DES_CYCLES_SLEEP 600 // 5min
#define DES_CYCLES_LOCK 1200 // 10min
#define DES_CYCLES_MAX 7200 // 1h

enum {
  
  MB_CONTROLLER_ARSEC,       // 0 R/W
  MB_CONTROLLER_AUTODES,     // 1 R/W
  MB_CONTROLLER_DESBR,       // 2 R/W
  MB_CONTROLLER_DESWT,       // 3 R/W
  MB_CONTROLLER_FULLSYNC,    // 4 R/W
  MB_CONTROLLER_PING_ON,     // 5
  MB_CONTROLLER_SYSPOWER,    // 6 R/W
  MB_CONTROLLER_TIMER_COUNT, // 7
  
  MB_DOME_220V,              // 8
  MB_DOME_AZIMUTE,           // 9
  MB_DOME_ON_HOME,           // 10
  MB_DOME_ON_LEFT,           // 11 R/W
  MB_DOME_ON_RIGHT,          // 12 R/W
  MB_DOME_PING_ON,           // 13
  MB_DOME_TIMER_COUNT,       // 14
    
  MB_SCOPE_HUMIDITY,         // 15
  MB_SCOPE_PING_ON,          // 16
  MB_SCOPE_STEPS,            // 17 R/W
  MB_SCOPE_TEMPERATURE,      // 18
  MB_SCOPE_TIMER_COUNT,      // 19
  MB_SCOPE_WALL_LEFT,        // 20
  MB_SCOPE_WALL_RIGHT,       // 21

  MB_SHUTTER_CLOSED,         // 22
  MB_SHUTTER_CLOSING,        // 23 R/W
  MB_SHUTTER_OPENED,         // 24
  MB_SHUTTER_OPENING,        // 25 R/W
  MB_SHUTTER_PING_ON,        // 26
  MB_SHUTTER_TIMER_COUNT,    // 27

  MB_STP_FOCUS_INWARD,      // 28 W
  MB_STP_FOCUS_OUTWARD,     // 29 W

  MB_REGS
};

#endif

typedef enum { NOTHING,

               DOME_STOP, 
               DOME_RIGHT, 
               DOME_LEFT, 
               DOME_SENSORHOME, 
               DOME_SENSOR220V, 
               DOME_GETSTATE, DOME_RETURNSTATE, 
               DOME_GETTIMER, DOME_TIMER,
               
               SHUTTER_STOP, 
               SHUTTER_OPEN, 
               SHUTTER_CLOSE, 
               SHUTTER_SENSOROPENED, 
               SHUTTER_SENSORCLOSED, 
               SHUTTER_GETSTATE, SHUTTER_RETURNSTATE, 
               SHUTTER_GETTIMER, SHUTTER_TIMER,
               SHUTTER_SENDSYNC, SHUTTER_SYNC,
               
               SCOPE_GETSTATE, SCOPE_RETURNSTATE, 
               SCOPE_GETTIMER, SCOPE_TIMER, 
               SCOPE_SENDSYNC, SCOPE_SYNC,
               
               FOCUS_INWARD, 
               FOCUS_OUTWARD, 
               FOCUS_1, 
               FOCUS_10, 
               FOCUS_100,
               
               DESARSEC_CHANGE, 
               DESBROWN_CHANGE, 
               DESWHITE_CHANGE, 
               AUTODES_CHANGE, 
               
               SYSPOWER_CHANGE, 
               
               CONTROLLER_GETSTATE, CONTROLLER_RETURNSTATE, 
               CONTROLLER_GETTIMER, CONTROLLER_TIMER, 
               
               FULL_SYNC  } action_e;

struct payload_t {
  action_e action;
  byte b1;
  byte b2;
  byte b3;
  byte b4;
  int i1;
};

#ifndef __CONTROLLER__
static const char *action_desc[] =
             { "NOTHING",

               "DOME_STOP", 
               "DOME_RIGHT", 
               "DOME_LEFT", 
               "DOME_SENSORHOME", 
               "DOME_SENSOR220V", 
               "DOME_GETSTATE", "DOME_RETURNSTATE", 
               "DOME_GETTIMER", "DOME_TIMER",
               
               "SHUTTER_STOP", 
               "SHUTTER_OPEN", 
               "SHUTTER_CLOSE", 
               "SHUTTER_SENSOROPENED", 
               "SHUTTER_SENSORCLOSED", 
               "SHUTTER_GETSTATE", "SHUTTER_RETURNSTATE", 
               "SHUTTER_GETTIMER", "SHUTTER_TIMER",
               "SHUTTER_SENDSYNC", "SHUTTER_SYNC",
               
               "SCOPE_GETSTATE", "SCOPE_RETURNSTATE", 
               "SCOPE_GETTIMER", "SCOPE_TIMER", 
               "SCOPE_SENDSYNC", "SCOPE_SYNC",
               
               "FOCUS_INWARD", 
               "FOCUS_OUTWARD", 
               "FOCUS_1", 
               "FOCUS_10", 
               "FOCUS_100",
               
               "DESARSEC_CHANGE", 
               "DESBROWN_CHANGE", 
               "DESWHITE_CHANGE", 
               "AUTODES_CHANGE", 
               
               "SYSPOWER_CHANGE", 
               
               "CONTROLLER_GETSTATE", "CONTROLLER_RETURNSTATE", 
               "CONTROLLER_GETTIMER", "CONTROLLER_TIMER", 
               
               "FULL_SYNC"  };

#endif

// CONTROLLER
// b1: relayArsec = ArsecOn
// b2: relayDesBr = DesBrOn
// b3: relayDesWt = DesWtOn
// b4: relaySysPower = SysPowerOn

// DOME
// b1: motorForward = OnRight
// b2: motorReverse = OnLeft
// b3: switchHome = OnHome
// b4: switch220v = 220v
// i1: azimute*10 = Azimute

// SHUTTER
// b1: motorForward = Opening
// b2: motorReverse = Closing
// b3: switchOpened = Opened 
// b4: switchClosed = Closed

// SCOPE
// b1: wallLeft
// b2: wallRight
// b3: steps
// b4: humidity
// i1: temperature*10


#endif

// criar sync-on (9) / sync-off (9) - implementar logica
// na falha do 220v, cancelar sync e fechar trapeira
// nao permitir abrir trapeira sem 220v


