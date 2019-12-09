#include "scoremanager.hpp"

const int MAX_PLAYERS = 2;
const int LED_PER_USR = 4;

const int SREG_DATA = 10;
const int SREG_LATCH = 9;
const int SREG_CLOCK = 8;

SReg _register = SReg(SREG_DATA, SREG_LATCH, SREG_CLOCK);

PlayerScoreIndicator* _indicators;

void ScoreManager::Configure() {
    _register.Init();
    uint32_t offset = 0;
    for (uint32_t i = 0; i < MAX_PLAYERS; i++)
    {
        _indicators[i] = PlayerScoreIndicator(offset);
        offset += LED_PER_USR;
    }
}

void ScoreManager::Reset() {
    for (uint32_t i = 0; i < MAX_PLAYERS; i++)
        _indicators[i].Reset();
}

bool ScoreManager::Increment(uint8_t pid) {
    if (pid >= MAX_PLAYERS) return false;

    else return _indicators[pid].Increment();
}

void ScoreManager::Decrement(uint8_t pid) {
    if (pid >= MAX_PLAYERS) return;

    _indicators[pid].Decrement();
}

/*--*/

PlayerScoreIndicator::PlayerScoreIndicator(uint32_t offset) {
    this->_offset = offset;
    this->_currentScore = 0;
}

void PlayerScoreIndicator::Reset() {
    for (uint32_t i = this->_offset; i < LED_PER_USR; i++)
    {
        _register.DigitalWrite(i, LOW);
        this->_currentScore = 0;
    }
}

bool PlayerScoreIndicator::Increment() {
    _register.DigitalWrite(this->_offset + this->_currentScore, HIGH);
    this->_currentScore++;

    return this->_currentScore >= LED_PER_USR;
}

void PlayerScoreIndicator::Decrement() {
    if (this->_currentScore > 0) {
        this->_currentScore--;
        _register.DigitalWrite(this->_currentScore, LOW);
    }
}

uint32_t PlayerScoreIndicator::GetScore() {
    return this->_currentScore;
}