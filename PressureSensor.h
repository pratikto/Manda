#pragma once
#include "PeakDetector.h"

#if defined(ARDUINO) && ARDUINO >= 100
    #include "arduino.h"
#else
    #include "WProgram.h"
#endif

class PressureSensor :
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
	//previous peak indicator
	int _prevPeak;
	//sum of value in one periode
	float _sumValue;
	//value counter in one periode 
	int _countValue;
	//wave periode
	float _periode;
	//total breath
	uint8_t _breath;
	//breath per minute value
	uint8_t _breathPerMinute;
	//previous measurement value
	float _prevValue;



public:
	//constructor
	PressureSensor();

	//constructor
	PressureSensor(const int lag, const float threshold, const float influence);

	//constructor
	PressureSensor(const float xDev, const int lag, const float threshold, const float influence);

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

	//return breath per minute value
	float breathPerMinute();

	//set breath per minute value
	void breathPerMinute(uint8_t value);

	//return total breath
	uint8_t breath();

	//set breath value
	void breath(uint8_t value);

	//measurement value
	float value;
};

