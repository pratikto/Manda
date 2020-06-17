#include "FlowSensor.h"

FlowSensor::FlowSensor() :
	PeakDetector(_lag = 5, _threshold = 3.5, _influence = 0.5)
{
	_tidalVolume = 0.0;
	_xDev = 0.0;
	_VolumeAcc = 0.0;
	_peak = 0;
}

FlowSensor::FlowSensor(const int lag, const float threshold, const float influence) :
	PeakDetector(_lag = lag, _threshold = threshold, _influence = influence)
{
	_tidalVolume = 0.0;
	_xDev = 0.0;
	_VolumeAcc = 0.0;
	_peak = 0;
}

//constructor
FlowSensor::FlowSensor(const float xDev, const int lag, const float threshold, const float influence) :
	PeakDetector(_lag = lag, _threshold = threshold, _influence = influence)
{
	_tidalVolume = 0.0;
	_xDev = xDev;
	_VolumeAcc = 0.0;
	_peak = 0;
}


// Detect if the provided sample is a positive or negative peak.
// Will return 0 if no peak detected, 1 if a positive peak and -1
// if a negative peak.
int FlowSensor::detect(float sample) {
	value = sample;
	//call detect() function from its base class, PeakDetector.
	_peak = PeakDetector::detect(value);

	//crest is detected
	if ((_prevPeak == CREST) && (_peak == NOPEAK)) {

		//assign volume accumulator to tidal volume, then reset the volume accumulator
		_tidalVolume = _VolumeAcc;
		_VolumeAcc = 0.0;

		//reset _tidalVolume
		_tidalVolume = 0.0;
	}
	//through is detected
	else if ((_prevPeak == THROUGH) && (_peak == NOPEAK)) {

	}
	//nopeak is detected
	else {

	}

	//calculate tidal Volume
	//tidal Volume = sum of (value *  T_sampling) = sum of (value / f_sampling) 
	_VolumeAcc = _VolumeAcc + (abs(value - _xDev) / 30.0f);

	//assign previoud register to current register
	_prevPeak = _peak;
	_prevValue = value;

	//return current peak indicator
	return _peak;
}

// Detect if the provided sample is a positive or negative peak.
// Will return 0 if no peak detected, 1 if a positive peak and -1
// if a negative peak.
int FlowSensor::detect() {
	return detect(value);
}

// Detect if the provided sample is a positive or negative peak.
// Will return 0 if no peak detected, 1 if a positive peak and -1
// if a negative peak.
//int Sensor::detect() {
//}

//return crest, through, or no-peak
int FlowSensor::peak() {
	return _peak;
}

//return tidal volume
float FlowSensor::tidalVolume() {
	return _tidalVolume;
}