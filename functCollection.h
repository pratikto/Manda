// functCollection.h

#ifndef _FUNCTCOLLECTION_h
#define _FUNCTCOLLECTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//Timer & timer interrupt configuration
#define samplingRate    = 30 //Hz
#define megaFrequency   = 16000000 //Hz
#define prescalerTimer  = 1024

void generate60Hz_Timer1(); 
void generate30Hz_Timer1();
bool generate1Hz_Timer1();

#endif

