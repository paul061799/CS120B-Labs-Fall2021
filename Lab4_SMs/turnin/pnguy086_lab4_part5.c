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

enum States{Start, Process, Wait, Unlocked} state;

unsigned char unlock, i;

unsigned char sequence[4] = {0x04, 0x01, 0x02, 0x01};

void Tick(){
	switch(state){
		case Start:
			state = Process;
			unlock = 0x00;
			i = 0x00;
			break;
		case Process:
			if(PINA == sequence[i] && i == 3){state = Unlocked;}
			else if(PINA == sequence[i]){state = Wait;}
			else{state = Process; i = 0;}
			break;
		case Wait:
			if(PINA == sequence[i] || PINA == 0x00){state = Wait;}
			else{state = Process; i++;}
			break;
		case Unlocked:
			if(PINA == 0x80){unlock = 0x00;}
			state = Process;
			break;
		default:
			printf("State Transition Error\n"); break;
	}

	switch(state){
		case Unlocked:
			unlock = unlock ? 0 : 1;
			i = 0;
			break;
		case Process:
		case Wait:
			break;
		default:
			printf("State Action Error\n"); break;
	}
	
	PORTB = unlock;
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
