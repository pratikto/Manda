#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
    #include "arduino.h"
#else
    #include "WProgram.h"
#endif

class FlowSensor
{
protected:
	float _VolumeAcc;
	//axis deviation
	float _xDev;
	//previous measurement value
	float _prevValue;



public:
	//constructor
	FlowSensor();

	//constructor
	FlowSensor(const float xDev);

	// Detect if the provided sample is a positive or negative peak.
	// Will return 0 if no peak detected, 1 if a positive peak and -1
	// if a negative peak.
	float detect(float sample);

	// Detect if the provided sample is a positive or negative peak.
	// Will return 0 if no peak detected, 1 if a positive peak and -1
	// if a negative peak.
	float detect();
	
	//return volume accumulator
	float VolumeAcc();

	//set volume accumulator
	void VolumeAcc(float);

	//measurement value
	float value;
};

