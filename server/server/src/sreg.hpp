#pragma once
/* 
 * This implementation is re-used from my last arduino coursework submission.
 * Patrick Michallet & Daniel Morris, 2019
 * https://github.bath.ac.uk/cm10194-cw1-prm45-dm986/arduino-code/blob/master/game/src/sreg.hpp
*/

class SReg {
    public:
        SReg(int, int, int);
        void Init();
        void DigitalWrite(int, int);
        int GetPinState(int);
    private:
        int _data_pin, _latch_pin, _clock_pin;
        char _state;
};
