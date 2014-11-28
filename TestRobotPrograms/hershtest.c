#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S2,     LeftIR,         sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     LeftMtr,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     RightMtr,      tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C2_1,    AutonomousBlock,      tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "drivers/hitechnic-irseeker-v2.h"
#include "ServoLibrary.c"

void Move(int MtrPwr_Left, int MtrPwr_Right, int MtrDur_Left, int MtrDur_Right)
{
 	nMotorEncoder[LeftMtr] = 0;
	nMotorEncoder[RightMtr] = 0;

 	nMotorEncoderTarget[LeftMtr] = -MtrDur_Left;
 	nMotorEncoderTarget[RightMtr] = -MtrDur_Right;

 	motor[LeftMtr] = MtrPwr_Left;
 	motor[RightMtr] = MtrPwr_Right;

 	while ( (nMotorRunState[LeftMtr] != runStateIdle) &&
   	     	(nMotorRunState[RightMtr] != runStateIdle) )
 	{
   	//wait
 	}

 	motor[LeftMtr] = 0;
  motor[RightMtr] = 0;
}

task main()
{
	Move(-60, 60, 1950, 1950);

	Move(60, 60, 3100, 3100);

	Move(-60, 60, 1950, 1950);

	Move(60, 60, 4000, 4000);
}
