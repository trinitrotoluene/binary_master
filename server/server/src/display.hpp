#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "led.hpp"
class Display {
    public:
    Display(Led* leds, byte size);
    void PrintBinary(int decimal);
    int GetCurrentNumber();
    private:
    Led* _leds;
    byte _size;
    int _currentNumber;
};

#endif