/*
 * File name: ledModule.h
 * Description: Module to communicate with and set the color of the LED
 */

#ifndef LEDMODULE_H_
#define LEDMODULE_H_

/**
 * Indicates direction of the robot.
 * The Led will change:-
 * 	 Green: While moving Forward
 *   Red: While moving Forward
 *   Blue: While spinning (right or left).
 *   White: When not moving.
 */
 void changeLEDColour( );

#endif
