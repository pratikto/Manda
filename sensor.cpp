// 
// 
// 

#include "sensor.h"

Sensor::Sensor() : 
	PeakDetector(_lag = 5, _threshold = 3.5, _influence = 0.5) 
{
	_tidalVolume = 0.0;
	_breathPerMinute = 0.0;
	_xDev = 0.0;
	_countValue = 0;
	_sumValue = 0.0;
	_periode = 0.0;
	_PAverage = 0.0;
	_PPEP = 0.0;
	_VolumeAcc = 0.0;
	_PPeak = 0.0;
	_peak = 0;
}

Sensor::Sensor(const int lag, const float threshold, const float influence) : 
	PeakDetector(_lag = lag, _threshold = threshold, _influence = influence)
{
	_tidalVolume = 0.0;
	_breathPerMinute = 0.0;
	_xDev = 0.0;
	_countValue = 0;
	_sumValue = 0.0;
	_periode = 0.0;
	_PAverage = 0.0;
	_PPEP = 0.0;
	_VolumeAcc = 0.0;
	_PPeak = 0.0;
	_peak = 0;
}

//constructor
Sensor::Sensor(const float xDev, const int lag, const float threshold, const float influence) :
	PeakDetector(_lag = lag, _threshold = threshold, _influence = influence)
{
	_tidalVolume = 0.0;
	_breathPerMinute = 0.0;
	_xDev = xDev;
	_countValue = 0;
	_sumValue = 0.0;
	_periode = 0.0;
	_PAverage = 0.0;
	_PPEP = 0.0;
	_VolumeAcc = 0.0;
	_PPeak = 0.0;
	_peak = 0;
}

//read sensor and doing calculation
bool Sensor::read(float tempValue) {
	detect(tempValue);
	if (_peak == CREST) {
		_PPeak = tempValue;
	}
	else if (_peak == THROUGH) {
		_PPEP = tempValue;
	}
	return _peak;
}

//read sensor and doing calculation
//bool Sensor::read() {
//	detect(value);
//	if (_peak == CREST) {
//		_PPeak = value;
//	}
//	else if (_peak == THROUGH) {
//		_PPEP = value;
//	}
//	return _peak;
//}

// Detect if the provided sample is a positive or negative peak.
// Will return 0 if no peak detected, 1 if a positive peak and -1
// if a negative peak.
int Sensor::detect(float sample) {
	//call detect() function from its base class, PeakDetector.
	PeakDetector::detect( sample);

	//update sumValue & _countValue
	_sumValue = _sumValue + sample;
	_countValue++;

	//calculate tidal Volume
	//tidal Volume = sum of (value *  T_sampling) = sum of (value / f_sampling) 
	_VolumeAcc = _VolumeAcc + ( abs(sample - _xDev) / 30.0f );

	//crest is detected
	if (_peak == CREST) {
		//assign _PPeak if crest is detected
		_PPeak = sample;

		//assign volume accumulator to tidal volume, then reset the volume accumulator
		_tidalVolume = _VolumeAcc;
		_VolumeAcc = 0.0;
		
		//calculate T (wave Periode). T = 1/f_sampling * _countValue;
		_periode = (float) _countValue / 30.0f;

		//calculate breath per minute
		_breathPerMinute = 60.0f / _periode;

		//calculate _PAverage every time a crest is detected
		_PAverage = _sumValue / _countValue;
		
		//reset _tidalVolume, _sumValue & _countValue to zero
		_tidalVolume = 0.0;
		_sumValue = 0.0;
		_countValue = 0;
	}
	//through is detected
	else if (_peak == THROUGH) {
		//assign _PPEP if througn is detected
		_PPEP = sample;
	}
	//nopeak is detected
	else {

	}

	return _peak;
}

// Detect if the provided sample is a positive or negative peak.
// Will return 0 if no peak detected, 1 if a positive peak and -1
// if a negative peak.
//int Sensor::detect() {
//}

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

//return crest, through, or no-peak
int Sensor::peak() {
	return _peak;
}

//return breath per minute value
float Sensor::breathPerMinute() {
	return _breathPerMinute;
}

//return tidal volume
float Sensor::tidalVolume() {
	return _tidalVolume;
}