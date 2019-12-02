#include <Arduino.h>
#include "button.hpp"

const int BTN_PIN_START = 2;
const int BTN_COUNT = 2;

Button BUTTONS[BTN_COUNT];

void setup() {
    for (int i = 0; i < BTN_COUNT; i++)
        BUTTONS[i].Bind(i + BTN_PIN_START);
}

void loop() {
    for (int i = 0; i < BTN_COUNT; i++)
        BUTTONS[i].UpdateState();
}