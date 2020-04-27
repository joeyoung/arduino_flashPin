### arduino_flashPin

This repository contains two related libraries:

* flashPin - timed pulse on a single arduino pin
* flashPin_I2C - pulse on a PCF8574 or PCF8575 port expander pin

Each library has examples illustrating use. 

##### flashPin

Sometimes debugging a program can be assisted
by having an indication that a particular point in the program has been reached. Often
the indication is provided by inserting one or more `Serial.print()` statements, but
that doesn't always work if the program is already sending data to the serial port. In
that case, flashing a light on a spare port pin can be that indication. Using a
`flashPin` object provides a simplified setup for timed pulses.

On construction `flashPin` allows optionally specifying the pin, pulse duration, and 
port type. The default constructor selects pin 13, 250 msec, and PCF8574. `flashPin` 
functions provided allow changing the duration and generating a repeated group of
pulses on each call.

##### flashPin_I2C

This library extends flashPin to use PCF8574 and PCF8575 port expander chips which
use I2C (or `Wire`) communications. I2C uses only two microprocessor pins plus system
power and ground. Some arduino boards (for example: MKR, ESP32) can have more than
one I2C bus, and `flashPin_I2C` objects allow specifying the bus to use.


