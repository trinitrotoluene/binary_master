#include <Arduino.h>
#include "numchain.hpp"

// Populate a number chain with a provided target number, and min/max size for other generated numbers.
NumChain::NumChain(int target, int min, int max) {
    this->_target = target;
    this->_min = min;
    this->_max = max;

    this->FillChain();
}

int NumChain::Next() {
    // This read will be OOB
    if (this->_pos >= CHAIN_SIZE) {
        // Reset our position in the chain
        this->_pos = 0;
        // Repopulate the chain with a fresh sequence of numbers
        this->FillChain();
    }

    // Get the next number and advance one position in the chain
    auto num = this->_buffer[_pos];
    _pos++;

    return num;
}

void NumChain::FillChain() {
    // Calculate the index at which the target will be inserted
    auto indexToInsertAt = random(0, CHAIN_SIZE);
    // Loop over every item in the buffer
    for (int i = 0; i < CHAIN_SIZE; i++)
    {
        // Insert target at this index
        if (i == indexToInsertAt) {
            this->_buffer[i] = _target;
        }
        // Insert a random number at this index
        else {
            int randNum = _target;
            while (randNum == _target) {
                // Generate numbers until we get one that isn't our target number!
                randNum = random(_min, _max);
            }
            // Insert the non-target number to our buffer at this index.
            this->_buffer[i] = randNum;
        }
    }
}