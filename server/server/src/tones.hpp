#pragma once

#include <Arduino.h>

class Tone {
    public:
    static void Beep();
    static void GameStart();
    static void Victory();
    static void Correct();
    static void Wrong();
};

void tone_wait(uint32_t, uint32_t);