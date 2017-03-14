/*
 * File name: WheelMotion.c
 * Description: Module to communicate with the servomotors,
 *  to enable controlling the wheels and the head mount.
 */

#include "motion.h"
#include "WheelMotion.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "usartserial.h"
#include "SerialLCDModule.h"
#include <stdio.h>


int pos = INITIAL_PULSE_WIDTH_TICKS;
bool flag1 = false;

int direction = 0;
int directionCount = 0;

//Speed Variables
uint32_t tickCountRight[1];
uint32_t tickCountLeft[1];
double leftWheelSpeed = 0;
double rightWheelSpeed = 0;
double rightWheelDistance = 0;
double leftWheelDistance = 0;
double speed = 0;
double distance = 0;

void MoveForward() {
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	motion_init();
	motion_servo_start(MOTION_WHEEL_RIGHT);
	motion_servo_set_pulse_width(MOTION_WHEEL_RIGHT, 1100);
	motion_servo_start(MOTION_WHEEL_LEFT);
	motion_servo_set_pulse_width(MOTION_WHEEL_LEFT, 4660);
	vTaskDelayUntil(&xLastWakeTime, (5 / portTICK_PERIOD_MS));
}

void MoveMount(void) {
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	motion_servo_start(MOTION_SERVO_CENTER);

	if (direction==4) {
		motion_servo_set_pulse_width(MOTION_SERVO_CENTER, INITIAL_PULSE_WIDTH_TICKS);
		vTaskDelayUntil(&xLastWakeTime, (100 / portTICK_PERIOD_MS));
		pos = motion_servo_get_pulse_width(MOTION_SERVO_CENTER);
	} else {
		if (!flag1) {
			motion_servo_set_pulse_width(MOTION_SERVO_CENTER, pos + 20);
			vTaskDelayUntil(&xLastWakeTime, (50 / portTICK_PERIOD_MS));
			pos += 20;
			if (pos >= (4200))
				flag1 = true;
		} else if (flag1) {
			motion_servo_set_pulse_width(MOTION_SERVO_CENTER, pos - 20);
			vTaskDelayUntil(&xLastWakeTime, (50 / portTICK_PERIOD_MS));
			pos -= 20;
			if (pos <= MIN_PULSE_WIDTH_TICKS)
				flag1 = false;
		}
	}
}

/**
 * direction	0: Moving forward;
 * 				1: Moving Backwards;
 * 				2: SpinClockwise;
 * 				3: SpinCounterClockWise;
 * 				4: Stopped;
 */
void Motion(void) {
	motion_init();

	if (direction == 0) {
		directionCount += 1;
		MoveForward();
	} else if (direction == 1) {
		directionCount += 1;
		MoveBackward();
	} else if (direction == 2) {
		directionCount += 1;
		SpinClockwise();
	} else if (direction == 3) {
		directionCount += 1;
		SpinCounterClockwise();
	} else if (direction == 4) {
		directionCount += 1;
		StopRobot();
	}
	if (directionCount > 30) {
		directionCount = 0;
		direction = (direction + 1) % 5;
	}

}

void Speed() {
	double leftTime=0; double rightTime=0;
	if (motion_enc_read(MOTION_WHEEL_LEFT, &tickCountLeft) == 1) {
		leftTime = (tickCountLeft[0] * 0.0000005);
		leftWheelDistance += 0.54;
	}

	if (motion_enc_read(MOTION_WHEEL_RIGHT, &tickCountRight) == 1) {
		rightTime = (tickCountRight[0] * 0.0000005);
		rightWheelDistance += 0.54;
	}

	distance = (leftWheelDistance + rightWheelDistance) / 2;
	if ( leftTime==0 && rightTime==0 ) {
		speed = 0;
	} else {
		speed = 0.54 / ( (leftTime + rightTime)/2 );
	}
}

void SpinClockwise() {
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	motion_servo_start(MOTION_WHEEL_RIGHT);
	motion_servo_set_pulse_width(MOTION_WHEEL_RIGHT, 1100);
	motion_servo_start(MOTION_WHEEL_LEFT);
	motion_servo_set_pulse_width(MOTION_WHEEL_LEFT, 1100);
	vTaskDelayUntil(&xLastWakeTime, (50 / portTICK_PERIOD_MS));

}

void SpinCounterClockwise() {
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	motion_servo_start(MOTION_WHEEL_RIGHT);
	motion_servo_set_pulse_width(MOTION_WHEEL_RIGHT, 4660);
	motion_servo_start(MOTION_WHEEL_LEFT);
	motion_servo_set_pulse_width(MOTION_WHEEL_LEFT, 4660);
	vTaskDelayUntil(&xLastWakeTime, (50 / portTICK_PERIOD_MS));
}

void MoveBackward() {
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	motion_servo_start(MOTION_WHEEL_RIGHT);
	motion_servo_set_pulse_width(MOTION_WHEEL_RIGHT, 4660);
	motion_servo_start(MOTION_WHEEL_LEFT);
	motion_servo_set_pulse_width(MOTION_WHEEL_LEFT, 1100);
	vTaskDelayUntil(&xLastWakeTime, (50 / portTICK_PERIOD_MS));
}

void StopRobot() {
	motion_servo_stop(MOTION_WHEEL_RIGHT);
	motion_servo_stop(MOTION_WHEEL_LEFT);
}
