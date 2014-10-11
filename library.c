
#include "JoystickDriver.c"

void setLeft(int speed)
{
	motor[leftBack] = speed;
	motor[leftFront] = speed;
}

void setRight(int speed)
{
	motor[rightBack] = speed;
	motor[rightFront] = speed;
}
