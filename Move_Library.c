#define SPIN_360 9000	//for ring it up tank drive bot
#define SPIN(x) ((SPIN_360/360)* x)

void Move(int MtrPwr_Left, int MtrPwr_Right, int waitInMSec)
{
 //nMotorPIDSpeedCtrl[LeftDrive] = mtrSpeedReg;
 //nMotorPIDSpeedCtrl[RightDrive] = mtrSpeedReg;

 motor[LeftDrive] = MtrPwr_Left;
 motor[RightDrive] = MtrPwr_Right;

 wait1Msec(waitInMSec);

 motor[LeftDrive] = 0;
 motor[RightDrive] = 0;

 //nMotorPIDSpeedCtrl[RightDrive] = mtrNoReg;
 //nMotorPIDSpeedCtrl[LeftDrive] = mtrNoReg;

 }

void RaiseArticArm(int MtrPwr, int MtrDur)
{
 nMotorPIDSpeedCtrl[Arm] = mtrSpeedReg;
 nMotorEncoder[Arm] = 0;
 nMotorEncoderTarget[Arm] = MtrDur;
 motor[Arm] = MtrPwr;

 while (nMotorRunState[Arm] != runStateIdle)
 {
   //wait
 }

 motor[Arm] = 0;
 nMotorPIDSpeedCtrl[Arm] = mtrNoReg;
}

void Move(int MtrPwrLeft, int MtrPwrRight, int MtrDurLeft, int MtrDurRight)
{
 nMotorPIDSpeedCtrl[LeftDrive] = mtrSpeedReg;
 nMotorPIDSpeedCtrl[RightDrive] = mtrSpeedReg;

 nMotorEncoder[LeftDrive] = 0;
 nMotorEncoder[RightDrive] = 0;

 nMotorEncoderTarget[LeftDrive] = MtrDurLeft;
 nMotorEncoderTarget[RightDrive] = MtrDurRight;

 motor[LeftDrive] = MtrPwrLeft;
 motor[RightDrive] = MtrPwrRight;

 while ( (nMotorRunState[LeftDrive] != runStateIdle) &&
   	    (nMotorRunState[RightDrive] != runStateIdle)  )
 {
  	wait1Msec(5);
   //wait
 	}

 motor[LeftDrive] = 0;
 motor[RightDrive] = 0;

 nMotorPIDSpeedCtrl[LeftDrive] = mtrNoReg;
 nMotorPIDSpeedCtrl[RightDrive] = mtrNoReg;

}


/*
void Move(int MtrPwrLeft, int MtrPwrRight, int MtrDurLeft, int MtrDurRight, bool enablePID = true)
{
 if(enablePID == true)
 {
 nMotorPIDSpeedCtrl[LeftDrive] = mtrSpeedReg;
 nMotorPIDSpeedCtrl[RightDrive] = mtrSpeedReg;
}

 nMotorEncoder[LeftDrive] = 0;
 nMotorEncoder[RightDrive] = 0;

 nMotorEncoderTarget[LeftDrive] = MtrDurLeft;
 nMotorEncoderTarget[RightDrive] = MtrDurRight;

 motor[LeftDrive] = MtrPwrLeft;
 motor[RightDrive] = MtrPwrRight;

 while ( (nMotorRunState[LeftDrive] != runStateIdle) &&
   	    (nMotorRunState[RightDrive] != runStateIdle)  )
 {
  	wait1Msec(5);
   //wait
 	}

 motor[LeftDrive] = 0;
 motor[RightDrive] = 0;

 nMotorPIDSpeedCtrl[LeftDrive] = mtrNoReg;
 nMotorPIDSpeedCtrl[RightDrive] = mtrNoReg;

}
*/
void stopMotors()
{
 	motor[LeftDrive] = 0;
 	motor[RightDrive] = 0;
}

void moveForTime (int powerLeft, int powerRight, int mSecs)
{
	motor[LeftDrive] = powerLeft;
 	motor[RightDrive] = powerRight;

 	wait1Msec(mSecs);

 	motor[LeftDrive] = 0;
 	motor[RightDrive] = 0;
}

void MoveForward(int MtrPwr, int MtrDur)
{
 if(MtrPwr < 0)
     MtrPwr = MtrPwr * -1;
 if(MtrDur < 0)
     MtrDur = MtrDur * -1;

 Move(MtrPwr, MtrPwr, MtrDur, MtrDur);
}

void MoveBackward(int MtrPwr, int MtrDur)
{
 if(MtrPwr < 0)
     MtrPwr = MtrPwr * -1;
 if(MtrDur < 0)
     MtrDur = MtrDur * -1;

  Move(-MtrPwr, -MtrPwr, -MtrDur, -MtrDur);
}

void SpinRight(int MtrPwr, int MtrDur)
{
 if(MtrPwr < 0)
     MtrPwr = MtrPwr * -1;
 if(MtrDur < 0)
     MtrDur = MtrDur * -1;

  Move(-MtrPwr, MtrPwr, -MtrDur, MtrDur);
}

void SpinLeft(int MtrPwr, int MtrDur)
{
 if(MtrPwr < 0)
     MtrPwr = MtrPwr * -1;
 if(MtrDur < 0)
     MtrDur = MtrDur * -1;

  Move(MtrPwr, -MtrPwr, MtrDur, -MtrDur);
}
