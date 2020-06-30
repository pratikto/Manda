/*
 Name:		Sensor.ino
 Created:	5/22/2020 10:14:16 PM
 Author:	Pratikto Sulthoni Hidayat
*/
#include "PressureSensor.h"
#include "FlowSensor.h"
#include "functCollection.h"

//frequency clock configuration for sampling triggering and one minutes triggering
#define Fsampling   222
#define oneHz       1

// Uncomment this to output a stream of debug information
// from peak detector.  Use the serial
// plotter to view the graph of these 4 values:
//#define DEBUG

// Configure peak detector behavior://
// Lag, how large is the buffer of filtered samples. Must be an integer value!
#define LAG_pressure             10
// Number of standard deviations above average a value needs to be to be considered a peak.
#define THRESHOLD_pressure        4.0f
// Scale down peak values to this percent influence when storing 
// them back in the filtered values. Should be a value from 0 to 1.0 
// where smaller values mean peaks have less influence.
#define INFLUENCE_pressure         0.1f  

//Initialize Deviation of x axis for Tidal volume calculation
#define XDeviation1 0.0f
#define XDeviation2 0.0f

//Tidal Volume from flow sensor 1 and 2
float tidalVolume = 0.0f;
//Total Volume accumulator
float totalAcc = 0.0f;

//Sensor initialization
PressureSensor Pressure(LAG_pressure, THRESHOLD_pressure, INFLUENCE_pressure);
FlowSensor Flow1(XDeviation1);
FlowSensor Flow2(XDeviation2);

#ifdef DEBUG
    float value;    //temporary value register
    float result;   //temporary result register
#else 
    //Pin configuration
    int pressurePin = A0;
    int flow1Pin = A1;
    int flow2Pin = A2;
    float result;   //temporary result register

    //timing configuration
    bool oneMinute  = false;
    uint8_t seconds = 0;
    bool readSample = false;

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

    //timer0 initialization
    initTimer0(Fsampling);

    //timer1 initialization
    initTimer1(oneHz);
        
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

#ifndef DEBUG

//interrupt service routine for timer 2
//trigger sampling data instruction
ISR(TIMER0_COMPA_vect) {
    readSample = true;
}

//interrupt service routine for timer 1
//generate 1 Hz signal
ISR(TIMER1_COMPA_vect) {
    seconds++;
    //1 minute
    if (seconds == 60) {
        oneMinute = true;

        //measure breath per minute
        Pressure.breathPerMinute(Pressure.breath());

        //reset total breath
        Pressure.breath(0);

        //assign Volume tidal
        tidalVolume = totalAcc;

        //reset accumulator
        totalAcc = 0.0f;

        //reset volume accumulator flow 1 and 2
        Flow1.VolumeAcc(0.0f);
        Flow2.VolumeAcc(0.0f);

        //reset fraction of minute
        seconds = 0;
    }
    else {
        oneMinute = false;
    }
}
#endif

// the loop function runs over and over again until power down or reset
void loop() {
#ifndef DEBUG
    //FSampling clock indicator
    digitalWrite(LED_BUILTIN, oneMinute);

    if (readSample) {

        //Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
        Flow1.value = analogRead(flow1Pin) * (5.0 / 1023.0);
        Flow2.value = analogRead(flow2Pin) * (5.0 / 1023.0);
        Pressure.value = analogRead(pressurePin) * (5.0 / 1023.0);

        //detect pressure sensor
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

        //Detect Flow sensor 1 and 2
        Flow1.detect();
        Flow2.detect();

        //calculate tidal volume
        totalAcc = Flow1.VolumeAcc() + Flow2.VolumeAcc();

        Serial.print(totalAcc);
        Serial.print(",");
        Serial.print(tidalVolume);
        Serial.println(",");

        //turn off sampling trigger
        readSample = false;
    }
#endif
}
