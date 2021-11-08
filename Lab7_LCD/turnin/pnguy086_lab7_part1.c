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
#include "io.h"

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

unsigned char out, i, in;

void Tick(){
	in = ~PINA & 0x03;
	switch(state){
		case Start:
			state = Wait;
			out = 0x00;
			break;
		case Wait:
			if(in == 0x01){state = Incr; i = 0;}
			else if(in == 0x02){state = Decr; i = 0;}
			else if(in == 0x03){state = Reset;}
			else{state = Wait;}
			break;
		case Incr:
			if(in == 0x01){state = Incr;}
			else if(in == 0x00){state = Wait;}
			else if(in == 0x02){state = Decr; i = 0;}
			else if(in == 0x03){state = Reset;}
			break;
		case Decr:
			if(in == 0x01){state = Incr; i = 0;}
			else if(in == 0x00){state = Wait;}
			else if(in == 0x02){state = Decr;}
			else if(in == 0x03){state = Reset;}
			break;
		case Reset:
		case ResetWait:
			if(in == 0x00){state = Wait;}
			else if(in == 0x03){state = ResetWait;}
			else if(in == 0x01){state = Incr; i = 0;}
			else if(in == 0x02){state = Decr; i = 0;}
			break;
		default:
			break;
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
			break;
	}
	
	LCD_ClearScreen();
	LCD_WriteData(out + '0');
	
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00; //LCD data lines
	DDRD = 0xFF; PORTD = 0x00; //LCD control lines
    /* Insert your solution below */
    LCD_init();
    
    TimerSet(100);
    TimerOn();
	state = Start;
    while (1) {
		Tick();
    }
    return 1;
}
