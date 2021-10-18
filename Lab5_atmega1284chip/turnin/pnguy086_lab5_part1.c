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

int main(void) {
	/* Insert DDR and PORT initializations */
   	DDRA = 0x00; PORTA = 0xFF;
   	DDRC = 0xFF; PORTC = 0x00; 
	unsigned char fuelLevel, lowFuel, final = 0x00;
    /* Insert your solution below */
    while (1) {
		fuelLevel = ~PINA & 0x0F;
		
		if(fuelLevel >= 13){final = 0x3F;}
		else if(fuelLevel >= 10){final = 0x3E;}
		else if(fuelLevel >= 7){final = 0x3C;}
		else if(fuelLevel >= 5){final = 0x38;}
		else if(fuelLevel >= 3){final = 0x30; lowFuel = 0x01;}
		else if(fuelLevel >= 1){final = 0x20; lowFuel = 0x01;}
		else if(fuelLevel == 0){final = 0x00; lowFuel = 0x01;}

		if(lowFuel){final = final | 0x40;}

		PORTC = final;
    }
    return 1;
}
