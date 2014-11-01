// Functions that are used in both teleop and anonymous mode

#include "JoystickDriver.c"

// Library variables

const float spoolCircumference = 6;

const int liftAutoSpeed = 75;

const int amountAboveTubes = 5;

// Library functions

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

void setLift(int velocity)
{
	motor[liftLeft] = velocity;
	motor[liftRight] = velocity;
	syncLift();
}

void zeroEncoders(void)
{
	nMotorEncoder[liftLeft] = 0;
	nMotorEncoder[liftRight] = 0;
	nMotorEncoder[left] = 0;
	nMotorEncoder[right] = 0;
}

int turnsToEncoders(float turns) { return turns * 1440; }
float encodersToTurns(int encoders) { return encoders / 1440.0; }
