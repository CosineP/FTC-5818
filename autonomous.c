// moveMotorTurns(backLeft, -100, 4.5); Will turn motor backwards 4 times and 180 degrees after that
// Warning: will delete encoder value, should backup if you will need it later
void moveMotorTurns(int motorType, int speed, float turns)
{
	int originalSpeed = motor[motorType];
	motor[motorType] = speed;
	nMotorEncoder[motorType] = 0;
	int encoderValue = turns * 1440; // Encoder value per rotation
	while (abs(nMotorEncoder[motorType]) < encoderValue)	{}
	motor[motorType] = 0;
}
