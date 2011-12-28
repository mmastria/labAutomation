/*
  FunctionalWrapper.h - Wrapper to bind functional methods
  2010 nov. 24
*/

#ifndef _FunctionalWrapper_h
#define _FunctionalWrapper_h

#include <inttypes.h>
//#include "WProgram.h"
#include <Traces.h>
#include <FunctionalTasks.h>


class FunctionalWrapper
{
  public:

	// passing obj to wrapper
	static void setObj(FunctionalTasks & obj) { fObj = &obj; }
	//
	static void AfficheDateGlue()			{ return fObj->AfficheDate()		; }
	static void AfficheTemperatureGlue()	{ return fObj->AfficheTemperature()     ; }

	static void setRealTimeClockGlue()		{ return fObj->setRealTimeClock()	 ; }
	static void getRealTimeClockGlue()		{ return fObj->getRealTimeClock()	 ; }
	static void displayRealTimeClockGlue()	{ return fObj->displayRealTimeClock()   ; }

	static void CouperLampadaireGlue()		{ return fObj->CouperLampadaire()	 ; }
	static void AlimenterLampadaireGlue()	{ return fObj->AlimenterLampadaire()    ; }
	static void CouperProjoAlleeGlue()		{ return fObj->CouperProjoAllee()	 ; }
	static void AlimenterProjoAlleeGlue()	{ return fObj->AlimenterProjoAllee()    ; }
	static void CouperAppentiGlue()			{ return fObj->CouperAppenti()	    ; }
	static void AlimenterAppentiGlue()		{ return fObj->AlimenterAppenti()	 ; }
	static void CouperPuitGlue()			{ return fObj->CouperPuit()		 ; }
	static void AlimenterPuitGlue()			{ return fObj->AlimenterPuit()	    ; }


  private:

	static FunctionalTasks *fObj;


//=============================================================================
/* Constructor & Destructor {{{1 */
    FunctionalWrapper();
/* }}}1 */
};

#endif /* _FunctionalWrapper_h */

// vim:fdm=marker:nowrap:ts=4:expandtab:
 