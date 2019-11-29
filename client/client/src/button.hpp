#pragma once
/* 
 * This implementation is re-used from my last arduino coursework submission.
 * Patrick Michallet & Daniel Morris, 2019
 * https://github.bath.ac.uk/cm10194-cw1-prm45-dm986/arduino-code/blob/master/game/src/button.hpp
*/

#include <Arduino.h>

enum ButtonState {
    Pressed, Held, Released, Neutral,
};

class Button {
private:
    int pin;
    ButtonState state;
public:
    void Bind(int pin);
    void UpdateState();
    ButtonState GetState() const;
};
