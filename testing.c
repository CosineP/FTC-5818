#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     picollo,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     scoop,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     liftRight,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     liftLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     left,          tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     right,         tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    door,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    grabber,              tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard !!*//

//#include "library.c"
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment 4.X\Sample Programs\NXT\3rdPartyDriverLibrary\include\hitechnic-irseeker-v2.h"

// Global variables

task main()
{

    while (1)
    {
        servo[door] = 0;
    }

    // This is for testing n' shit if ever needed
	// eraseDisplay();
	// displayTextLine(0,"HT IR Seeker");
	// displayTextLine(2, "dir: %3d", direction);
	// displayTextLine(3, "ir1: %3d", ir[1]);
	// displayTextLine(4, "ir2: %3d", ir[2]);
	// displayTextLine(5, "ir3: %3d", ir[3]);
	// displayTextLine(6, "lol: %3d", motor[left]);
	// displayTextLine(7, "ror: %3d", motor[right]);

}
