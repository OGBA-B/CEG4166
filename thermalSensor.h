/*
 * File name: thermalSensor.h
 * Description: Module to communicate with the thermal array sensor in order to
 * get the temperature readings and make them available to other modules.
 */
#ifndef THERMALSENSOR_H_
#define THERMALSENSOR_H_

/**
 * Variable to hold the average of the ambient temperature & the 8 pixels
 */
extern uint8_t avgTemp;

/**
 * Array to hold the ambient & 8 pixel temperatures
 */
extern uint8_t temps[9];

/**
 * Array to hold the ambient temperature and the average of the 4 right and left pixels.
 */
extern uint8_t pixelTemps[3];

/**
 * Reads temperatures, 1 ambient + 8 pixel temperatures, from thermal array sensor,
 * finds the average of the 4 left and 4 right pixels.
 */
void  ReadTemperature();

#endif /* THERMALSENSOR_H_ */
