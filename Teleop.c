#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     leftBack,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     rightBack,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     lift,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     scoop,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     leftFront,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     rightFront,    tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


#include "library.c"

// The RobotC naming. SUCKS. Fix this:

// Joystick naming. Fix the order. Thank you.
#define driver1LeftStickX joystick.joy1_x1
#define driver1LeftStickY joystick.joy1_y1
#define driver1RightStickX joystick.joy1_x2
#define driver1RightStickY joystick.joy1_y2

#define driver2LeftStickX joystick.joy2_x1
#define driver2LeftStickY joystick.joy2_y1
#define driver2RightStickX joystick.joy2_x2
#define driver2RightStickY joystick.joy2_y2

// Button naming. Actual names. Thank you.
#define driver1BtnA joy1Btn(2)
#define driver1BtnB joy1Btn(3)
#define driver1BtnX joy1Btn(1)
#define driver1BtnY joy1Btn(4)
#define driver1BtnL2 joy1Btn(7)
#define driver1BtnR2 joy1Btn(8)

#define driver2BtnA joy2Btn(2)
#define driver2BtnB joy2Btn(3)
#define driver2BtnX joy2Btn(1)
#define driver2BtnY joy2Btn(4)
#define driver2BtnL2 joy2Btn(8)
#define driver2BtnR2 joy2Btn(8)

#define driver1HatUp joy1_TopHat >= 7 || (joy1_TopHat <= 1 && joy1_TopHat != -1)
#define driver1HatDown joy1_TopHat >= 3 && joy1_TopHat <= 5
#define driver1HatRight joy1_TopHat >= 1 && joy1_TopHat <= 3
#define driver1HatLeft joy1_TopHat >= 5 && joy1_TopHat <= 7

#define driver2HatUp joy2_TopHat >= 7 || (joy2_TopHat <= 2 && joy2_TopHat != -2)
#define driver2HatDown joy2_TopHat >= 3 && joy2_TopHat <= 5
#define driver2HatRight joy2_TopHat >= 2 && joy2_TopHat <= 3
#define driver2HatLeft joy2_TopHat >= 5 && joy2_TopHat <= 7


// Teleop-only "library" functions:

// Exponential function to map to the joystickValue
int joystickToMotor(int joystickValue)
{

	int motorValue;
	const int minimumValue = 4; // This value high = less control, less whining; this value low = more fine control, more whining, more magic blue smoke (out of 100)
	const int joystickZero = 5; // Joysticks are very sensitive; it may be a bit off zero when they're not trying to move anything anyway (out of 127)
	if (abs(joystickValue) < joystickZero)
	{
		motorValue = 0;
	}
	else
	{
		// We will play the piccolo
		motorValue = ((pow(1.05, abs(joystickValue)) - 1) / (490.954203 - minimumValue) / 100 + minimumValue) * (joystickValue < 0 ? -1 : 1); // That constant is 1.05^127
	}
	return motorValue;

}

// Reads button values to modify a motor value
int motorModifiers(int motorValue)
{

	if (driver1BtnR2 || driver2BtnR2)
	{
		// R2 to slow /everything/ down to half
		motorValue /= 2;
	}

	return motorValue;

}

// Takes a joystick value, exponents it, and applies modifiers
int fullMotorValue(int joystickValue)
{

	return motorModifiers(joystickToMotor(joystickValue));

}


task main()
{

	// Programwide variables:

	// Servo initialization:

	waitForStart();

	while (true)
	{

		getJoystickSettings(joystick);

		// Each loop cycle code goes here (eg joystick driving):

		/* Joystick 1: Driving layout
		 * Analog sticks: Tankdrive
		 * Hat up/down: Lift control
		 * Buttons for Scoop
		 */

		/* Joystick 2: Lift layout
		 * Analog stick 1: Lift
		 * Analog stick 2: Scoop
		 * Hat for Arcade Drive
		 */

		/* Both Joysticks:
		 * Button A for emergency shutdown
		 * R2 for half-speed everything
		 */

		// Driving Layout (Joystick 1)

		// Tank Drive
		setLeft(fullMotorValue(driver1LeftStickY));
		setRight(fullMotorValue(driver1RightStickY));

		// Lift Hat
		const int liftSpeed = 80;
		motor[lift] = liftSpeed * (driver1HatUp - driver1HatDown);

		// Scoop buttons
		const int scoopSpeed = 90;
		motor[scoop] = scoopSpeed * (driver1BtnX - driver1BtnY);

		// Lift Layout (Joystick 2)

		// Lift
		motor[lift] = fullMotorValue(driver2LeftStickY);

		// Scoop
		motor[scoop] = fullMotorValue(driver2RightStickY);

		// Emergency Shutdown
		if (driver1BtnA || driver2BtnA)
		{
			setLeft(0);
			setRight(0);
			motor[lift] = 0;
			motor[scoop] = 0;
			break;
		}

	}

	return;

}
