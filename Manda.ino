/*
 Name:		Sensor.ino
 Created:	5/22/2020 10:14:16 PM
 Author:	Pratikto Sulthoni Hidayat
*/
#include "sensor.h"
#include "functCollection.h"
#include "PeakDetector.h"

//Pin configuration
int pressurePin = A0;
int flowPin = A1;

//30 Hz square wave 
bool clock30Hz = 0;

// Configure peak detector behavior:

// Lag, how large is the buffer of filtered samples. Must be an integer value!
#define LAG_flow                 30
#define LAG_pressure             30

// Number of standard deviations above average a value needs to be to be considered a peak.
#define THRESHOLD_flow            20.0
#define THRESHOLD_pressure        20.0

// Scale down peak values to this percent influence when storing 
// them back in the filtered values. Should be a value from 0 to 1.0 
//where smaller values mean peaks have less influence.
#define INFLUENCE_flow             0.1   
#define INFLUENCE_pressure         0.1   

//Sensor initialization
Sensor Pressure(LAG_pressure, THRESHOLD_pressure, INFLUENCE_pressure);
Sensor Flow(LAG_flow, THRESHOLD_flow, INFLUENCE_flow);

// the setup function runs once when you press reset or power the board
void setup() {
    //stop interrupts
    cli();

    // initialize digital pin LED_BUILTIN as FSampling clock indicator
    pinMode(LED_BUILTIN, OUTPUT);
    
    //timer1 initialization
    generate60Hz_Timer1();
    
    //allow interrupts
    sei();
}

//interrupt service routine for timer 1
//generate 30 Hz square wave clock
ISR(TIMER1_COMPA_vect) {
    clock30Hz = !clock30Hz;
}


// the loop function runs over and over again until power down or reset
void loop() {
    if (clock30Hz) {
        //FSampling clock indicator
        digitalWrite(LED_BUILTIN, clock30Hz);

        // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
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
        //Flow.detect();
        //Pressure.detect();

        //write result to serial monitor
        Serial.print("Flow PPeak : "); Serial.print(Flow.PPeak());
        Serial.print("\tPressure PPeak : "); Serial.print(Pressure.PPeak());
        Serial.print("\tFlow PAvg : "); Serial.print(Flow.PAverage());
        Serial.print("\tPressure PAvg : "); Serial.print(Pressure.PAverage());
        Serial.print("\tFlow PEEP : "); Serial.print(Flow.PPEP());
        Serial.print("\tPressure PEEP : "); Serial.print(Pressure.PPEP());
        Serial.print("\tFlow BPM : "); Serial.print(Flow.PPEP());
        Serial.print("\tPressure BPM : "); Serial.print(Pressure.PPEP());
        Serial.print("\tFlow tidal : "); Serial.print(Flow.tidalVolume());
        Serial.print("\tPressure tidal : "); Serial.print(Pressure.tidalVolume());
        Serial.println();
        
    }
}
