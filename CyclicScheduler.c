/*
 * File name: CyclicScheduler.c
 * Description: Cyclic Scheduler module for scheduling the tasks to be executed.
 */
#include "SerialLCDModule.h"
#include "WheelMotion.h"
#include "thermalSensor.h"
#include "ledModule.h"

typedef void (*TASK)(void);

/**
 * The number of tasks to be executed
 */
#define NUM_MINOR_CYCLES 6

/**
 * The minor cycle time (frame size) for each task.
 */
#define MINOR_CYCLE_TIME 1

/**
 * The tasks to be executed.
 */
TASK table[NUM_MINOR_CYCLES] = {
		ReadTemperature,
		Motion,
		Speed,
		MoveMount,
		displayDistTemp,
		changeLEDColour
		};

void Scheduler() {
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	int taskNum = 0;

	while (1) {

		if (table[taskNum] != NULL) {
			table[taskNum]();
		}
		vTaskDelayUntil(&xLastWakeTime, ( MINOR_CYCLE_TIME / portTICK_PERIOD_MS));
		taskNum = (taskNum + 1) % NUM_MINOR_CYCLES;


	}
}
