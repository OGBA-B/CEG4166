/*
 * File name: ledModule.c
 * Description: Module to communicate with and set the color of the LED
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <avr/io.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "WheelMotion.h"

/**
 * Indicates direction of the robot.
 * The Led will change:-
 * 	 Green: While moving Forward
 *   Red: While moving Forward
 *   Blue: While spinning (right or left).
 *   White: When not moving.
 */
 void changeLEDColour(){

	//Set pins assigned to LED colors to output
	DDRE |= _BV(DDE5);
	DDRE |= _BV(DDE3);
	DDRH |= _BV(DDH3);


	if (direction==0){
		PORTE &= ~_BV(PORTE3); //GREEN LIGHT ON
		PORTH |= _BV(PORTH3); //RED LIGHT OFF
		PORTE |= _BV(PORTE5); //BLUE LIGHT OFF
	} else if ( direction==1 ) {
		PORTH &= ~_BV(PORTH3); //RED LIGHT ON
		PORTE |= _BV(PORTE5); //BLUE LIGHT OFF
		PORTE |= _BV(PORTE3); //GREEN LIGHT OFF
	} else if ( direction==2 ) {
		PORTE &= ~_BV(PORTE5); //BLUE LIGHT ON
		PORTH |= _BV(PORTH3); //RED LIGHT OFF
		PORTE |= _BV(PORTE3); //GREEN LIGHT OFF
	} else if ( direction==3 ) {
		PORTE &= ~_BV(PORTE5); //BLUE LIGHT ON
		PORTH |= _BV(PORTH3); //RED LIGHT OFF
		PORTE |= _BV(PORTE3); //GREEN LIGHT OFF
	} else if ( direction==4 ) {
		PORTE &= ~_BV(PORTE5); //Turn all on for white
		PORTH &= ~_BV(PORTH3);
		PORTE &= ~_BV(PORTE3);
	}
}
