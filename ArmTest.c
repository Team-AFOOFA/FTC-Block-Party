#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     LeftIR,         sensorI2CCustom)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     RightDrive,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     LeftDrive,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     Arm,           tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     Slider,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     Flag,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     NoMotor,       tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    RightHook,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    LeftHook,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "rdpartyrobotcdr-3.3.1\drivers\hitechnic-sensormux.h"
#include "drivers/lego-light.h"

#include "Move_Library.c"

const tMUXSensor ArmLowerLimit = msensor_S3_4;

task main()
{
	// Turn the light on
  LSsetActive(ArmLowerLimit);

	//nMotorPIDSpeedCtrl[Arm] = mtrSpeedReg;
	bFloatDuringInactiveMotorPWM = false;

  while (true)
  {
  		nxtDisplayString(3, "LV=%d", SensorValue[ArmLowerLimit]);
	    //If the left button is pressed on the nxt, move the arm down
	    if(nNxtButtonPressed == 2)
	  	{
	  		//if((SensorValue[ArmLowerLimit]) > 45)
	  		if(LSvalNorm(ArmLowerLimit) > 45)
	  			motor[Arm] = 0;
	  		else
	      	motor[Arm] = -70;
	    }
	    	    //If the right button is pressed on the nxt, move the arm up
	    else if(nNxtButtonPressed == 1)
	 		{
	 			motor[Arm] = 70;
	    }
	    //If no buttons on the NXT are pressed, dont move the arm
	    else if(nNxtButtonPressed == -1)
	    {
	      motor[Arm] = 0;
	    }
	    wait1Msec(5);
	 }
}
