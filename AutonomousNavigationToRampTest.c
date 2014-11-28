#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     LeftIR,         sensorI2CCustom)
#pragma config(Motor,  motorA,          RotorR,        tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,          RotorL,        tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     RightDrive,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     LeftDrive,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     Arm,           tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     Slider,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     Flag,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     NoMotor,       tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    AutonomousBlock,      tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    LeftHook,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    RightHook,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "drivers/hitechnic-irseeker-v2.h"
#include "ServoLibrary.c"
#include "JoystickDriver.c"

task main()
{
	nMotorEncoder[RightDrive] = 0;
	while(nMotorEncoder[RightDrive] < 1000) //Move robot to 7600 degrees of total rottion regardless of the position of the IR Beacon
		{
			motor[LeftDrive] = 60;
			motor[RightDrive] = 60;
			wait10Msec(2);
		}
	motor[LeftDrive] = 0; //Brake Motors
	motor[RightDrive] = 0;
}