/*-----------------------------------
* File name: SerialLCDModule.h
* Authors: Daniel Hong , Saba Shaikh
* Description: Module for interfacing with the LCD screen, including formating for
* temperature display
*-----------------------------------*/

#ifndef SERIAL_LCD_MODULE
#define SERIAL_LCD_MODULE

//standard imports
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

//avrio import
#include <avr/io.h>


//USART interaction import
#include "usartSerial.h"


//Methods
/**
 * @author Daniel Hong
 * @author Saba Shaikh
 *
 * Uses writeUSART() from the usartSerial.h module to send commands to the LCD
 * @param command command to send to the LCD. Automatically sends the 254 command indicator before sending the indicated command
 */
void extendedCommand(int8_t command);
/**
 * @author Daniel Hong
 * @author Saba Shaikh
 *
 * Uses extendedCommand() from this module to set the LCD to the desired cursor position
 * and usart_fprint() from the usartSerial.h module display messages on the LCD
 * @param displayString string to display on the LCD
 * @param row row to write to, 0 for the first, 1 for the second
 * @param position position to write to per row, from 0 - 15
 *
 */
void lcdTextWrite(uint8_t * displayString, int row, int position);
/**
 * @author Daniel Hong
 * @author Saba Shaikh
 *
 * Clears the LCD and converts an array of integers to strings via sprintf() and repeatedly uses LCDTextWrite()
 * from this module to set the LCD to the desired cursor position and print to the LCD
 * @param temps an array of nine integers representing the eight pixel temperatures and the ambient temperature
 */
void displayTemperature(uint8_t temps[9]);
/**
 * @author Daniel Hong
 * @author Saba Shaikh
 *
 * Displays the temperatures, speed and distance traveled to the LCD
 */
void displayDistTemp();

#endif
