#include <Arduino.h>
#include "display.hpp"
#include "sreg.hpp"

// Construct a new display wrapping a shift register's output.
Display::Display(SReg* sreg) {
    this->_sreg = sreg;
    this->_size = 8;
    this->_currentNumber = -1;
}

// Output a number to the display in binary form.
void Display::PrintBinary(int number) {
    // Copy by value so we can use it in the algorithm below.
    int num = number;
    // Loop over every LED on the display, and every bit in the number, until we run out of one of them.
    for (int i = 0; i < this->_size; i++) {
        // Set the state to HIGH if the bit is set, LOW if it is not.
        this->_sreg->DigitalWrite(i, num & 1);
        // Shift the number one bit to the right, so we can test against the next one.
        num >>= 1;
    }
    // Update our currently displayed number.
    this->_currentNumber = number;
}
