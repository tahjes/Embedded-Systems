/*
 * SensorAlarm.c
 * Ultrasonic Sensor and Passive Buzzer Interfacing with Atmega328P
 * The farther the distance, the slower the buzzer, the closer the faster
 * The sensor can track distances between 2 cm to 400 cm (13 Feet)
 * Created: 6/17/2025 7:55:09 AM
 * Author : TJ
 */ 

#define F_CPU 8000000UL
#define TRIG 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    /* Configuration */
	// PB2 (Trig), PB3 (Echo), PB0 (Passive Buzzer)
	DDRB |= (1 << DDB2)| (1 << DDB0); // 1 = output, 0 = input for data direction register
	DDRB &= ~(1 << DDB3); // set echo as an input. (Pull ups aren't needed in this case)
	
	sei(); // enable global interrupts (without this interrupts like timers won't occur at all)
	TIMSK1 = (1 << TOIE1); // Enable Timer1 overflow interrupts
	TCCR1A = 0x00; // Timer1 control reg A = 0: normal mode... counts from 0 until 65535 and then triggers interrupt
	
    while (1) 
    {
		// Trigger pulse for 10us
		PORTB |= (1 << PINB2); // set pin to HIGH
		_delay_us(10);
		PORTB &= ~(1 << PINB2); // set back to low
		
		TCNT1 = 0x00; // reset timer counter
		TCCR1B = 0x41; // capture on rising edge
		TIFR1 = (1 << ICF1); // clear input capture flag
		TIFR1 = (1 << TOV1); // clear overflow flag
		
		// calculate width of echo (speed of buzzer corresponds to distance)
    }
}

