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

enum States{Start, Init, PoundPress, PoundRelease, Unlocked} state;

unsigned char unlock;

void Tick(){
	switch(state){
		case Start:
			state = Init;
			unlock = 0x00;
			break;
		case Init:
			if(PINA == 0x04){state = PoundPress;}
			else{state = Init;}
			break;
		case PoundPress:
			if(PINA == 0x00){state = PoundRelease;}
			else if(PINA == 0x04){state = PoundPress;}
			else{state = Init;}
			break;
		case PoundRelease:
			if(PINA == 0x00){state = PoundRelease;}
			else if(PINA == 0x02){state = Unlocked;}
			else{state = Init;}
			break;
		case Unlocked:
			if(PINA == 0x80){unlock = 0x00;}
			state = Init;
			break;
		default:
			printf("State Transition Error\n"); break;
	}

	switch(state){
		case Unlocked:
			unlock = unlock ? 0 : 1;
			break;
		case Init:
		case PoundPress:
		case PoundRelease:
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
