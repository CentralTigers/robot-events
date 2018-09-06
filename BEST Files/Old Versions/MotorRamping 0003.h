// Ethan Davenport
// Motor Ramping library
// Version 0003
//
// ------------ Credit ------------
// Code from Collin Stiers on the VEX Forums used for updateSMotor function.
//
// ------------ Usage Instructions ------------
// 1) Import library using '#include "MotorRamping.h"'
// 2) Set up a motor configured however you would like.
// 3) Create a new SmoothMotor named whatever you want using "SmoothMotor <insert name here>;"
// 4) To set up the SmoothMotor for usage, call "initSMotor();" (see add'l comments below)
// 5) When setting motor speed in your main() loop, use "updateSMotor();" instead (see add'l comments below)
// 6) To manually update the max rate of change later, use "sMotorSetMaxChange();" (see add'l comments below)

// Create a SmoothMotor type for managing smoothed motors

typedef struct{
	int power; //				The current power value
	int lastPower; //		The previous power value
	int deltaPower; //	The change in power, from previous to current
	int maxChange; //		The maximum allowable change in power value
	tMotor motorVar; //	The motor to be controlled
} SmoothMotor;

// Initialize a new SmoothMotor given a SmoothMotor m,
// an initial maxChange, and a motor called motorName.

void initSMotor(SmoothMotor m, int maxIn, tMotor motorName){
	m.power = 0;
	m.lastPower = 0;
	m.deltaPower = 0;
	m.maxChange = maxIn;
	m.motorVar = motorName;
}

// Update a SmoothMotor m with a power value powerIn.
// This allows setting and changing the motor's speed.

void updateSMotor(SmoothMotor m, int powerIn){
	m.power = powerIn;
	m.deltaPower = (m.lastPower - m.power);
	if (m.deltaPower > m.maxChange){
		m.deltaPower = m.maxChange;
	}
	m.power = m.lastPower + m.deltaPower;
	motor[m.motorVar] = m.power;
	m.lastPower = m.power;
	wait1Msec(20);
}

// Set the maxChange for a given SmoothMotor m.
// Not normally necessary, but could be useful if you wanted
// a toggleable fine/coarse control mode for your robot.

void sMotorSetMaxChange(SmoothMotor m, int newMax){
	m.maxChange = newMax;
}
