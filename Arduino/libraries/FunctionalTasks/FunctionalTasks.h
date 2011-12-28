/*
  FunctionalTasks.h - Functional methods
*/

#ifndef _FunctionalTasks_h
#define _FunctionalTasks_h

#include <inttypes.h>
//#include "WProgram.h"
#include <Traces.h>

class FunctionalTasks
{

  private:

	Traces *_Tracer;

  public:

	static int heure;
	static int dateLiterale;
	static int temperature;

	void setTracer(Traces *TracerPtr);

//=============================================================================
/* Constructor & Destructor {{{1 */
    FunctionalTasks();
/* }}}1 */
//=============================================================================
/* {{{1 TIME MANAGMENT */

	void setRealTimeClock();
	void getRealTimeClock();
	void displayRealTimeClock();
/* }}}1 */
//=============================================================================
/* {{{1 AFFICHAGE INFOS HORODATAGE */
//
	void AfficheInfo(const int p_Info);
	void AfficheTemperature();
	void AfficheDate();
/* }}}1 */
//=============================================================================
/* {{{1 GESTION DES LIGNES ELECTRIQUES */
//
//	SHUTDOWN / START POWER
//

	//	SHUTDOWN / START POWE
	//	LAMPADAIRE
	void CouperLampadaire();
	void AlimenterLampadaire();
	//	PROJECTEUR_ALLEE
	void CouperProjoAllee();
	void AlimenterProjoAllee();
	//	APPENTI
	void CouperAppenti();
	void AlimenterAppenti();
	//	PUIT
	void CouperPuit();
	void AlimenterPuit();
/* }}}1 */
//=============================================================================
};

#endif /* _FunctionalTasks_h */

 