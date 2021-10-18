/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: 
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, Wait, Press, WaitRelease} state;
char sequence[5] = {0x15, 0x2A, 0x21, 0x12, 0x0C};

unsigned char out, i;

void Tick(){
	switch(state){
		case Start:
			state = Wait;
			i = 0;
			break;
		case Wait:
			if((PINA & 0x01) == 0x01){state = Press;}
			else{state = Wait;}
			break;
		case Press:
			if((PINA & 0x01) == 0x00){state = Wait;}
			else{state = WaitRelease;}
			break;
		case WaitRelease:
			state = (PINA & 0x01) ? WaitRelease : Wait;
			break;
		default:
			printf("State Transition Error\n"); break;
	}

	switch(state){
		case Wait:
		case WaitRelease:
			out = sequence[i];
			break;
		case Press:
			i++;
			if(i == 5){i = 0;}
			out = sequence[i];
			break;
		default:
			printf("State Action Error\n"); break;
	}
	
	PORTB = out;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	state = Start;
    while (1) {
		Tick();
    }
    return 1;
}
