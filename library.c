// Functions that are used in both teleop and anonymous mode

#include "JoystickDriver.c"

// Library variables

const float spoolCircumference = 6.91; // In centimeters

const int liftAutoSpeed = 75; // TODO: Make this number good

const int amountAboveTubes = 3; // Everything is in centimeters. TODO: Make not arbitrary

const float zeroLift = 0.5; // Going below zero would be disasterous, so we don't even wanna get close. Centimeters.

// Library functions

int turnsToEncoders(float turns) { return turns * 1440; }
float encodersToTurns(int encoders) { return encoders / 1440.0; }

void syncLift(void)
{
	int speed = motor[liftLeft];
	if (speed != 0)
	{
		// We're slightly lopsided, better fix this
		bool leftBehind = nMotorEncoder[liftLeft] > nMotorEncoder[liftRight];
		if (speed < 0)
		{
			leftBehind = !leftBehind;
		}
		const float lagBehind = 0.75;
		motor[liftLeft] = !leftBehind * speed + leftBehind * speed * lagBehind;
		motor[liftRight] = leftBehind * speed + !leftBehind * speed * lagBehind;
	}
}

void setLift(int velocity, bool checkIfBottom = true)
{
	if (checkIfBottom)
	{
		while (encodersToTurns(nMotorEncoder[liftLeft]) * spoolCircumference < zeroLift)
		{
			motor[liftLeft] = liftAutoSpeed;
			motor[liftRight] = liftAutoSpeed;
		}
	}
	motor[liftLeft] = velocity;
	motor[liftRight] = velocity;
	syncLift();
}

void zeroEncoders(void)
{
	nMotorEncoder[liftLeft] = turnsToEncoders(zeroLift / spoolCircumference);
	nMotorEncoder[liftRight] = nMotorEncoder[liftLeft];
	nMotorEncoder[left] = 0;
	nMotorEncoder[right] = 0;
}
