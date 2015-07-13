# arduino--

arduino-- is a C++ library for AVR microcontrollers.

The project got kicked off by this blog post by Ben Laurie, [Grown-up Arduino programming](http://www.links.org/?p=1057).

In a nutshell, the idea is to move as much work as possible into the
compilation phase via C++ templates, and have a system where toggling an
output pin in C++ compiles down to a single assembler instruction, while
still having an abstraction layer that is at least very similar between devices.

This is what hello world - blinking an LED - looks like:

<pre lang="c++"><code>
/*
 The hello world of arduino--, a C++ take on the Arduino libraries.

 Blinks an LED connected to digital pin 13 (which is connected to an LED
 on all Arduino variants that we know of).
 */

#include "arduino--.h"
#include <avr/sleep.h>

int main(void)
    {
    // Arduino Pin D13 is an output
    Arduino::D13::modeOutput();

    while(true)
        {
        // toggle the pin
        Arduino::D13::toggle();
        // wait
        _delay_ms(2000);
        }
    
    return 0;
    }
</code></pre>
# Getting started

## Prerequisites

* `avrdude`
* `avr-gcc` (and avr-binutils)
* `avr-libc`
* `perl`
* `python`

On a Mac, installation via [Homebrew](http://brew.sh/) is recommended:

    brew tap larsimmisch/avr
    brew install avr-libc

This will pull in the prerequisites avr-binutils and avr-gcc.


