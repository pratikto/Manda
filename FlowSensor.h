#pragma once
#include "PeakDetector.h"

#if defined(ARDUINO) && ARDUINO >= 100
    #include "arduino.h"
#else
    #include "WProgram.h"
#endif

class FlowSensor :
    public PeakDetector
{
protected:
	int _peak;
	//previous peak indicator
	int _prevPeak;
	//absolute area of tidal volume
	float _tidalVolume;
	float _VolumeAcc;
	//axis deviation
	float _xDev;
	//previous measurement value
	float _prevValue;



public:
	//constructor
	FlowSensor();

	//constructor
	FlowSensor(const int lag, const float threshold, const float influence);

	//constructor
	FlowSensor(const float xDev, const int lag, const float threshold, const float influence);

	// Detect if the provided sample is a positive or negative peak.
	// Will return 0 if no peak detected, 1 if a positive peak and -1
	// if a negative peak.
	int detect(float sample) override;

	// Detect if the provided sample is a positive or negative peak.
	// Will return 0 if no peak detected, 1 if a positive peak and -1
	// if a negative peak.
	int detect();

	// Detect if the provided sample is a positive or negative peak.
	// Will return 0 if no peak detected, 1 if a positive peak and -1
	// if a negative peak.
	//int detect() override;

	////return _PPeak value
	//float PPeak();

	////return PMean value
	//float PAverage();

	////return PPEP value
	//float PPEP();

	//return crest, through, or no-peak
	int peak();

	//return tidal volume
	float tidalVolume();

	//measurement value
	float value;
};

