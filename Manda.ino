/*
 Name:		Sensor.ino
 Created:	5/22/2020 10:14:16 PM
 Author:	Pratikto Sulthoni Hidayat
*/
#include "PressureSensor.h"
#include "FlowSensor.h"
#include "functCollection.h"
//#include "PeakDetector.h"

// Uncomment this to output a stream of debug information
// from peak detector.  Use the serial
// plotter to view the graph of these 4 values:
#define DEBUG

// Configure peak detector behavior:

// Lag, how large is the buffer of filtered samples. Must be an integer value!
#define LAG_flow                 100
#define LAG_pressure             10

// Number of standard deviations above average a value needs to be to be considered a peak.
#define THRESHOLD_flow            3.8f
#define THRESHOLD_pressure        4.0f

// Scale down peak values to this percent influence when storing 
// them back in the filtered values. Should be a value from 0 to 1.0 
//where smaller values mean peaks have less influence.
#define INFLUENCE_flow             0.01f   
#define INFLUENCE_pressure         0.1   

#ifdef DEBUG
    //Sensor initialization
    PeakDetector Pressure(LAG_pressure, THRESHOLD_pressure, INFLUENCE_pressure);
    PeakDetector Flow(LAG_flow, THRESHOLD_flow, INFLUENCE_flow);
    float value;    //temporary value register
    float result;   //temporary result register
#else 
    //Pin configuration
    int pressurePin = A0;
    int flowPin = A1;

    //Sensor initialization
    PressureSensor Pressure(LAG_pressure, THRESHOLD_pressure, INFLUENCE_pressure);
    FlowSensor Flow(LAG_flow, THRESHOLD_flow, INFLUENCE_flow);

    //30 Hz square wave 
    bool clock30Hz = 0;

    //interrupt service routine for timer 1
    //generate 30 Hz square wave clock
    ISR(TIMER1_COMPA_vect) {
        clock30Hz = !clock30Hz;
    }
#endif

// the setup function runs once when you press reset or power the board
void setup() {
    // Initialize serial output for debugging and plotting.
    Serial.begin(2000000);
#ifndef DEBUG
    //stop interrupts
    cli();

    // initialize digital pin LED_BUILTIN as FSampling clock indicator
    pinMode(LED_BUILTIN, OUTPUT);
    
    //timer1 initialization
    generate60Hz_Timer1();
    
    //allow interrupts
    sei();

#else
    for (unsigned int i = 0; i < 6364; i++) {
        //Flow.value = pgm_read_float(&flowOutput[i]);
        //Flow.detect();
        value = pgm_read_float(&flowOutput[i]);
        Flow.detect(value);
        //Serial.print(i); Serial.print(", "); Serial.print(Flow.value); Serial.println(",");
        Serial.print(i); Serial.print(", "); Serial.print(value); Serial.println(",");

    }
    for (unsigned int j = 0; j < 1358; j++) {
        //Pressure.value = pgm_read_float(&pressureOutput[j]);
        value = pgm_read_float(&pressureOutput[j]);
        Pressure.detect(value);
        Serial.print(j); Serial.print(", "); Serial.print(value); Serial.println(",");
    }
#endif
}

// the loop function runs over and over again until power down or reset
void loop() {
#ifndef DEBUG
    if (clock30Hz) {
        //FSampling clock indicator
        digitalWrite(LED_BUILTIN, clock30Hz);

        //Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
        Flow.value = analogRead(flowPin) * (5.0 / 1023.0);
        Pressure.value = analogRead(pressurePin) * (5.0 / 1023.0);

        //detect crest, throuh, and no peak.
        //
        //if result is 'CREST', then 
        //  (1)the voltage measurement is stored in PPeak
        //  (2)calculate the wave periode
        //  (3)calculate breath per minute (BPM)
        //  (4)calculate wave amplitude average each periode (PAverage)
        //  (5)calculate tidal volume
        //if result is 'THROUGH', then 
        //  (6)the voltage measurement is stored in PPEP
        //if result is 'NOPEAK', then
        //  (7)increment countValue & sumValue
        //  (8)calculate volumeAcc
        Flow.detect();
        Pressure.detect();

        //write result to serial monitor
        //Serial.print("Flow PPeak : "); Serial.print(Flow.PPeak());
        //Serial.print("\tPressure PPeak : "); Serial.print(Pressure.PPeak());
        //Serial.print("\tFlow PAvg : "); Serial.print(Flow.PAverage());
        //Serial.print("\tPressure PAvg : "); Serial.print(Pressure.PAverage());
        //Serial.print("\tFlow PEEP : "); Serial.print(Flow.PPEP());
        //Serial.print("\tPressure PEEP : "); Serial.print(Pressure.PPEP());
        //Serial.print("\tFlow BPM : "); Serial.print(Flow.PPEP());
        //Serial.print("\tPressure BPM : "); Serial.print(Pressure.PPEP());
        //Serial.print("\tFlow tidal : "); Serial.print(Flow.tidalVolume());
        //Serial.println();
    }
#endif
}
