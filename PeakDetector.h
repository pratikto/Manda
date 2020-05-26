// PeakDetector.h

 // Signal peak detector using smoothed z-score algorithm.
 // Detects when a continuous signal has a significant peak in values.  Based on
 // algorithm from the answer here:
 //   https://stackoverflow.com/questions/22583391/peak-signal-detection-in-realtime-timeseries-data/22640362#22640362
 // Author: Tony DiCola
 // License: MIT License (https://opensource.org/licenses/MIT)
 // Usage:
 // - Create an instance of the PeakDetector class and configure its lag, threshold,
 //   and influence.  These likely need to be adjust to fit your dataset.  See the
 //   Stack Overflow question above for more details on their meaning.
 // - Continually call detect and feed it a new sample value.  Detect will return 0
 //   if no peak was detected, 1 if a positive peak was detected and -1 if a negative
 //   peak was detected.
#ifndef _PEAKDETECTOR_h
#define _PEAKDETECTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define CREST 1
#define THROUGH -1
#define NOPEAK 0

class PeakDetector {
public:
    PeakDetector(const int lag = 5, const float threshold = 3.5, const float influence = 0.5);
    
    ~PeakDetector();
    
    // Detect if the provided sample is a positive or negative peak.
    // Will return 0 if no peak detected, 1 if a positive peak and -1
    // if a negative peak.
    virtual int detect(float sample);

    // Detect if the provided sample is a positive or negative peak.
    // Will return 0 if no peak detected, 1 if a positive peak and -1
    // if a negative peak.
    virtual int detect();
    
    // Return the current signal average, useful for debugging.
    float getAvg();
    
    // Return the current signal standard deviation, useful for debugging.
    float getStd();

    //measurement value
    float value;

protected:
    int _lag;
    float _threshold;
    float _influence;
    float* _filtered;
    float _avg;
    float _std;
    bool _primed;
    int _index;


    // Increment the index of the current sample.
    void _incrementIndex();
    // Find the index of the last sample.
    int _previousIndex();
};

#endif