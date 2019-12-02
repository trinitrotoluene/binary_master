#pragma once

#include "led.hpp"
#include "sreg.hpp"

class PlayerScoreIndicator {
    public:
    PlayerScoreIndicator(uint32_t);
    bool Increment();
    void Decrement();
    void Reset();
    uint32_t GetScore();
    private:
    uint32_t _currentScore;
    uint32_t _offset;
};

class ScoreManager {
    public:
    static bool Increment(uint8_t);
    static void Decrement(uint8_t);
    static void Reset();
    static void Configure();
};