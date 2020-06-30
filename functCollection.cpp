// 
// 
// 

#include "functCollection.h"

void initTimer0(int freq) {
    //set timer0 interrupt at 222Hz
    TCCR0A = 0;// set entire TCCR0A register to 0
    TCCR0B = 0;// same for TCCR0B
    TCNT0 = 0;//initialize counter value to 0
    // set compare match register for 2khz increments
    OCR0A = clock / (freq * 1024) - 1;//must be <256
    // turn on CTC mode
    TCCR0A |= (1 << WGM01);
    // Set CS01 and CS00 bits for 1024 prescaler
    TCCR0B |= (1 << CS02) | (1 << CS00);
    // enable timer compare interrupt
    TIMSK0 |= (1 << OCIE0A);
}

void initTimer1(int freq) {
    //set timer1 interrupt at 1 Hz
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1 = 0;//initialize counter value to 0
    // set compare match register for 1Hz increments
    OCR1A = clock / (freq * 1024) - 1;// must be < 65536
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
}