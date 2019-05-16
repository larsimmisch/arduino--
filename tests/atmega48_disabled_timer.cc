/*
 * avrtest.c
 *
 *  Created on: 1 Dec 2009
 *      Author: jone
 */

#include "arduino--.h"

#include "avr_mcu_section.h"
AVR_MCU(F_CPU, "atmega48");

ISR(TIMER0_COMPA_vect)
{
}

int main(void)
{
	// Set up timer0 - do not start yet
	TCCR0A |= (1 << WGM01);                     // Configure timer 0 for CTC mode
	TIMSK0 |= (1 << OCIE0A);                    // Enable CTC interrupt
	OCR0A   = 0xAA;                             // CTC compare value

	//TCCR0B |= (1 << CS00) | (1 << CS01);        // Start timer: clk/64

	sei();                                      // Enable global interrupts

	// here the interupts are enabled, but the interupt
	// vector should not be called
	sleep_mode();

	// this should not be reached
	cli();
	sleep_mode();
}
