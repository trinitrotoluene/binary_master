/* 
 * This implementation is re-used from my last arduino coursework submission.
 * Patrick Michallet & Daniel Morris, 2019
 * https://github.bath.ac.uk/cm10194-cw1-prm45-dm986/arduino-code/blob/master/game/src/button.cpp
*/

#include "button.hpp";

void Button::Bind(int pin) {
    pinMode(pin, INPUT);
    this->pin = pin;
    this->state = ButtonState::Neutral;
}

void Button::UpdateState() {
    if (digitalRead(pin) == HIGH) {
        switch (state) {
            case ButtonState::Neutral:
                state = ButtonState::Pressed;
                break;
            case ButtonState::Released:
                state = ButtonState::Pressed;
                break;
            default:
                state = ButtonState::Held;
                break;
        }
    } 
    else {
        switch (state) {
            case ButtonState::Neutral:
                state = ButtonState::Neutral;
                break;
            case ButtonState::Released:
                state = ButtonState::Neutral;
                break;
            default:
                state = ButtonState::Released;
                break;
        }
    }
}

ButtonState Button::GetState() const {
    return state;
}