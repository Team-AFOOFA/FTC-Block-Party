#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     RightMtr,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     LeftMtr,       tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"


task main()
{
  //waitForStart();   // wait for start of tele-op phase

	int MtrPwrLeftFront = 0;
	int MtrPwrLeftBack = 0;
	int MtrPwrRightFront = 0;
	int MtrPwrRightBack = 0;

	while(1)
	{
			alive();
			getJoystickSettings(joystick);

			//Handle Drive Train Power Settings For the Two Joysticks
			float RtPwr = ((joystick.joy1_y1) * 0.78125);
			float LtPwr = ((joystick.joy1_y2) * 0.78125);

			//If the Value Given By the Joysticks is too low to Move the Drive Train, Set the Power to 0
			if(abs(RtPwr) <= 20)
					RtPwr = 0;
			if(abs(LtPwr) <= 20)
					LtPwr = 0;

		 	motor[RightMtr] = RtPwr;
		 	motor[LeftMtr] = LtPwr;

			wait1Msec(10);
	}
}
