#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     left,          tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     right,         tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

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
			motor[left] = (joystickToMotor(joystick.joy1_y1));
			motor[right] = (joystickToMotor(joystick.joy1_y2));
		}
		else
		{
			motor[left] = (joystickToMotor(joystick.joy1_x1 * -1 + joystick.joy1_y1));
			motor[right] = (joystickToMotor(joystick.joy1_x1 + joystick.joy1_y1));
		}
	}
	return;
}
