#include "PressureSensor.h"

PressureSensor::PressureSensor() :
	PeakDetector(_lag = 5, _threshold = 3.5, _influence = 0.5)
{
	_breathPerMinute = 0.0;
	_breath = 0;
	_countValue = 0;
	_sumValue = 0.0;
	_periode = 0.0;
	_PAverage = 0.0;
	_PPEP = 0.0;
	_PPeak = 0.0;
	_peak = 0;
}

PressureSensor::PressureSensor(const int lag, const float threshold, const float influence) :
	PeakDetector(_lag = lag, _threshold = threshold, _influence = influence)
{
	_breathPerMinute = 0.0;
	_breath = 0;
	_countValue = 0;
	_sumValue = 0.0;
	_periode = 0.0;
	_PAverage = 0.0;
	_PPEP = 0.0;
	_PPeak = 0.0;
	_peak = 0;
}

//constructor
PressureSensor::PressureSensor(const float xDev, const int lag, const float threshold, const float influence) :
	PeakDetector(_lag = lag, _threshold = threshold, _influence = influence)
{
	_breathPerMinute = 0.0;
	_breath = 0;
	_countValue = 0;
	_sumValue = 0.0;
	_periode = 0.0;
	_PAverage = 0.0;
	_PPEP = 0.0;
	_PPeak = 0.0;
	_peak = 0;
}

// Detect if the provided sample is a positive or negative peak.
// Will return 0 if no peak detected, 1 if a positive peak and -1
// if a negative peak.
int PressureSensor::detect(float sample) {
	value = sample;
	//call detect() function from its base class, PeakDetector.
	_peak = PeakDetector::detect(value);

	//crest is detected
	if ((_prevPeak == CREST) && (_peak == NOPEAK)) {
		//assign _PPeak if crest is detected
		_PPeak = _prevValue;

		//calculate T (wave Periode). T = 1/f_sampling * _countValue;
		_periode = (float)_countValue / 30.0f;

		//calculate breath per minute
		//_breathPerMinute = 60.0f / _periode;

		//increment breath
		_breath++;

		//calculate _PAverage every time a crest is detected
		_PAverage = _sumValue / _countValue;

		//reset _sumValue & _countValue to zero
		_sumValue = 0.0;
		_countValue = 0;
	}
	//through is detected
	else if ((_prevPeak == THROUGH) && (_peak == NOPEAK)) {
		//assign _PPEP if througn is detected
		_PPEP = _prevValue;
	}
	//nopeak is detected
	else {

	}

	//update sumValue & _countValue
	_sumValue = _sumValue + value;
	_countValue++;

	//assign previoud register to current register
	_prevPeak = _peak;
	_prevValue = value;

	//return current peak indicator
	return _peak;
}

// Detect if the provided sample is a positive or negative peak.
// Will return 0 if no peak detected, 1 if a positive peak and -1
// if a negative peak.
int PressureSensor::detect() {
	return detect(value);
}

//return _PPeak value
float PressureSensor::PPeak() {
	return _PPeak;
}

//return PMean value
float PressureSensor::PAverage() {
	return _PAverage;
}

//return PPEP value
float PressureSensor::PPEP() {
	return _PPEP;
}

//return crest, through, or no-peak
int PressureSensor::peak() {
	return _peak;
}

//return breath per minute value
float PressureSensor::breathPerMinute() {
	return _breathPerMinute;
}

//set breath per minute value
void PressureSensor::breathPerMinute(uint8_t value) {
	_breathPerMinute = value;
}

//return total breath
uint8_t PressureSensor::breath() {
	return _breath;
}

//set breath value
void PressureSensor::breath(uint8_t value) {
	_breath = value;
}