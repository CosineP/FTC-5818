// 

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

void zeroAll(void)
{
	setLeft(0);
	setRight(0);
	motor[lift] = 0;
	motor[scoop] = 0;
}
