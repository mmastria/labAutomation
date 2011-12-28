/*
  Traces.cpp for traces output.

  Copyright (c) Nicolas VALENTIN 2010
  12 Oct 2010  - First Version
  2010 nov. 20 Adding Special Features Writing Direction
*/

#include "WProgram.h"
#include "Traces.h"
#include "Time.h"
#include <Wire.h>
#include <Utils.h>
#include <DS1307.h>
#include <LiquidCrystal.h>

//=============================================================================
/* Constructor & Destructor {{{1 */
Traces::Traces()
{

	b_clearEntireLine=true;
	l_lastIndexPositionWritten=0;
	l_selectedLine=0;
}

Traces::~Traces()
{
}

Traces::Traces( const Traces &cpy )
{
}
/* }}}1 */
//=============================================================================
/* Accessors {{{1 */
void Traces::setLcd(LiquidCrystal *lcdPtr) {

	if (  lcdPtr != NULL )
	{
		_lcdPtr = lcdPtr;
		Traces::Print("Tracer contains LCD object's pointer now !");
		delay(500);
	}
	else
	{
		Traces::Print("Erreur pointeur nul sur le module de trace");
	}
}
/* }}}1 */
//=============================================================================
/* Serial Print Feature {{{1 */
void Traces::Print(String pstr) {
   Serial.println(Date()+pstr);
}

void Traces::BeginPrint(String pstr) {
   Serial.print(Date()+pstr);
}

void Traces::EndPrint(String pstr) {
   Serial.println(pstr);
}
/* }}}1 */
//=============================================================================
/* LCD Print Methods {{{1 */
//=============================================================================
// Print methods on LCD Top Line {{{2
void Traces::LcdPrintTopLine(String pstr) {
	l_selectedLine=0;
	_lcdPtr->home();
	_lcdPtr->print(strutils::CompleteString(pstr));
}

void Traces::LcdPrintTopLineFromLeft(String pstr) {
	l_selectedLine=0;
	Traces::LcdPrintFromLeft(pstr);
}

void Traces::LcdPrintTopLineFromRight(String pstr) {
	l_selectedLine=0;
	Traces::LcdPrintFromRight(pstr);
}
// }}}2
//=============================================================================
// Print methods on LCD Bottom Line {{{2
void Traces::LcdPrintBottomLine(String pstr) {
	l_selectedLine=1;
	_lcdPtr->home();
	_lcdPtr->print(strutils::CompleteString(pstr));
}

void Traces::LcdPrintBottomLineFromLeft(String pstr) {
	l_selectedLine=1;
	Traces::LcdPrintFromLeft(pstr);
}

void Traces::LcdPrintBottomLineFromRight(String pstr) {
	l_selectedLine=1;
	Traces::LcdPrintFromRight(pstr);
}
// }}}2
//=============================================================================
// Print methods to write from left or right direction {{{2
void Traces::LcdPrintFromLeft(String pstr) {

	// _lcdPtr->home();
	_lcdPtr->setCursor(0,0);
	// write message
	for (int i=0; i<pstr.length(); ++i)
	{
		_lcdPtr->setCursor(i,0);
		_lcdPtr->print(pstr.charAt(i));
		// delay(150);
	}
}

void Traces::LcdPrintFromRight(String pstr) {

	//
	_lcdPtr->setCursor(16,l_selectedLine);
	// write message
	int pos = 16;
	for (int i=pstr.length(); i>=0; --i)
	{
		_lcdPtr->setCursor(pos,l_selectedLine);
		_lcdPtr->print(pstr.charAt(i));
		pos--;
		// delay(150);
	}
}
// }}}2
// }}}1
//=============================================================================
// LCD Clear Methods {{{1
void Traces::LcdClearLine(int noLine) {

	_lcdPtr->home();
	for (int i=0; i<16; ++i)
	{
		_lcdPtr->setCursor(i,noLine);
		_lcdPtr->print(" ");
		delay(10);
	}
}
void Traces::LcdClearTopLine() {
	Traces::LcdClearLine(0);
}
void Traces::LcdClearBottomLine() {
	Traces::LcdClearLine(1);
}
void Traces::LcdClearScreen() {
	Traces::LcdClearTopLine();
	Traces::LcdClearBottomLine();
}
// }}}1
//=============================================================================
/* Utils Private Methods {{{1 */
String Traces::Date(){

  String str ;
  str+=convert::ToTwoDigits(RTC.get(DS1307_HR, true))+":"+convert::ToTwoDigits(RTC.get(DS1307_MIN, false))+":"+convert::ToTwoDigits(RTC.get(DS1307_SEC , false))+"_";
  return str;
}
/* }}}1 */
//=============================================================================

// Traces Tracer = Traces() ;
/* set fdm=marker */
 