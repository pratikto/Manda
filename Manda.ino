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
//#define DEBUG

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
#define INFLUENCE_pressure         0.1f   

//Sensor initialization
PressureSensor Pressure(LAG_pressure, THRESHOLD_pressure, INFLUENCE_pressure);
FlowSensor Flow(LAG_flow, THRESHOLD_flow, INFLUENCE_flow);

#ifdef DEBUG
    float value;    //temporary value register
    float result;   //temporary result register
#else 
    //Pin configuration
    int pressurePin = A0;
    int flowPin = A1;
    float result;   //temporary result register

    //timing configuration
    bool oneMinute          = false;
    uint8_t FracOneMinute   = 0;
    bool readSample         = false;


    //interrupt service routine for timer 1
    //generate 1 Hz signal
    ISR(TIMER1_COMPA_vect) {
        FracOneMinute++;
        if (FracOneMinute == 60) {
            oneMinute = true;
            FracOneMinute = 0;
        }
        else {
            oneMinute = false;
        }
    }    
    
    //interrupt service routine for timer 2
    //trigger sampling data instruction
    ISR(TIMER2_COMPA_vect) {
        readSample = true;
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
    generate1Hz_Timer1();

    //timer2 initialization
    generate222Hz_Timer2;
    
    //allow interrupts
    sei();

#else
    //Do Absolutely Nothing until something is received over the serial port
    while (!Serial.available()) {     
    }

    Serial.println("Pressure");
    for (unsigned int j = 0; j < 1358; j++) {
        value = pgm_read_float(&pressureOutput[j]);
        result = 5 * Pressure.detect(value);
        //print to Serial monitor. 
        //then copy it to csv file for further analysis
        Serial.print(result);
        Serial.print(",");
        Serial.print(Pressure.PPeak()); 
        Serial.print(",");
        Serial.print(Pressure.PAverage()); 
        Serial.print(",");
        Serial.print(Pressure.PPEP()); 
        Serial.print(",");
        Serial.print(Pressure.breathPerMinute()); 
        Serial.println(",");
    }

    Serial.println("Flow");
    for (unsigned int i = 0; i < 6364; i++) {
        value = pgm_read_float(&flowOutput[i]);
        result = 5 * Flow.detect(value);
        //print to Serial monitor. 
        //then copy it to csv file for further analysis
        Serial.print(result); 
        Serial.print(",");
        Serial.print(Pressure.breathPerMinute());
        Serial.println(",");
    }
#endif
}

// the loop function runs over and over again until power down or reset
void loop() {
#ifndef DEBUG
    //FSampling clock indicator
    digitalWrite(LED_BUILTIN, oneMinute);

    if (readSample) {
        //turn off sampling trigger
        readSample = false;

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
        result = Pressure.detect(); 

        Serial.print(result);
        Serial.print(",");
        Serial.print(Pressure.PPeak());
        Serial.print(",");
        Serial.print(Pressure.PAverage());
        Serial.print(",");
        Serial.print(Pressure.PPEP());
        Serial.print(",");
        Serial.print(Pressure.breathPerMinute());
        Serial.println(",");

        result = Flow.detect();

        Serial.print(result);
        Serial.print(",");
        Serial.print(Pressure.breathPerMinute());
        Serial.println(",");
    }
#endif
}
