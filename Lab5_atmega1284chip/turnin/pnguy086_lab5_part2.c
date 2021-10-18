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

enum States{Start, Wait, Incr, Decr, IncrWait, DecrWait, Reset, ResetWait} state;

unsigned char out;

void Tick(){
	switch(state){
		case Start:
			state = Wait;
			out = 0x07;
			break;
		case Wait:
			if((PINA & 0x03) == 0x01){state = Incr;}
			else if((PINA & 0x03) == 0x02){state = Decr;}
			else if((PINA & 0x03) == 0x03){state = Reset;}
			else{state = Wait;}
			break;
		case Incr:
		case IncrWait:
			if((PINA & 0x03) == 0x01){state = IncrWait;}
			else if((PINA & 0x03) == 0x00){state = Wait;}
			else if((PINA & 0x03) == 0x02){state = Decr;}
			else if((PINA & 0x03) == 0x03){state = Reset;}
			break;
		case Decr:
		case DecrWait:
			if((PINA & 0x03) == 0x01){state = Incr;}
			else if((PINA & 0x03) == 0x00){state = Wait;}
			else if((PINA & 0x03) == 0x02){state = DecrWait;}
			else if((PINA & 0x03) == 0x03){state = Reset;}
			break;
		case Reset:
		case ResetWait:
			if((PINA & 0x03) == 0x00){state = Wait;}
			else{state = ResetWait;}
			break;
		default:
			printf("State Transition Error\n"); break;
	}

	switch(state){
		case Incr:
			out = (out < 9) ? out+1 : out;
			break;
		case Decr:
			out = (out > 0) ? out-1 : out;
			break;
		case Reset:
			out = 0;
			break;
		case Wait:
		case IncrWait:
		case DecrWait:
		case ResetWait:
			break;
		default:
			printf("State Action Error\n"); break;
	}
	
	PORTC = out;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	state = Start;
    while (1) {
		Tick();
    }
    return 1;
}
