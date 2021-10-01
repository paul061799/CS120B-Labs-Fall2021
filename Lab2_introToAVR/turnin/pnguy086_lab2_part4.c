/*	Author: pnguy086
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #2 Exercise #4 (Challenge)
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
   	DDRA = 0x00; PORTA = 0xFF;
   	DDRB = 0x00; PORTB = 0xFF;
   	DDRC = 0x00; PORTC = 0xFF; 
	DDRD = 0xFF; PORTD = 0x00; 
	unsigned char tmpA = 0x00; 
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;
	unsigned char totWeight = 0x00;
	unsigned char acDiff = 0x00;
	unsigned char final = 0x00;

    /* Insert your solution below */
    while (1) {
		tmpA = PINA;
		tmpB = PINB;
		tmpC = PINC;

		totWeight = tmpA + tmpB + tmpC;

		if(tmpC > tmpA){
			acDiff = tmpC - tmpA;
		} else {
			acDiff = tmpA - tmpC;
		}

		final = totWeight & 0xFC;

		if(totWeight > 140){
			final = final | 0x01;
		}

		if(acDiff > 80){
			final = final | 0x02;
		}
		
		PORTD = final;
    }
    return 0;
}
