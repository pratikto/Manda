#include "FlowSensor.h"

//constructor
FlowSensor::FlowSensor() {
	//Volume Accumulator
	_VolumeAcc = 0.0f;
	//axis deviation
	_xDev = 0.0f;
	//previous measurement value
	_prevValue = 0.0f;
}

//constructor
FlowSensor::FlowSensor(const float xDev) {
	//Volume Accumulator
	_VolumeAcc = 0.0f;
	//axis deviation
	_xDev = xDev;
	//previous measurement value
	_prevValue = 0.0f;
}

// Detect if the provided sample is a positive or negative peak.
// Will return 0 if no peak detected, 1 if a positive peak and -1
// if a negative peak.
float FlowSensor::detect(float value) {

	//calculate tidal Volume
	//tidal Volume = sum of (value *  T_sampling) = sum of (value / f_sampling) 
	_VolumeAcc = _VolumeAcc + ((value - _xDev) / 222.0f);

	//return current peak indicator
	return _VolumeAcc;
}

// Detect if the provided sample is a positive or negative peak.
// Will return 0 if no peak detected, 1 if a positive peak and -1
// if a negative peak.
float FlowSensor::detect() {
	return detect(value);
}

//return volume accumulator
float FlowSensor::VolumeAcc() {
	return _VolumeAcc;
}

//set volume accumulator
void FlowSensor::VolumeAcc(float VolumeAcc) {
	_VolumeAcc = VolumeAcc;
}