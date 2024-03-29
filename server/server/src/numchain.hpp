#pragma once

// Defines the length of the chain.
const int CHAIN_SIZE = 5;

class NumChain {
    public:
    NumChain();
    NumChain(int target, int min, int max);
    int Next();
    int GetCurrentNumber();
    private:
    int _pos = 0;
    int _target, _min, _max;
    int _buffer[CHAIN_SIZE];
    void FillChain();
};
