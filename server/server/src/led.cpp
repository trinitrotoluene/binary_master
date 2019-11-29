#include <Arduino.h>
#include "led.hpp"

// Bind an LED to a provided pin.
void Led::Bind(uint8_t pin) {
    // Make sure the mode of the bound pin is set correctly.
    pinMode(pin, OUTPUT);
    this->_pin = pin;
}

// Gets whether this LED is lit.
bool Led::IsLit() {
    return this->_state == OUTPUT;
}

// Toggle the current state of the LED.
void Led::Toggle() {
    if (this->_state == HIGH) {
        this->_state = LOW;
        digitalWrite(this->_pin, LOW);
    }
    else {
        this->_state = HIGH;
        digitalWrite(this->_pin, HIGH);
    }
}

void Led::SetState(uint8_t state) {
    this->_state = state;
    digitalWrite(this->_pin, state);
}