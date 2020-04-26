// flashPin.cpp - flash arduino pin using non-blocking timing

// created: Oct 12, 2013 Copyright(C) G. D. (Joe) Young <jyoung@islandnet.com>

// revised: Jan 14/14 - add specification of resting level
//          Jan 15/14 - use i/o wrapper functions pin_mode, pin_write
//          Jan 16/14 - fp_set function added
//          Apr 24/20 - version 1.0.1 - Library formatting
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.



#include "flashPin.h"

// constructor - allow default setting of pin and duration
	flashPin::flashPin( byte pin, bool restLevel, unsigned long duration ) {
		fpin = pin;
		fdur = duration;
		fstate = restLevel;
		frest = restLevel;
		pin_mode( fpin, OUTPUT );
		pin_write( fpin, frest );
	} // flashPin constructor

// set - change resting level
	void flashPin::fp_set( bool restLevel ) {
		frest = restLevel;
		fstate = frest;
		pin_write( fpin, frest );
	} // fp_set( )

// flash - with duration specified
	void flashPin::flash( unsigned long duratn ) {
		pin_write( fpin, !frest );
		fstate = !fstate;
		fdur = duratn;			// reset default duration 
		fmark = millis( );		// setup flashOff with end time
	} // flash

// flash - default duration
	void flashPin::flash( ) {
		pin_write( fpin, !frest );
		fstate = !fstate;
		fmark = millis( );	// setup flashOff with constructed end time
	} // flash

// flashOff - call at loop rate to find time to turn off pin
	void flashPin::flashOff( ) {
		if( fstate == frest ) return;	// quick exit if already off
		if( millis( ) - fmark > fdur ) {
			pin_write( fpin, frest );
			fstate = frest;
		} // if timeup
	} // flashOff
