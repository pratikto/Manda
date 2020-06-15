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
	//crest amplitudo. this value will be updated every time a new crest is detected
	float _PPeak;
	//wave average value. this value will be updated each cycle
	float _PAverage;
	//trough amplitudo. this value will be updated every time a new trough is detected
	float _PPEP;
	//peak indicator
	int _peak;
	//sum of value in one periode
	float _sumValue;
	//value counter in one periode 
	int _countValue;
	//wave periode
	float _periode;
	//breath per minute
	float _breathPerMinute;
	//absolute area of tidal volume
	float _tidalVolume;
	float _VolumeAcc;
	//axis deviation
	float _xDev;



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

	//return _PPeak value
	float PPeak();

	//return PMean value
	float PAverage();

	//return PPEP value
	float PPEP();

	//return crest, through, or no-peak
	int peak();

	//return tidal volume
	float tidalVolume();

	//measurement value
	float value;
};

