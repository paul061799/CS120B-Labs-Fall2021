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

enum States{Start, SequenceRelease, Press, ScoreUpdate, Wait, SequenceHold, End} state; 

unsigned char in, i, out, score, tickCnt;
unsigned char sequence[4] = {0x01, 0x02, 0x04, 0x02};

void Tick() {
	in = (~PINA & 0x01);
	switch(state){
		case Start:
			i = 0;
			score = 0;
			state = SequenceRelease;
			break;
		case SequenceRelease:
			state = in ? Press : SequenceRelease;
			break;
		case Press:
			state = ScoreUpdate;
			break;
		case ScoreUpdate:
			state = Wait;
			break;
		case Wait:
			state = in ? SequenceHold : Wait;
			if(state == SequenceHold){i=0;}
			break;
		case SequenceHold:
			if(score == 9){state = End; break;}
			state = in ? SequenceHold : SequenceRelease;
			break;
		case End:
			state = in ? Start : End;
			break;
		default:
			printf("State transiton error\n");
			break;
	}
	
	switch(state){
		case SequenceRelease:
		case SequenceHold:
			out = sequence[i%4];
			tickCnt++;
			if(tickCnt%3 == 0){i++;}
			break;
		case Wait:
		case Press:
			out = sequence[i%4];
			break;
		case ScoreUpdate:
			if((i%2) == 1){score++;}
			break;
		case End:
			out = sequence[i%4];
			break;
		default:
			printf("State action error\n");
			break;
	}
	PORTB = out;
	
	LCD_ClearScreen();
	LCD_WriteData(score + '0');
	if(score == 9){LCD_DisplayString(2, "You Win!");}
	
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
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
