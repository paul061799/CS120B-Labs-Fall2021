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

enum States{Start, SequenceRelease, Press, Wait, SequenceHold} state; 

unsigned char i, output;
unsigned char sequence[4] = {0x01, 0x02, 0x04, 0x02};

void Tick() {
	switch(state){
		case Start:
			i = 0;
			state = SequenceRelease;
			break;
		case SequenceRelease:
			state = (PINA & 0x01) ? Press : SequenceRelease;
			break;
		case Press:
			state = (PINA & 0x01) ? Press : Wait;
			break;
		case Wait:
			state = (PINA & 0x01) ? SequenceHold : Wait;
			if(state == SequenceHold){i=0;}
			break;
		case SequenceHold:
			state = (PINA & 0x01) ? SequenceHold : SequenceRelease;
			break;
		default:
			printf("State transiton error\n");
			break;
	}
	
	switch(state){
		case SequenceRelease:
		case SequenceHold:
			output = sequence[i%4];
			i++;
			break;
		case Wait:
		case Press:
			output = sequence[i%4];
			break;
		default:
			printf("State action error\n");
			break;
	}
	PORTB = output;
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(30);
	TimerOn();
	state = Start;
    /* Insert your solution below */
    while (1) {
		Tick();
		while(!TimerFlag);
		TimerFlag = 0;
    }
    return 1;
}
