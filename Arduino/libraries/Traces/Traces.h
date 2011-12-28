/*
  traces.h - low level traces functions
*/

#ifndef _Traces_h
#define _Traces_h

//#include "WProgram.h"
#include <inttypes.h>
#include <LiquidCrystal.h>
//#include "Time.h"


class Traces
{
  public:
//=============================================================================
/* Constructor & Destructor {{{1 */
	Traces();
	~Traces();
	Traces( const Traces &cpy );
/* }}}1 */
//=============================================================================
/* Accessors {{{1 */
	void setLcd(LiquidCrystal *lcdPtr);
/* }}}1 */
//=============================================================================
/* Serial Print Feature {{{1 */
	void Print(String pstr);
	void BeginPrint(String pstr);
	void EndPrint(String pstr);
/* }}}1 */
//=============================================================================
	/* LCD Print Methods {{{1 */
//=============================================================================
	// Print methods on LCD Top Line {{{2
	void LcdPrintTopLine		 (String pstr);
	void LcdPrintTopLineFromLeft (String pstr);
	void LcdPrintTopLineFromRight(String pstr);
	// }}}2
	// Print methods on LCD Bottom Line {{{2
	void LcdPrintBottomLine		 	(String pstr);
	void LcdPrintBottomLineFromLeft (String pstr);
	void LcdPrintBottomLineFromRight(String pstr);
	// }}}2
//=============================================================================
	// Print methods to write from left or right direction {{{2
	void LcdPrintFromLeft (String pstr);
	void LcdPrintFromRight(String pstr);
	// }}}2
	/* }}}1 */
//=============================================================================
// LCD Clear methods {{{1
	void LcdClearLine(int noLine) ;
	void LcdClearTopLine()	  ;
	void LcdClearBottomLine()     ;
	void LcdClearScreen()	   ;
// }}}1
  private:
//=============================================================================
/* Private Members {{{1 */
/* Accessors members {{{2 */
	LiquidCrystal * _lcdPtr;
/* }}}2 */
//=============================================================================
	/* LCD Print private members {{{2 */
	bool b_clearEntireLine;

	// on 16x2 LCD line,
	//
	int l_selectedLine;

	// this save the position index of last character written
	// from left or from right
	int l_lastIndexPositionWritten;
	/* }}}2 */
/* }}}1 */
//=============================================================================
/* Utils Private Methods {{{1 */
	String Date();
/* }}}1 */
//=============================================================================
};
/* set fdm=marker */

#endif /* _Traces_h */

 
