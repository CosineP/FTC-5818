#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C2_1,     scoop,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     picollo,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     lift,          tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     left,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     right,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,      ,             tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    grabber,              tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    door,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    picollo3,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    picollo4,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_5,    picollo5,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_6,    picollo6,             tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "library.c"

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
#define driver1BtnL1 joy1Btn(5)
#define driver1BtnR1 joy1Btn(6)
#define driver1BtnL2 joy1Btn(7)
#define driver1BtnR2 joy1Btn(8)

#define driver2BtnA joy2Btn(2)
#define driver2BtnB joy2Btn(3)
#define driver2BtnX joy2Btn(1)
#define driver2BtnY joy2Btn(4)
#define driver2BtnL1 joy2Btn(5)
#define driver2BtnR1 joy2Btn(6)
#define driver2BtnL2 joy2Btn(7)
#define driver2BtnR2 joy2Btn(8)
#define driver2BtnBack joy2Btn(9)


// Teleop-only "library" functions:

// Exponential function to map to the joystickValue
int joystickToMotor(int joystickValue)
{

	int motorValue;
	const int minimumValue = 4; // This value high = less control, less whining; this value low = more fine control, more whining, more magic blue smoke (out of 100)
	const int joystickZero = 7; // Joysticks are very sensitive; it may be a bit off zero when they're not trying to move anything anyway (out of 127)
	if (abs(joystickValue) < joystickZero)
	{
		motorValue = 0;
	}
	else
	{
		// We will play the piccolo
		const int motorMax = 100;
		int backwards = joystickValue < 0 ? -1 : 1;
		motorValue = (pow(1.05, abs(joystickValue)) / pow(1.05, 127)
			* (motorMax - minimumValue) + minimumValue) * backwards;
	}
	return motorValue;

}

// Reads button values to modify a motor value
int motorModifiers(int motorValue)
{

	if (driver1BtnR2 || driver2BtnR2)
	{
		// R2 to slow everything down to half
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

	// In centimeters, -1 = we're not trying to move
	int movingLiftTo = -1;

	bool asymLift = false; // TODO: Normally this should be false, but... yeah... we suck.

	// If we are not going down, we do not want to go down. If this encoder starts dropping, we panic.
	int lastEncoder = nMotorEncoder[lift];

	// Servo / program initialization:

	zeroEncoders();

	waitForStart();

	while (true)
	{

		getJoystickSettings(joystick);

		// Each loop cycle code goes here (eg joystick driving):

		/* Driver 1: Driving layout
		 * Analog sticks: Tankdrive
		 * A for ungrabbing tube
		 * B for grabbing tube
		 */

		/* Driver 2: Lift layout
		 * Analog stick left: Lift
		 * Analog stick right: Scoop
		 * A for opening scoop door
		 * B for closing scoop door
		 * L1 for screw da lift limit on the bottom
		 * L2 for zero encoders
		 */

		/* Both Joysticks:
		 * R1 for emergency shutdown
		 * R2 for half-speed everything
		 */

		// Driving Layout (Driver 1)

		// Tank drive
		motor[left] = fullMotorValue(driver1LeftStickY);
		motor[right] = fullMotorValue(driver1RightStickY);

		// Grabber
		if (driver1BtnA)
		{
			servo[grabber] = 0;
		}
		if (driver1BtnB)
		{
			servo[grabber] = 127;
		}

		// Lift Layout (Driver 2)

		bool stopAtBottom = true;

		// Screw the limit of the lift that you can't go all the way down
		// Used if we have to emergency shutdown without lowering the lift
		if (driver2BtnL1)
		{
			stopAtBottom = false;
		}

		// Reset encoders if it started in a bad place
		if (driver2BtnL2)
		{
			zeroEncoders();
		}

		// Lift
		setLift(fullMotorValue(driver1LeftStickY), stopAtBottom);

		lastEncoder = nMotorEncoder[lift];

		// Door opening / closing
		if (driver2BtnA)
		{
			servo[door] = 0;
		}
		if (driver2BtnB)
		{
			servo[door] = 127;
		}

		// Scoop
		motor[scoop] = fullMotorValue(driver2RightStickX);

		// Both drivers

		// Emergency shutdown
		if (driver1BtnR1 || driver2BtnR1)
		{
			motor[left] = 0;
			motor[right] = 0;
			setLift(0);
			motor[scoop] = 0;
			break;
		}

	}

	return;

}
