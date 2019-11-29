#pragma once

#include "led.hpp"
#include "sreg.hpp"

class Display {
    public:
    Display(SReg* sreg);
    void PrintBinary(int decimal);
    int GetCurrentNumber();
    private:
    SReg* _sreg;
    byte _size;
    int _currentNumber;
};
