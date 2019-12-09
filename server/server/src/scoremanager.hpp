#pragma once

#include "led.hpp"
#include "sreg.hpp"

const int SC_MAX_PLAYERS = 2;
const int SC_LED_PER_USR = 4;

const int SC_SREG_DATA = 10;
const int SC_SREG_LATCH = 9;
const int SC_SREG_CLOCK = 8;

class PlayerScoreIndicator {
    public:
    PlayerScoreIndicator();
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
    static SReg Sreg;
    private:
    static PlayerScoreIndicator _indicators[SC_MAX_PLAYERS];
};