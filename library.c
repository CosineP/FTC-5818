// Functions that are used in both teleop and anonymous mode

#include "JoystickDriver.c"

// Library variables

const float spoolCircumference = 6.91; // In centimeters

const int liftAutoSpeed = 75; // TODO: Make this number good

const int amountAboveTubes = 3; // Everything is in centimeters. TODO: Make not arbitrary

const float zeroLift = 0.5; // Going below zero would be disasterous, so we don't even wanna get close. Centimeters.

const float gearingRatio = 3.0/2;

// Library functions

int turnsToEncoders(float turns) { return turns * 1440; }
float encodersToTurns(int encoders) { return encoders / 1440.0; }

void setLift(int velocity, bool checkIfBottom = true)
{
	motor[lift] = velocity;
	if (checkIfBottom)
	{
		bool resetZero = false;
		while (encodersToTurns(nMotorEncoder[lift]) * gearingRatio * spoolCircumference < zeroLift)
		{
			motor[lift] = liftAutoSpeed;
			resetZero = true;
		}
		if (resetZero)
		{
			motor[lift] = 0;
		}
	}
}

void zeroEncoders(void)
{
	nMotorEncoder[lift] = turnsToEncoders(zeroLift / spoolCircumference);
	nMotorEncoder[left] = 0;
	nMotorEncoder[right] = 0;
}
