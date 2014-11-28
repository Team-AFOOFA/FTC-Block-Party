#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     LeftIR,         sensorI2CCustom)
#pragma config(Motor,  motorA,          RotorR,        tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,          RotorL,        tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     RightDrive,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     LeftDrive,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     Arm,           tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     Slider,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     Flag,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     NoMotor,       tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    AutonomousBlock,      tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    LeftHook,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    RightHook,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    BasketTiltL,          tServoStandard)
#pragma config(Servo,  srvo_S1_C4_5,    BasketTiltR,          tServoStandard)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "drivers/hitechnic-irseeker-v2.h"
#include "ServoLibrary.c"
#include "JoystickDriver.c"
#include "Move_Library.c"

unsigned int StartWait = 0;

void initializeRobot() //Function which will setup the robot for autonomous (raise hooks and keep block thrower up)
{
	// Set DSP mode to 1200 Hz.
  tHTIRS2DSPMode _mode = DSP_1200;

 	disableDiagnosticsDisplay();

	StartTask(ResetBasket);
	LockRightHook();
	LockLeftHook();

	bFloatDuringInactiveMotorPWM = false;

	nMotorEncoder[LeftDrive] = 0;//Reset encoders for drivetrain motors
	nMotorEncoder[RightDrive] = 0;

	ServoRotate(AutonomousBlock, 240);

	while(nNxtButtonPressed != 3)
	{
		if(nNxtButtonPressed == 1)
			StartWait = StartWait + 1000;
		else if (nNxtButtonPressed == 2)
			if(StartWait > 0)
				StartWait = StartWait - 1000;
		else
		{
			//Do nothing
		}
		nxtDisplayCenteredTextLine(0, "%d ms delay", StartWait);
		wait1Msec(400);
	}

	bDisplayDiagnostics = true;

	return;
}

task main()
{
		//use NXT buttons to select autonomous route and time delay

		//bDisplayDiagnostics = false;   // Disable diagnostic display
		initializeRobot();

  	waitForStart(); // Wait for the beginning of autonomous phase.

  	wait1Msec(StartWait);
  	PlaySound(soundBeepBeep);


		//UnlockRightHook();
		//UnlockLeftHook();
		//Add wait here if
		int LeftIRVal = HTIRS2readACDir(LeftIR); //Initialize variable storing left IR sensor value

		nMotorEncoder[RightDrive] = 0;

    motor[LeftDrive] = 30;
		motor[RightDrive] = 30;
		wait10Msec(5);

		while(LeftIRVal != 6) //move forward until robot is perpendicular to IR beacon
		{
			motor[LeftDrive] = 70;
			motor[RightDrive] = 70;
			wait10Msec(1);

			LeftIRVal = HTIRS2readACDir(LeftIR); //refresh the current IR value
		}
		motor[LeftDrive] = 0; //Brake Motors
		motor[RightDrive] = 0;

		wait1Msec(200);

		if(nMotorEncoder[RightDrive] > 3500){
			motor[LeftDrive] = -50;
			motor[RightDrive] = -50;
			wait1Msec(200);
		}
		motor[LeftDrive] = 0; //Brake Motors
		motor[RightDrive] = 0;

		ServoRotate (AutonomousBlock,30); //Rotating Servo to put block in basket
		ServoRotate (AutonomousBlock,130);//Rotate Servo inside robot

		//nxtDisplayCenteredTextLine(3, "%d", nMotorEncoder[RightDrive]);//display current encoder values for drive train motors on screen

		while(nMotorEncoder[RightDrive] < 7700){
			motor[LeftDrive] = 70;
			motor[RightDrive] = 70;
			wait1Msec(10);
		}
		motor[LeftDrive] = 0; //Brake Motors7
		motor[RightDrive] = 0;

		wait1Msec(500);

		Move(-70, 70, 1450, 1450);
		Move(70, 70, 4400, 4400);
		Move(80, -80, 2100, 2100);
		motor[Arm] = 45;//Raise arm for safe navigation over ramp. This is so that the bottom of the end effector does not hit the
		wait1Msec(500); //bump at the bottom of the ramp.
		motor[Arm] = 0;
		Move(-100, -100, 6500, 6500);

		ServoRotate(AutonomousBlock, 240);

		while(1){wait10Msec(10);} //wait until end of autonomous time period
}
