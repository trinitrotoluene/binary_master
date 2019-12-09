#include "scoremanager.hpp"

SReg ScoreManager::Sreg = SReg(SC_SREG_DATA, SC_SREG_LATCH, SC_SREG_CLOCK);
PlayerScoreIndicator ScoreManager::_indicators[SC_MAX_PLAYERS];

void ScoreManager::Configure() {
    ScoreManager::Sreg.Init();
    int offset = 0;
    for (int i = 0; i < SC_MAX_PLAYERS; i++)
    {
        ScoreManager::_indicators[i] = PlayerScoreIndicator(offset);
        offset += SC_LED_PER_USR;
    }
}

void ScoreManager::Reset() {
    for (uint32_t i = 0; i < SC_MAX_PLAYERS; i++)
        ScoreManager::_indicators[i].Reset();
}

bool ScoreManager::Increment(uint8_t pid) {
    if (pid >= SC_MAX_PLAYERS) return false;

    else return _indicators[pid].Increment();
}

void ScoreManager::Decrement(uint8_t pid) {
    if (pid >= SC_MAX_PLAYERS) return;

    _indicators[pid].Decrement();
}

/*--*/
PlayerScoreIndicator::PlayerScoreIndicator() {
}

PlayerScoreIndicator::PlayerScoreIndicator(uint32_t offset) {
    this->_offset = offset;
    this->_currentScore = 0;
}

void PlayerScoreIndicator::Reset() {
    for (uint32_t i = this->_offset; i < SC_LED_PER_USR; i++)
    {
        ScoreManager::Sreg.DigitalWrite(i, LOW);
        this->_currentScore = 0;
    }
}

bool PlayerScoreIndicator::Increment() {
    ScoreManager::Sreg.DigitalWrite(this->_offset + this->_currentScore, HIGH);
    this->_currentScore++;

    return this->_currentScore >= SC_LED_PER_USR;
}

void PlayerScoreIndicator::Decrement() {
    if (this->_currentScore > 0) {
        --this->_currentScore;
        ScoreManager::Sreg.DigitalWrite(this->_currentScore, LOW);
    }
}

uint32_t PlayerScoreIndicator::GetScore() {
    return this->_currentScore;
}