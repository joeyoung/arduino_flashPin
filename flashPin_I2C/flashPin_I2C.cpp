// flashPin.cpp - I2C i/o version of flashPin arduino library
//
// created: Jan 15, 2014  Copyright (C) G. D. (Joe) Young <jyoung@islandnet.com>
//
// revised: Apr 22/20 - fix compile error when using MKR board(s), add alternate
//                      I2C port specification Version 1.0.1
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


#include "flashPin_I2C.h"


// Initialize I2C
void flashPin_I2C::begin(void) {
	jwire->begin();
//	pinState = 0xff;
	pinState = pinState_set( );
}

void flashPin_I2C::pin_write(byte pinNum, boolean level) {
	pinState = pinState_set( );
	word mask = 1<<pinNum;
	if( level == HIGH ) {
		pinState |= mask;
	} else {
		pinState &= ~mask;
	}
	port_write( pinState );
} // I2CxWrite( )

void flashPin_I2C::port_write( word i2cportval ) {
	jwire->beginTransmission((int)i2caddr);
	jwire->write( i2cportval & 0x00FF);
	if (i2cwidth > 1) {
		jwire->write( i2cportval >> 8 );
	}
	jwire->endTransmission();
	pinState = i2cportval;
} // port_write( )

word flashPin_I2C::pinState_set( ) {
	jwire->requestFrom( (int)i2caddr, (int)i2cwidth );
	pinState = jwire->read( );
	if (i2cwidth > 1) {
		pinState |= jwire->read( ) << 8;
	}
	return pinState;
} // set_pinState( )


