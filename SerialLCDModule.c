/*-----------------------------------
* File name: SerialLCDModule.c
* Authors: Daniel Hong , Saba Shaikh
* Description: Module for interfacing with the LCD screen, including formating for
* temperature display
*-----------------------------------*/

#include "SerialLCDModule.h"
#include "thermalSensor.h"
#include "WheelMotion.h"

int thisUsartID = USART1_ID;


/*
 * Executes LCD extended commands and takes care of the command initiation code needed
 * @param command command number to be sent
 */
void extendedCommand(int8_t command){
	usartWrite(thisUsartID, 254);
	usartWrite(thisUsartID, command);
}
/**
 *Prints a string to a specified position and row
 *@param displayString string to send to the LCD
 *@param row row to print to, 0 or 1
 *@param position position to print to , 0-15
 */
void lcdTextWrite(uint8_t * displayString, int row, int position){
//	int modifiedSring = position + 128;//set to the right code
	if(row == 1){
		position += 64;//if second row, add 64 to set it to row 2
	}
	extendedCommand((position + 128));//position the typing
	usart_fprint(thisUsartID, displayString);//print
}
/*
 * Prints temperature with an ambient temperature label.
 * @param temp temperature to print
 */
void displayTemperature(uint8_t temps[9]){
	 TickType_t xLastWakeTime;

			/* The xLastWakeTime variable needs to be initialised with the current tick
			count.  Note that this is the only time we access this variable.  From this
			point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
			API function. */
	xLastWakeTime = xTaskGetTickCount();
	extendedCommand(1);//clear screen
	char str[32];
	sprintf(str, "%d", temps[0]);//convert temperature to number
	lcdTextWrite("AMBT:", 0, 0);//print label
	lcdTextWrite(str ,0,5);//print temp

	sprintf(str, "%d", temps[1]);//convert temperature to number
	lcdTextWrite(str ,0,8);//print temp
	lcdTextWrite(" " ,0,10);//print temp

	sprintf(str, "%d", temps[2]);//convert temperature to number
	lcdTextWrite(str ,0,11);//print temp
	lcdTextWrite(" " ,0,13);//print temp

	sprintf(str, "%d", temps[3]);//convert temperature to number
	lcdTextWrite(str ,0,14);//print temp


	sprintf(str, "%d", temps[4]);//convert temperature to number
	lcdTextWrite(str ,1,0);//print temp
	lcdTextWrite(" " ,1,2);//print temp

	sprintf(str, "%d", temps[5]);//convert temperature to number
	lcdTextWrite(str ,1,3);//print temp
	lcdTextWrite(" " ,1,5);//print temp

	sprintf(str, "%d", temps[6]);//convert temperature to number
	lcdTextWrite(str ,1,6);//print temp
	lcdTextWrite(" " ,1,8);//print temp

	sprintf(str, "%d", temps[7]);//convert temperature to number
	lcdTextWrite(str ,1,9);//print temp
	lcdTextWrite(" " ,1,11);//print temp

	sprintf(str, "%d", temps[8]);//convert temperature to number
	lcdTextWrite(str ,1,12);//print temp
	lcdTextWrite(" " ,1,14);//print temp
	vTaskDelayUntil( &xLastWakeTime, ( 1000 / portTICK_PERIOD_MS ) );
}


void displayDistTemp(){
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	extendedCommand(1);//clear screen
	char str[32];

	lcdTextWrite("SP:", 0, 0);//print label
	snprintf(str, 5, "%f", speed);//convert temperature to number
	lcdTextWrite(str ,0,3);//print temp

	lcdTextWrite("DT:", 0, 8);//print label
	snprintf(str, 6, "%f", distance);//convert temperature to number
	lcdTextWrite(str ,0,11);//print temp

	lcdTextWrite("AMB:", 1, 0);//print label
	sprintf(str, "%d", pixelTemps[0]);//convert temperature to number
	lcdTextWrite(str ,1,4);//print temp

	lcdTextWrite("L:", 1, 7);//print label
	sprintf(str, "%d", pixelTemps[1]);//convert temperature to number
	lcdTextWrite(str ,1,9);//print temp

	lcdTextWrite("R:", 1, 12);//print label
	sprintf(str, "%d", pixelTemps[2]);//convert temperature to number
	lcdTextWrite(str ,1,14);//print temp

	vTaskDelayUntil( &xLastWakeTime, ( 10 / portTICK_PERIOD_MS ) );
}

