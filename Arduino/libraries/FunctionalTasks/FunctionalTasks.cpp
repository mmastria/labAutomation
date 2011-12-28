/*
   FunctionalTasks.cpp manage some utility own tasks to provide
   in my domotik managment

   12 Oct 2010 - First Version
   */

//#include "WProgram.h"
#include <Wire.h>
#include <Traces.h>
#include <FunctionalTasks.h>
// #include <PinManager.h>
#include <DS1307.h> // written by  mattt on the Arduino forum and modified by D. Sjunnesson
#include <Utils.h>

// MANAGER
//static PinManager PinMng;
//=============================================================================
/* Constructor & Destructor {{{1 */
FunctionalTasks::FunctionalTasks()
{
}
/* }}}1 */
//=============================================================================
/* Accessors {{{1 */
void FunctionalTasks::setTracer(Traces *TracerPtr) {

	if (  TracerPtr != NULL )
	{
		_Tracer = TracerPtr;
	}
}
/* }}}1 */
//=============================================================================
/* {{{1 TIME MANAGMENT */
void FunctionalTasks::setRealTimeClock() {

	//setTime(22,15,00,01,18,2010);

	_Tracer->Print("Heures du systeme embarque mise a jour.");
	// MODULE HORLOGE TEMPS REEL EMBARQUEE
	RTC.stop();
	// REGLAGE HEURE
	RTC.set(DS1307_HR   , horodatage::getHours());     // set the hours
	RTC.set(DS1307_MIN  , horodatage::getMinutes());     // set the minutes
	RTC.set(DS1307_SEC  , horodatage::getSeconds());     // set the seconds
	// REGLAGE DATE
	RTC.set(DS1307_DATE , 12);     // set the date
	RTC.set(DS1307_MTH  , 11);     // set the month
	RTC.set(DS1307_YR   , 10);     // set the year
	RTC.set(DS1307_DOW  , 4 );     // set the day of the week
	RTC.start();
}

void FunctionalTasks::getRealTimeClock() {

    _Tracer->BeginPrint(RTC.get(DS1307_HR  , true )); //read the hour and also update all the values by pushing in true
    Serial.print(":");
    Serial.print(RTC.get(DS1307_MIN , false)); //read  minutes without update (false)
    Serial.print(":");
    Serial.print(RTC.get(DS1307_SEC , false)); //read  seconds
    Serial.print("	");		  // some space for a more happy life
    Serial.print(RTC.get(DS1307_DATE, false)); //read  date
    Serial.print("/");
    Serial.print(RTC.get(DS1307_MTH , false)); //read  month
    Serial.print("/");
    Serial.print(RTC.get(DS1307_YR  , false)); //rea d year
	  Serial.println();
}

void FunctionalTasks::displayRealTimeClock() {

    _Tracer->BeginPrint(RTC.get(DS1307_HR  , true )); //read the hour and also update all the values by pushing in true
    _Tracer->BeginPrint(":");
    _Tracer->BeginPrint(RTC.get(DS1307_MIN , false)); //read  minutes without update (false)
    _Tracer->BeginPrint(":");
    _Tracer->EndPrint(RTC.get(DS1307_SEC , false)); //read  seconds
}
/* }}}1 */
//=============================================================================
/* {{{1 AFFICHAGE INFOS HORODATAGE */
//

void FunctionalTasks::AfficheInfo(const int p_Info) {

    _Tracer->LcdPrintTopLineFromLeft(horodatage::currentTime());

	switch ( p_Info )
	{
		// time
		case 1 :
			_Tracer->LcdPrintTopLineFromLeft(horodatage::currentTime());
			break;
		// temperature
		case 2 :
			_Tracer->LcdPrintTopLineFromRight("18.9 C");
			break;
		// date
		case 3 :
			_Tracer->LcdPrintBottomLineFromRight(horodatage::currentDate());
			break;
		default:
		_Tracer->Print(horodatage::currentTime());
			_Tracer->LcdPrintTopLineFromLeft(horodatage::currentTime());
			_Tracer->LcdPrintTopLineFromRight("18.9 C");
			_Tracer->LcdPrintBottomLineFromRight(horodatage::currentDate());
			break;
			break;
	}
}

void FunctionalTasks::AfficheTemperature() {
	_Tracer->LcdPrintTopLineFromRight("18.9 C");
}

void FunctionalTasks::AfficheDate() {
    _Tracer->Print("Date");
	_Tracer->LcdPrintBottomLineFromRight(horodatage::currentDate());
}

/* }}}1 */
//=============================================================================
/* {{{1 GESTION DES LIGNES ELECTRIQUES */
//
//	SHUTDOWN / START POWER
//

/* {{{2 LAMPADAIRE */
void FunctionalTasks::CouperLampadaire() {

	//_Tracer->Print("ALARM: - coupure alimentation ligne lampadaire");
	// PinManager::Off("LAMPADAIRE");
}
void FunctionalTasks::AlimenterLampadaire() {

	//_Tracer->Print("ALARM: - demarre alimentation ligne lampadaire");
	// PinManager::On("LAMPADAIRE");
}
/* }}}2 */

/* {{{2 PROJECTEUR_ALLEE */
void FunctionalTasks::CouperProjoAllee() {

	// PinManager::Off("PROJECTEUR_ALLEE");
}
void FunctionalTasks::AlimenterProjoAllee() {

	// PinManager::On("PROJECTEUR_ALLEE");
}
/* }}}2 */

/* {{{2 APPENTI*/
void FunctionalTasks::CouperAppenti() {

	// PinManager::Off("APPENTI");
}
void FunctionalTasks::AlimenterAppenti() {

	// PinManager::On("APPENTI");
}
/* }}}2 */

/* {{{2 PUIT*/
void FunctionalTasks::CouperPuit() {

	// PinManager::Off("PUIT");
}
void FunctionalTasks::AlimenterPuit() {

	// PinManager::On("PUIT");
}
/* }}}2 */
/* }}}1 */

// vim:fdm=marker:nowrap:ts=4:expandtab:
 
