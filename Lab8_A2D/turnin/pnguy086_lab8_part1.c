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
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE); 
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00; 
	DDRD = 0xFF; PORTD = 0x00;
	unsigned short read;
	unsigned char top;
	unsigned char bot;
	ADC_init();
	
	while(1) {
		read = ADC;
		bot = (char)read;
		top = (char)(read >> 4);
		PORTB = bot;
		PORTD = top;
	}
}
