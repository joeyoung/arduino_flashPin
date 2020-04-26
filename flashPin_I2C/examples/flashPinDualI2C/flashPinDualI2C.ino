// flashPin_I2CDualI2C - example multiple objects, separate and same ports

// created: Oct 12, 2013 G. D. (Joe) Young <jyoung@islandnet.com>

// revised: Jan 14/14 - using version 2 with resting level specified
//          Jan 15/14 - I2C i/o version
//          Jan 16/14 - multiple objects declared

// Illustrate the use of non-blocking timers in the flashPin library
// to flash I2C port expansion ICs individual bits.


#include <flashPin.h>
#include <flashPin_I2C.h>
#include <Wire.h>

#define I2CADR 0x21
#define I2CADR0 0x20

flashPin_I2C bit7( 7, HIGH, 500, I2CADR, PCF8575 );
flashPin_I2C bit15( 15, HIGH, 500, I2CADR, PCF8575 );
flashPin_I2C bit07( 7, LOW, 500, I2CADR0, PCF8574 );
flashPin myPin( 13, LOW, 500 );


unsigned long sectick;

void setup( ) {
  bit15.begin( );
  bit7.begin( );
//  bit7.port_write( 0xffff );  // init pcf8575 all high (not nec'y)
  bit07.begin( );
  sectick = millis( ) + 2000;
}

void loop( ) {
  if( sectick < millis( ) ) {
    sectick += 2000;
//    bit15.flash( );  // order doesn't matter
    bit7.flash( );
    bit07.flash( );
    bit15.flash( );
    myPin.flash( 750 );  // optionally specify new duration
  }
  bit15.flashOff( );
  bit7.flashOff( );
  bit07.flashOff( );
//  bit15.flashOff( );
  myPin.flashOff( );
}
