
#include "JoystickDriver.c"

void setLeft(int value)
{
	motor[leftBack] = value;
	motor[leftFront] = value;
}

void setRight(int value)
{
	motor[rightBack] = value;
	motor[rightFront] = value;
}
