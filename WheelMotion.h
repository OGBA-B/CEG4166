/*
 * File name: WheelMotion.h
 * Description: Module to communicate with the servomotors,
 *  to enable controlling the wheels and the head mount.
 */

#ifndef WHEELMOTION_H_
#define WHEELMOTION_H_

/**
 * The current speed of the robot
 */
extern double speed;
/**
 * The distance covered by the robot
 */
extern double distance;
/**
 * direction	0: Moving forward;
 * 				1: Moving Backwards;
 * 				2: SpinClockwise;
 * 				3: SpinCounterClockWise;
 * 				4: Stopped;
 */
extern int direction;

/**
 * Controls the direction the robot is moving in and stop the robot
 * by calling the move and stop functions.
 */
void Motion(void);

/**
 * Moves the robot forward
 */
void MoveForward(void);

/**
 * Moves the robot backwards.
 */
void MoveBackward(void);

/**
 * Moves the head mount of the robot to one end
 * and then back to the other end.
 */
void MoveMount(void);

/**
 * Calculates the speed the robot is moving in.
 * Calcsulates the distance covered by the robot.
 */
void Speed(void);

/**
 * Spins the robot to the right.
 */
void SpinClockwise(void);

/**
 * Spins the robot to the left
 */
void SpinCounterClockwise(void);

/**
 * Stops the robot
 */
void StopRobot (void);


#endif /* WHEELMOTION_H_ */
