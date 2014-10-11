#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     leftBack,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     rightBack,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     tread,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     scoop,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     liftLeft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     liftRight,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     leftFront,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     rightFront,    tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "library.c"

int joystickToMotor(int joystickValue)
{
	int motorValue;
	const int margin = 5; // This value high = less control, less whining; this value low = more fine control, more whining, more magic blue smoke
	if (abs(joystickValue) < margin)
	{
		motorValue = 0;
	}
	else
	{
		// We will play the piccolo
		motorValue = ((pow(1.05, abs(joystickValue)) - 1) / 4.899542) * (joystickValue < 0 ? -1 : 1); // That constant is (1.05^127-1)/100
	}
	return motorValue;
}

task main()
{
	// Loopwide variables go here
	bool tankDrive = true;
	// Any servo initialization goes here
	waitForStart();
	// Any motor initialization goes here (Warning: You probably don't want to do that)
	while (true)
	{
		getJoystickSettings(joystick);
		// Each loop cycle code goes here (eg joystick driving)
		if (tankDrive)
		{
			setLeft(joystickToMotor(joystick.joy1_y1));
			setRight(joystickToMotor(joystick.joy1_y2));
		}
		else
		{
			setLeft(joystickToMotor(joystick.joy1_x1 * -1 + joystick.joy1_y1));
			setRight(joystickToMotor(joystick.joy1_x1 + joystick.joy1_y1));
		}
	}
	return;
}
