
#include "drivers\hitechnic-gyro.h"
int GyroValue = 0;
float TimeElapsed = 0;
long currTime;
long prevTime;
float heading = 0.0;
int gPwr = 0;

float getHeading()
{

  //nxtDisplayTextLine(3, "rawGyro:   %4d", HTGYROreadRot(HTGYRO));
  currTime = nPgmTime;
  nxtDisplayTextLine(4, "et:   %1.8f", (float)(currTime - prevTime)/1000.0);
  nxtDisplayTextLine(5, "%4d-%4d",currTime, prevTime);


  GyroValue = HTGYROreadRot(HTGYRO);
  GyroValue = GyroValue + 20; // Calibrating ...
  nxtDisplayTextLine(1, "%d", GyroValue);
  if((GyroValue < 4) && (GyroValue > -4)
    GyroValue = 0;
  nxtDisplayTextLine(2, "%d", GyroValue); // after filtering

  heading += ((float) GyroValue * (float)(currTime - prevTime)/1000.0 ) ;
  prevTime = currTime;
  return heading;
}

task CalcHeading()
{
    prevTime =currTime = nPgmTime;

    while(true)
    {

      eraseDisplay();
      getHeading() ;
      nxtDisplayTextLine(6, "heading %1.4f", heading);

      if(heading > -5)
        gPwr = 20;
      else if(heading < 5)
        gPwr = -20;
      else
      {
        gPwr = 0;
      }

      wait1Msec(10);
    }
}

void BalanceOnBridgeUsingGyro()
{
	  eraseDisplay();
	    nxtDisplayTextLine(1, "Resetting");
	    nxtDisplayTextLine(1, "heading");
	    wait1Msec(100);

	    // Start the calibration and display the offset
	    nxtDisplayTextLine(2, "Offset: %4d", HTGYROstartCal(HTGYRO));
	   // wait10Msec(1000);
	    PlaySound(soundBlip);
	    while(bSoundActive);

	  StartTask(CalcHeading);

	   gPwr = -50;
	   motor[RightMtr] = gPwr;
		 motor[LeftMtr] = gPwr;
	   wait1Msec(2000);
	   //while (true)
	   {
	    gPwr = -25;
	    while(true)
	    {

	        motor[RightMtr] = gPwr;
		      motor[LeftMtr] = gPwr;
		      if( (heading < 5.5) && (heading > -5.5))
		      {
		        motor[RightMtr] = 0;
		        motor[LeftMtr] = 0;
	          wait1Msec(2000);
	  	      break;
	  	    }
	 	      wait1Msec(10);

	    }
	  }
}
