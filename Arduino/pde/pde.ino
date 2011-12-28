/*
   CoreSystem

   Manage Main Loop to control some electrical feature
   */

#include <inttypes.h>

//#include <Time.h>
//#include <TimeAlarms.h>

// niva add features
//#include <Utils.h>
#include <Traces.h>
// #include <PushButton.h>
// #include <PinManager.h>
#include <FunctionalTasks.h>
#include <FunctionalWrapper.h>

#include <Wire.h>
#include <LiquidCrystal.h>
//#include <DS1307.h> // written by  mattt on the Arduino forum and modified by D. Sjunnesson

Traces Tracer;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
FunctionalTasks FuncTask;



//
//  SETUP
//

void setup()  {

	// SERIAL
	Serial.begin(9600);

	// LCD
	  lcd.begin(16, 2);
	  lcd.setCursor(0, 0);
	  lcd.clear();
	  delay(2000);
	Tracer.Print("INIT SCREEN DONE");

	// pass lcd to tracer
	Tracer.setLcd(&lcd);
	FuncTask.setTracer(&Tracer);

	// Bind the wrapper to FunctionalTasks p and call procedure
	FunctionalWrapper::setObj(FuncTask);



	// Alarm.timerRepeat(4, p);
	FunctionalWrapper::AfficheDateGlue();
}

//
//  LOOP
//
void loop()  {


}
 
