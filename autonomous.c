#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S2,     irSeeker,       sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     picollo,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     scoop,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     liftRight,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     liftLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     right,         tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     left,          tmotorTetrix, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "library.c"
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment 4.X\Sample Programs\NXT\3rdPartyDriverLibrary\include\hitechnic-irseeker-v2.h"

// Global variables
int ir[6];

// Check whether we arrived at the IR beacon
bool hasArrived(void)
{
	const int arrivedThreshold = 105; // The value the IR beacon gets when we arrive TODO: Make not arbitrary.
	for (int i = 1; i <= 5; i++)
	{
		if (ir[i] > arrivedThreshold) return true;
	}
	return false;
}

void liftHeight(int height, int speed = liftAutoSpeed)
{
	while (abs(encodersToTurns(nMotorEncoder[liftLeft]) * spoolCircumference) < height)
	{
		int goingDown = height > 0 ? 1 : -1;
		setLift(speed * goingDown);
	}
	setLift(0);
}

task main()
{

	// Go somewhat slowly so we can pick up IR
	const int maxSpeed = 100;

	// When we get no signal, we go forward for a little while; this keeps track of piccollos.
	bool wentForwardAlready = false;

	zeroEncoders();

	waitForStart();

	// Make sure we pick of the IR so go forward mann
	motor[left] = maxSpeed;
	motor[right] = maxSpeed;
	//wait1Msec(3500); // TODO: Correct # for 200000 points
	motor[left] = 0;
	motor[right] = 0;

	while(true)
	{

		if (!hasArrived())
		{

			HTIRS2readAllACStrength(irSeeker, ir[1], ir[2], ir[3], ir[4], ir[5]);

			int direction = HTIRS2readACDir(irSeeker);

			const int zeroContinueTime = 200;
			const int correctDirTime = 3000;

			if (direction == 0)
			{
				if (!wentForwardAlready)
				{
					motor[left] = maxSpeed;
					motor[right] = maxSpeed;
					wait1Msec(zeroContinueTime);
					wentForwardAlready = true;
				}
				else
				{
					motor[left] = maxSpeed;
					motor[right] = -maxSpeed;
				}
			}
			else
			{
				wentForwardAlready = false;

				if (direction < 5)
				{
					motor[left] = maxSpeed * -1;
					motor[right] = maxSpeed * 1;
				}
				else if (direction > 5)
				{
					motor[left] = maxSpeed * 1;
					motor[right] = maxSpeed * -1;
				}
				else if (direction == 5)
				{
					motor[left] = maxSpeed;
					motor[right] = maxSpeed;
					clearTimer(T1);
					while (!hasArrived() && time1[T1] < correctDirTime)	{}
				}
			}

			eraseDisplay();
			displayTextLine(0,"HT IR Seeker");
			displayTextLine(2, "dir: %3d", direction);
			displayTextLine(3, "ir1: %3d", ir[1]);
			displayTextLine(4, "ir2: %3d", ir[2]);
			displayTextLine(5, "ir3: %3d", ir[3]);
			displayTextLine(6, "lol: %3d", motor[left]);
			displayTextLine(7, "ror: %3d", motor[right]);
		}

		if (hasArrived())
		{
			motor[left] = 0;
			motor[right] = 0;
			const int height = 120 + amountAboveTubes; // So that we have room for dumping BALLS
			const int ballSpittingOutTime = 750;
			liftHeight(height);
			motor[scoop] = -liftAutoSpeed;
			wait1Msec(ballSpittingOutTime);
			liftHeight(-height);
		}

	}

}
