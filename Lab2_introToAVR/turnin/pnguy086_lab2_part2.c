/*	Author: pnguy086
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #2 Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
   	DDRA = 0x00; PORTA = 0xFF; 
	DDRC = 0xFF; PORTC = 0x00; 
	unsigned char tmpA = 0x00; 
	unsigned char cntavail = 0x00;

    /* Insert your solution below */
    while (1) {
		tmpA = PINA & 0x0F; //read A3A2A1A0

		switch(tmpA){
			case 0x00:
				cntavail = 0x04;
				break;
			case 0x0F:
				cntavail = 0x00;
				break;
			case 0x01:
			case 0x02:
			case 0x04:
			case 0x08:
				cntavail = 0x03;
				break;
			case 0x03:
			case 0x05:
			case 0x06:
			case 0x09:
			case 0x0A:
			case 0x0C:
				cntavail = 0x02;
				break;
			case 0x07:
			case 0x0B:
			case 0x0D:
			case 0x0E:
				cntavail = 0x01;
				break;

			default:
				printf("Invalid input\n");
				break;
		}

		PORTC = cntavail;
    }
    return 0;
}
