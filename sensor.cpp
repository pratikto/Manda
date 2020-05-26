// 
// 
// 

#include "sensor.h"

Sensor::Sensor() : PeakDetector(_lag = 5, _threshold = 3.5, _influence = 0.5) {

}

Sensor::Sensor(const int lag, const float threshold, const float influence) : 
	PeakDetector(_lag = lag, _threshold = threshold, _influence = influence)
{
}

//read sensor and doing calculation
bool Sensor::read(float tempValue) {
	detect(tempValue);
	if (_peak = CREST) {
		_PPeak = tempValue;
	}
	else if (_peak = THROUGH) {
		_PPEP = tempValue;
	}
	return _peak;
}

//read sensor and doing calculation
bool Sensor::read() {
	detect(value);
	if (_peak = CREST) {
		_PPeak = value;
	}
	else if (_peak = THROUGH) {
		_PPEP = value;
	}
	return _peak;
}

// Detect if the provided sample is a positive or negative peak.
// Will return 0 if no peak detected, 1 if a positive peak and -1
// if a negative peak.
int Sensor::detect(float sample) {
	PeakDetector::detect( sample);
	if (_peak = CREST) {
		_PPeak = value;
	}
	else if (_peak = THROUGH) {
		_PPEP = value;
	}
	return _peak;
}

// Detect if the provided sample is a positive or negative peak.
// Will return 0 if no peak detected, 1 if a positive peak and -1
// if a negative peak.
int Sensor::detect() {
	PeakDetector::detect();
	if (_peak = CREST) {
		_PPeak = value;
	}
	else if (_peak = THROUGH) {
		_PPEP = value;
	}
	return _peak;
}

//return _PPeak value
float Sensor::PPeak() {
	return _PPeak;
}

//return PMean value
float Sensor::PAverage() {
	return _PAverage;
}

//return PPEP value
float Sensor::PPEP() {
	return _PPEP;
}


