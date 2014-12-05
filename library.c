// Functions that are used in both teleop and anonymous mode

#include "JoystickDriver.c"

// Library variables

const float spoolCircumference = 6.91; // In centimeters

const int liftAutoSpeed = 75;

const int amountAboveTubes = 3; // Everything is in centimeters.

const float zeroLift = 0.5; // Going below zero would be disasterous, so we don't even wanna get close. Centimeters.

// Library functions

int turnsToEncoders(float turns) { return turns * 1440; }
float encodersToTurns(int encoders) { return encoders / 1440.0; }

void syncLift(void)
{
	int speed = motor[liftLeft];
	if (speed != 0)
	{
		while (nMotorEncoder[liftLeft] != nMotorEncoder[liftRight])
		{
			// We're slightly lopsided, better fix this
			bool leftAboveRight = nMotorEncoder[liftLeft] > nMotorEncoder[liftRight];
			motor[liftLeft] = !leftAboveRight * speed;
			motor[liftRight] = leftAboveRight * speed;
		}
		motor[liftLeft] = speed;
		motor[liftRight] = speed;
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
