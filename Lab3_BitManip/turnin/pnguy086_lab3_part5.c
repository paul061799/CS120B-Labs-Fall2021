/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
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
   	DDRD = 0x00; PORTD = 0xFF;
	DDRB = 0xFE; PORTB = 0x01;
	unsigned short weight = 0x00;
	unsigned char final = 0x00;
    /* Insert your solution below */
    while (1) {
		weight = (PIND << 1) + (PINB & 0x01);

		if(weight >= 70){
			final = 0x02;
		} else if (weight > 5){
			final = 0x04;
		} else {
			final = 0x00;
		}
		PORTB = final;
    }
    return 1;
}
