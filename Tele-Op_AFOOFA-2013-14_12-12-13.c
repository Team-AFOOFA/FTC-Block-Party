#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ArmLimit,       sensorLightActive)
#pragma config(Sensor, S3,     LeftIR,         sensorI2CCustom)
#pragma config(Motor,  motorA,          RotorR,        tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,          RotorL,        tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     RightDrive,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     LeftDrive,     tmotorTetrix, openLoop)
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

#include "drivers/lego-light.h"

/*
#define Container_Stop  servo (Container) = 131;
#define Container_Forward  servo (Container) = 256;
#define Container_Back servo (Container) = 0;
*/

/*/////////////////*/
//Include Libraries//
/*/////////////////*/

#include "JoystickDriver.c"
#include "ServoLibrary.c"

/*/////////////////*/
//Macros for Servos//
/*/////////////////*/

#define RightHookUnlock 220
#define RightHookLock 125
#define LeftHookUnlock 20
#define LeftHookLock 128

void UnlockRightHook() //Function that unlocks the right hook
{
	ServoRotate(RightHook, RightHookUnlock);
}

void LockRightHook() //Function that Locks the right hook
{
	ServoRotate(RightHook, RightHookLock);
}

void UnlockLeftHook() //Function that unlocks the left hook
{
	ServoRotate(LeftHook, LeftHookUnlock);
}

void LockLeftHook() //Function that Locks the left hook
{
	ServoRotate(LeftHook, LeftHookLock);
}
void initializeRobot() //Function which prepares robot for Tele-Op
{

	return;
}

task main()
{
	initializeRobot();
	waitForStart();   // wait for start of tele-op phase

	int MtrPwrLeftDrive = 0;    //Power for Left drive
	int MtrPwrRightDrive = 0;   //Power for Right Drive
	int MtrPwrArm = 0;          //Articulating arm Power
	int MtrPwrRotorL= 0;        //Left Rotor Power
	int MtrPwrRotorR= 0;        //Right Rotor Power
	int MtrPwrSlider = 0;       //Pull-Up Slider Power
	int MtrPwrFlag = 0;         //Flag power

	while(1) //While Loop which continously relays the robot commands from the joysticks
	{
		alive();
		getJoystickSettings(joystick); //Find what joystick buttons are currently pressed

		//Handle Drive Train Power Settings For the Two Joysticks
		float LeftJoyPwr = ((joystick.joy1_y1) * 0.78125);      //Turn joystick values into 0-100 coordinate plane
		float RightJoyPwr   = ((joystick.joy1_y2) * 0.78125);   //Turn joystick values into 0-100 coordinate plane

		//If the Value Given By the Joysticks is too low to Move the Drive Train, Set the Power to 0
		if(abs(RightJoyPwr) <= 15)
			RightJoyPwr = 0;
		if(abs(LeftJoyPwr) <= 15)
			LeftJoyPwr = 0;

		//////////////////////////////////
		//Setting Power for Drive Train,//
		//Joystick 1                    //
		//////////////////////////////////

		if(joy1Btn(4) == 1) //Button 4 = go forward
		{
			if(joy1Btn(9) == 1)         //Button 9 = go forward at full power
			{
				MtrPwrRightDrive = 100;
				MtrPwrLeftDrive = 100;
			}
			else if(joy1Btn(10) == 1)   //Button 10 = go forward modertely fast
			{
				MtrPwrRightDrive = 75;
				MtrPwrLeftDrive = 75;
			}
			else                        //Normally (just button 4) go at a precise power = 30
			{
				MtrPwrRightDrive = 30;
				MtrPwrLeftDrive = 30;
			}
		}
		else if(joy1Btn(2) == 1) //Button 2 means go backward
		{
			{
			if(joy1Btn(9) == 1)         //Button 9 = go backwards at full power
				MtrPwrRightDrive = -100;
				MtrPwrLeftDrive = -100;
			}
			else if(joy1Btn(10) == 1)   //Button 10 = high power
			{
				MtrPwrRightDrive = -75;
				MtrPwrLeftDrive = -75;
			}
			else                        //If just 2 then go backward at precise 30 power
			{
				MtrPwrRightDrive = -30;
				MtrPwrLeftDrive = -30;
			}
		}
		else if(joy1Btn(1) == 1) //Button 1 means spin left
		{
			if(joy1Btn(9) == 1)         //Button 9 = go backwards at full power
			{
				MtrPwrRightDrive = 100;
				MtrPwrLeftDrive = -100;
			}
			else if(joy1Btn(10) == 1)   //Button 10 = high power
			{
				MtrPwrRightDrive = 75;
				MtrPwrLeftDrive = -75;
			}
			else
			{
				MtrPwrRightDrive = 40;    //If just 1 then go backward at precise 30 power
				MtrPwrLeftDrive = -40;
			}
		}
		else if(joy1Btn(3) == 1) //Button 2 means spin right
		{
			if(joy1Btn(9) == 1)          //Button 9 = go backwards at full power
			{
				MtrPwrRightDrive = -100;
				MtrPwrLeftDrive = 100;
			}
			else if(joy1Btn(10) == 1)    //Button 10 = high power
			{
				MtrPwrRightDrive = -75;
				MtrPwrLeftDrive = 75;
			}
			else                         //If just 3 then go backward at precise 30 power
			{
				MtrPwrRightDrive = -40;
				MtrPwrLeftDrive = 40;
			}
		}
		//If No Buttons Are Pressed, Move The Robot According to the Joysticks
		else
		{
			MtrPwrLeftDrive = LeftJoyPwr;    //set power values defined earlier to values fiven by the joysticks
			MtrPwrRightDrive = RightJoyPwr;
		}

		//Setting Power for Rotor
		if(joy1Btn(5) == 1)      //Button 5 = Left rotor clockwise
		{
			MtrPwrRotorL = 100;
		}
		else if(joy1Btn(7) == 1) //Button 7 = Left rotor counter-clockise
		{
			MtrPwrRotorL = -100;
		}
		else                     //No buttons pressed = no movement for rotor
		{
			MtrPwrRotorL = 0;
		}
		if(joy1Btn(6) == 1)      //Button 6 = Right rotor clockwise
		{
			MtrPwrRotorR = 100;
		}
		else if(joy1Btn(8) == 1) //Button 8 = right rotor counter-clockwise
		{
			MtrPwrRotorR = -100;
		}
		else                     //If no buttons pressed = no movement for rotor
		{
			MtrPwrRotorR = 0;
		}

		////////////////
		//Controller 2//
		////////////////

		//Setting Power for Flag
		if(joy2Btn(5) == 1)      //Button 5 rotates flag turner clockwise
		{
			MtrPwrFlag = 100;
		}
		else if(joy2Btn(6) == 1) //Button 6 rotates flag turner counter-clockwise
		{
			MtrPwrFlag = -100;
		}
		else                     //If no buttons are pressed then don't give any power to the Flag turner
		{
			MtrPwrFlag = 0;
		}

		//Setting Power for Arm
		if(joy2Btn(3) == 1) //Button 3 = Arm up
		{
			/*
			if(joy2Btn(9) == 1)
			{
			MtrPwrArm = 50;
			}
			if(joy2Btn(10) == 1)
			{
			MtrPwrArm = 75;
			}
			else
			*/
			{
				MtrPwrArm = 60;
			}
		}
		else if(joy2Btn(1) == 1) //Button 1 = Arm Down
		{
				MtrPwrArm = -25;
		}
			/*
			if(joy2Btn(9) == 1)
			{
			MtrPwrArm = -50;
			}
			if(joy2Btn(10) == 1)
			{
			MtrPwrArm = -75;
			}
			else
			*/
		}
		else                     //If no buttons are pressed then do not give power to arm
		{
			MtrPwrArm = 0;
		}

		//Setting Power for Slider
		if(joy2Btn(4) == 1) //If button 4 is pressed move the slider up
		{
			MtrPwrSlider = 100;
		}
		else if(joy2Btn(2) == 1) //If button 2 is pressed move slider down
		{
			MtrPwrSlider = -100;
		}
		else                     //If no buttons are pressed then do not give power
		{
			MtrPwrSlider = 0;
		}

		//Settng Movement for Pullup Hook (SERVO)
		if(joy2Btn(8) == 1) //Lock the hooks if button 8 is pressed
		{
			LockRightHook();
			LockLeftHook();
		}
		else if(joy2Btn(9) == 1) //Unlock hooks if button 9 is pressed
		{
			UnlockRightHook();
			UnlockLeftHook();;
		}

		//Set Power to all Motors

		motor[RightDrive] = MtrPwrRightDrive;
		motor[LeftDrive] = MtrPwrLeftDrive;
		motor[Arm] = MtrPwrArm;
		motor[RotorL] = MtrPwrRotorL;
		motor[RotorR] = MtrPwrRotorR;
		motor[Slider] = MtrPwrSlider;
		motor[Flag] = MtrPwrFlag;

		wait1Msec(10); //Give the robot time to execute before refreshing power values again

	}
}
