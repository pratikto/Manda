// 
// 
// 

#include "functCollection.h"

void generate222Hz_Timer2() {
    //set timer2 interrupt at 222 Hz
    TCCR2A = 0;// set entire TCCR2A register to 0
    TCCR2B = 0;// same for TCCR2B
    TCNT2 = 0;//initialize counter value to 0
    // set compare match register for 222 Hz increments
    OCR2A = 249;// = (16*10^6) / (222*8) - 1 (must be <256)
    // turn on CTC mode
    TCCR2A |= (1 << WGM21);
    // Set CS21 bit for 8 prescaler
    TCCR2B |= (1 << CS21);
    // enable timer compare interrupt
    TIMSK2 |= (1 << OCIE2A);
}

void generate1Hz_Timer1() {
    //set timer1 interrupt at 1 Hz
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1 = 0;//initialize counter value to 0
    // set compare match register for 1Hz increments
    OCR1A = 16000000 / (1 * 1024) - 1;// (must be < 65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
}