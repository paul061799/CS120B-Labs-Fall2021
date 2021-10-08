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

int main(void) {
    /* Insert DDR and PORT initializations */
   	DDRA = 0x00; PORTA = 0xFF;
   	DDRC = 0xFF; PORTC = 0x00; 
	unsigned char fuelLevel, lowFuel, final = 0x00;
    /* Insert your solution below */
    while (1) {
		fuelLevel = PINA & 0x0F;
		
		switch(fuelLevel){
			case 15:
			case 14:
			case 13:
				final = 0x3F;
				break;
			case 12:
			case 11:
			case 10:
				final = 0x3E;
				break;
			case 9:
			case 8:
			case 7:
				final = 0x3C;
				break;
			case 6:
			case 5:
				final = 0x38;
				break;
			case 4:
			case 3:
				final = 0x30;
				lowFuel = 0x01;
				break;
			case 2:
			case 1:
				final = 0x20;
				lowFuel = 0x01;
				break;
			default:
				final = 0x00;
				lowFuel = 0x01;
				break;
		}

		if(lowFuel){final = final | 0x40;}

		PORTC = final;
    }
    return 1;
}
