// Functions that are used in both teleop and anonymous mode

#include "JoystickDriver.c"

void setLeft(int speed)
{
	motor[leftBack] = speed;
	motor[leftFront] = speed;
}

void setRight(int speed)
{
	motor[rightBack] = speed;
	motor[rightFront] = speed;
}

void setLift(int speed)
{
	motor[liftLeft] = speed;
	motor[liftRight] = speed;
}

// moveMotorTurns(backLeft, 100, -4.5); Will turn motor backwards 4 times and 180 degrees after that
// Warning: will delete encoder value, should backup if you will need it later
void moveMotorTurns(int motorType, int speed, float turns)
{
	int originalSpeed = motor[motorType];
	motor[motorType] = speed * (turns < 0 ? -1 : 1);
	nMotorEncoder[motorType] = 0;
	int encoderValue = abs(turns) * 1440; // Encoder value per rotation
	while (abs(nMotorEncoder[motorType]) < encoderValue)	{}
	motor[motorType] = 0;
}

void liftHeight(int height)
{
	// All Measurements in centimeters
	// Todo: Warning: Circumference is subject to change
	const int spoolCircumference = 6;
	moveMotorTurns(liftLeft, 50, height/spoolCircumference);
}
