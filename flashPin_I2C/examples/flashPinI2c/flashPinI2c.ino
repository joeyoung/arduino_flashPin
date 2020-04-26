// flashPin_I2C basic example

// created: Oct 12, 2013 G. D. (Joe) Young <jyoung@islandnet.com>

// revised: Jan 14/14 - using version 2 with resting level specified
//          Jan 15/14 - I2C i/o version
//          Apr 23/20 - re-check with revised library

// Illustrate the use of non-blocking timers in the flashPin library
// to flash arduino pins.


#include <flashPin.h>
#include <flashPin_I2C.h>
#include <Wire.h>

#define I2CADR 0x20

flashPin_I2C bit7( 7, HIGH, 250, I2CADR, PCF8575 );
 flashPin_I2C pin12( 12, HIGH, 500, I2CADR, PCF8575 );
flashPin_I2C myPin( 11, HIGH, 500, I2CADR, PCF8575 );

unsigned long sectick;

void setup( ) {
  bit7.begin( );
  pin12.begin( );
  myPin.begin( );
  sectick = millis( );
}

void loop( ) {
  if( millis( ) - sectick > 3000 ) {
    sectick = millis( );
    bit7.flash( );
    pin12.flash( );
    myPin.flash( 1000 );  // optionally specify new duration
  }
  bit7.flashOff( );
  pin12.flashOff( );
  myPin.flashOff( );
}
