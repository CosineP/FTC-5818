// Functions that are used in both teleop and anonymous mode

#include "JoystickDriver.c"

// Joystick naming
#define driver1LeftStickX joystick.joy1_x1
#define driver1LeftStickY joystick.joy1_y1
#define driver1RightStickX joystick.joy1_x2
#define driver1RightStickY joystick.joy1_y2

#define driver2LeftStickX joystick.joy2_x1
#define driver2LeftStickY joystick.joy2_y1
#define driver2RightStickX joystick.joy2_x2
#define driver2RightStickY joystick.joy2_y2

// Button naming

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

// Library variables

const float spoolCircumference = 6.91; // In centimeters

const int liftAutoSpeed = 100; // TODO: Make this number good

const int amountAboveTubes = 3; // Everything is in centimeters. TODO: Make not arbitrary

const float zeroLift = 0.25; // Going below zero would be disasterous, so we don't even wanna get close. Centimeters.

const float gearingRatio = 1.0/4;

// Library functions

int turnsToEncoders(float turns) { return turns * 1440; }
float encodersToTurns(int encoders) { return encoders / 1440.0; }

void setLift(int velocity)
{
	motor[lift] = velocity;
	// This stores if we ever actually did have to adjust something
	bool resetZero = false;
	while (encodersToTurns(nMotorEncoder[lift]) * gearingRatio * spoolCircumference < zeroLift && !driver2BtnL1)
	{
		int thingy = (int)(nMotorEncoder[lift]);
		displayTextLine(0, "Hello thi%3d", thingy);
		motor[lift] = liftAutoSpeed;
		resetZero = true;
	}
	if (resetZero)
	{
		motor[lift] = velocity;
	}
}

void zeroEncoders(void)
{
	nMotorEncoder[lift] = turnsToEncoders(zeroLift / spoolCircumference);
	nMotorEncoder[left] = 0;
	nMotorEncoder[right] = 0;
	servo[door] = 100;
	servo[grabber] = 127;
}
