/*
 * File name: thermalSensor.c
 * Description: Module to communicate with the thermal array sensor in order to
 * get the temperature readings and make them available to other modules.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "i2cMultiMaster.h"
#include "ledModule.h"
#include "SerialLCDModule.h"
#include "usartserial.h"

/**
 * Variable to hold the average of the ambient temperature & the 8 pixels
 */
uint8_t avgTemp = 27;

//Array to hold the ambient & 8 pixel temperatures.
uint8_t temps[9];

//Array to hold the ambient temperature and the average of the 4 right and left pixels.
uint8_t pixelTemps[3];


/**
 * Reads temperatures, 1 ambient + 8 pixel temperatures, from thermal array sensor,
 * finds the average of the 4 left and 4 right pixels.
 */
void ReadTemperature(){

	//The chosen address of the master.
	uint8_t master = 0xB4;

	//array to store the write command and internal register address
	uint8_t toWrite[] = {0xD0, 0x01, 0xD0, 0x02, 0xD0, 0x03, 0xD0, 0x04, 0xD0, 0x05, 0xD0, 0x06, 0xD0, 0x07, 0xD0, 0x08, 0xD0, 0x09};

	//The read command followed by an empty location to store temperature reading.
	uint8_t toRead[] = {0xD1, 0xA4};

	//the requested data from the transceiver.
	uint8_t dataREQ[18];

		for (int i=0; i<9; i++)
		{
			//Start sequence.
			I2C_Master_Initialise(master);

			//Send I2C address of the thermal sensor, with the write command
			//& the internal address of the register.
			I2C_Master_Start_Transceiver_With_Data((toWrite+(i*2)), 2);

			//Send I2C address of the thermal sensor, with the read command
			//& Read data byte from thermal sensor.
			I2C_Master_Start_Transceiver_With_Data(toRead,2);	// Read with D1 and select reg # using array

			//retrieve data recorded from the thermal sensor and store it in the
			//dataREq array
			I2C_Master_Get_Data_From_Transceiver(dataREQ+(i*2), 2);
		}

		//ambient temperature
		temps[0] = *(dataREQ+1);

		//Find the average of the abient temperature and the 8 pixel temperatures
		int sumTemp = 0; //sum of the temperatures.
		for (int j=1; j<9; j++) {
			sumTemp += *(dataREQ+ ((j*2) + 1) );
			temps[j] = *(dataREQ+ ((j*2) + 1) );
		}
		avgTemp = sumTemp/8;

		pixelTemps[0] = temps[0];

		sumTemp = 0;
		for (int j=1; j<=4; j++ ){
			sumTemp += temps[j];
		}
		pixelTemps[1] = sumTemp/4;

		sumTemp = 0;
		for (int j=5; j<9; j++ ){
			sumTemp += temps[j];
		}
		pixelTemps[2] = sumTemp/4;

}


