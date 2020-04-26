// flashPin_I2C.h - definition of I2C i/o version of flashPin arduino library
//
// created: Jan 15, 2014  Copyright (C) G. D. (Joe) Young <jyoung@islandnet.com>
//
// revised: Apr 22/20 - fix compile error when using MKR board(s), add alternate
//                      I2C port specification. Version 1.0.1
//
// override the pin_mode and pin_write i/o functions in flashPin so that the
// flashPin operation can be simply accomplished on a I2C port expander (PCF8574,
// or PCF8575). Implementation is very similar to Keypad_I2C library.
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

#ifndef FLASHPIN_I2C
#define FLASHPIN_I2C

#include "flashPin.h"
#include "Wire.h"

#define	PCF8574	1	// PCF8574 I/O expander device is 1 byte wide
#define PCF8575 2	// PCF8575 I/O expander device is 2 bytes wide

class flashPin_I2C : public flashPin {

public:
	flashPin_I2C( byte bitNr, bool restLevel = LOW, unsigned long duration = 250, byte address = 0x20,
		  byte width = PCF8574, TwoWire * awire = &Wire ) : flashPin( bitNr, restLevel, duration )
			{ i2caddr = address; i2cwidth = width; jwire = awire; }

	void pin_mode(byte pinNum, byte mode) {}
	void pin_write(byte pinNum, boolean level);

	void begin( );	// this will get initial pin state, start wire library

	// read initial value for pinState
	word pinState_set( );
	// write a whole byte or word (depending on the port expander chip) to i2c port
	void port_write( word i2cportval );

private:
    // I2C device address
    byte i2caddr;
    // I2C port expander device width in bytes (1 for 8574, 2 for 8575)
    byte i2cwidth;
	// I2C pin_write state persistant storage
	// least significant byte is used for 8-bit port expanders
	word pinState;
	TwoWire * jwire;	//optional alternate I2C port

}; // class





#endif

