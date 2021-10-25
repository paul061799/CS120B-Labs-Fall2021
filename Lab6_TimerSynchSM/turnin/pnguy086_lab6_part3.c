/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 * Demo Link: https://youtu.be/MzSK_devBxQ
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff() {
	TCCR1B = 0x00;
}

void TimerISR() {
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

enum States{Start, Wait, Incr, Decr, Reset, ResetWait} state;

unsigned char out, i;

void Tick(){
	switch(state){
		case Start:
			state = Wait;
			out = 0x07;
			break;
		case Wait:
			if((PINA & 0x03) == 0x01){state = Incr; i = 0;}
			else if((PINA & 0x03) == 0x02){state = Decr; i = 0;}
			else if((PINA & 0x03) == 0x03){state = Reset;}
			else{state = Wait;}
			break;
		case Incr:
			if((PINA & 0x03) == 0x01){state = Incr;}
			else if((PINA & 0x03) == 0x00){state = Wait;}
			else if((PINA & 0x03) == 0x02){state = Decr; i = 0;}
			else if((PINA & 0x03) == 0x03){state = Reset;}
			break;
		case Decr:
			if((PINA & 0x03) == 0x01){state = Incr; i = 0;}
			else if((PINA & 0x03) == 0x00){state = Wait;}
			else if((PINA & 0x03) == 0x02){state = Decr;}
			else if((PINA & 0x03) == 0x03){state = Reset;}
			break;
		case Reset:
		case ResetWait:
			if((PINA & 0x03) == 0x00){state = Wait;}
			else if(!(PINA & 0x03)){state = ResetWait;}
			else if((PINA & 0x03) == 0x01){state = Incr; i = 0;}
			else if((PINA & 0x03) == 0x02){state = Decr; i = 0;}
			break;
		default:
			printf("State Transition Error\n"); break;
	}

	switch(state){
		case Incr:
			if(out < 9 && !(i%10)){out++;}
			i++;
			break;
		case Decr:
			if(out > 0 && !(i%10)){out--;}
			i++;
			break;
		case Reset:
			out = 0;
			break;
		case Wait:
			out = out;
			break;
		case ResetWait:
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
    TimerSet(10);
    TimerOn();
	state = Start;
	
    while (1) {
		Tick();
		while(!TimerFlag);
		TimerFlag = 0;
    }
    return 1;
}
