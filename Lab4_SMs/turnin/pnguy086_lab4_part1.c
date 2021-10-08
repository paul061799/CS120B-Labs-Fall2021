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

enum States{Start, B0Press, B0Release, B1Press, B1Release} state;

void Tick(){
	switch(state){
		case Start:
			state = B0Release;
			break;
		case B0Release:
			state = (PINA == 0x01) ? B1Press : B0Release; break;
		case B1Press:
			state = (PINA == 0x01) ? B1Press : B1Release; break;
		case B1Release:
			state = (PINA == 0x01) ? B0Press : B1Release; break;
		case B0Press:
			state = (PINA == 0x01) ? B0Press : B0Release; break;
		default:
			printf("State Transition Error\n"); break;
	}

	switch(state){
		case B0Release:
			break;
		case B1Press:
			PORTB = 0x02; break;
		case B1Release:
			break;
		case B0Press:
			PORTB = 0x01; break;
		default:
			printf("State Action Error\n"); break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	PORTB = 0x01;
	state = Start;
    while (1) {
		Tick();
    }
    return 1;
}
