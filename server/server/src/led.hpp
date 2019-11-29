#pragma once

#include <Arduino.h>

class Led {
    public:
    bool IsLit();
    void Toggle();
    void Bind(uint8_t);
    void SetState(uint8_t);
    void SetState(uint8_t, void (*)(int));
    private:
    uint8_t _pin;
    uint8_t _state;
};
