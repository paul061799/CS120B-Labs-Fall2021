/*	Author: pnguy086
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #2 Exercise #1
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
   	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	unsigned char tmpB = 0x00; // Temporary variable to hold the value of B
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A

    /* Insert your solution below */
    while (1) {
	tmpA = PINA & 0x03; //read A1A0
	//B0 = 1 if 01, 0 otherwise
	if (tmpA == 0x01) { 
		tmpB = (tmpB & 0xFC) | 0x01; 
	} else {
		tmpB = (tmpB & 0xFC) | 0x00; 
	}	
	// 3) Write output
	PORTB = tmpB;
    }
    return 0;
}
