/* 
 * This implementation is re-used from my last arduino coursework submission.
 * Patrick Michallet & Daniel Morris, 2019
 * https://github.bath.ac.uk/cm10194-cw1-prm45-dm986/arduino-code/blob/master/game/src/sreg.cpp
*/

#include "sreg.hpp"
#include <Arduino.h>

SReg::SReg(int data_pin, int latch_pin, int clock_pin) {
    this->_data_pin = data_pin;
    this->_latch_pin = latch_pin;
    this->_clock_pin = clock_pin;

    pinMode(data_pin, OUTPUT);
    pinMode(latch_pin, OUTPUT);
    pinMode(clock_pin, OUTPUT);

    this->_state = 0x0;
}

void SReg::Init() {
    digitalWrite(this->_latch_pin, LOW);
    shiftOut(this-> _data_pin, this->_clock_pin, MSBFIRST, this->_state);
    digitalWrite(this->_latch_pin, HIGH);
}

int SReg::GetPinState(int pin) {
    if (pin < 0 || pin > 7) {
        return LOW;
    }
    
    if (bitRead(this->_state, pin)) {
        return HIGH;
    }
    else {
        return LOW;
    }
}

void SReg::DigitalWrite(int pin, int value) {
    if (pin < 0 || pin > 7) {
        return;
    }

    bitWrite(this->_state, pin, value);

    digitalWrite(this->_latch_pin, LOW);

    shiftOut(this->_data_pin, this->_clock_pin, MSBFIRST, this->_state);
    
    digitalWrite(this->_latch_pin, HIGH);
}
