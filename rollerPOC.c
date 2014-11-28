#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     Motor,         tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while (true)
  {
	    if(nNxtButtonPressed == 2)
	  	{
	  		motor[Motor] = -70;
	    }
	    	    //If the right button is pressed on the nxt, move the arm up
	    else if(nNxtButtonPressed == 1)
	 		{
	 			motor[Motor] = 70;
	    }
	    //If no buttons on the NXT are pressed, dont move the arm
	    else if(nNxtButtonPressed == -1)
	    {
	      motor[Motor] = 0;
	    }
	    wait1Msec(5);
	 }
}
