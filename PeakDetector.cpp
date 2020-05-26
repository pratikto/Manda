// 
// 
// 

#include "PeakDetector.h"

PeakDetector::PeakDetector(const int lag = 5, const float threshold = 3.5, const float influence = 0.5) :
    _lag(lag), _threshold(threshold), _influence(influence), _avg(0.0), _std(0.0), _primed(false), _index(0)
{
    // Allocate memory for last samples (used during averaging) and set them all to zero.
    _filtered = new float[lag];
    for (int i = 0; i < lag; ++i) {
        _filtered[i] = 0.0;
    }
}

PeakDetector::~PeakDetector() {
    // Deallocate memory for samples.
    if (_filtered != NULL) {
        delete[] _filtered;
    }
}

int PeakDetector::detect(float sample) {
    // Detect if the provided sample is a positive or negative peak.
   // Will return 0 if no peak detected, 1 if a positive peak and -1
   // if a negative peak.
    int result = NOPEAK;
    // Fill up filtered samples if not yet primed with enough available samples.
    if (_primed && (abs(sample - _avg) > (_threshold * _std))) {
        // Detected a peak!
        // Determine type of peak, positive or negative.
        if (sample > _avg) {
            result = CREST;
        }
        else {
            result = THROUGH;
        }
        // Save this sample but scaled down based on influence.
        _filtered[_index] = (_influence * sample) + ((1.0 - _influence) * _filtered[_previousIndex()]);
    }
    else {
        // Did not detect a peak, or not yet primed with enough samples.
        // Just record this sample and move on.
        _filtered[_index] = sample;
    }
    // Increment index of next filtered sample.
    _incrementIndex();
    // When primed update the average and standard deviation of the most recent
    // filtered values.
    if (_primed) {
        // Compute mean of filtered values.
        _avg = 0.0;
        for (int i = 0; i < _lag; ++i) {
            _avg += _filtered[i];
        }
        _avg = _avg / float(_lag);
        // Compute standard deviation of filtered values.
        _std = 0.0;
        for (int i = 0; i < _lag; ++i) {
            _std += pow(_filtered[i] - _avg, 2.0);
        }
        _std = sqrt(_std / float(_lag));
    }
    return result;
}

int PeakDetector::detect() {
    return detect(value);
}

float PeakDetector::getAvg() {
    // Return the current signal average, useful for debugging.
    return _avg;
}

float PeakDetector::getStd() {
    // Return the current signal standard deviation, useful for debugging.
    return _std;
}

void PeakDetector::_incrementIndex() {
    // Increment the index of the current sample.
    _index += 1;
    if (_index >= _lag) {
        // Loop back to start of sample buffer when full, but be sure to note
        // when this happens to indicate we are primed with enough samples.
        _index = 0;
        _primed = true;
    }
}

int PeakDetector::_previousIndex() {
    // Find the index of the last sample.
    int result = _index - 1;
    if (result < 0) {
        result = _lag - 1;
    }
    return result;
}