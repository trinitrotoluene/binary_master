#include "tones.hpp"

const int PIEZO_PIN = 5;

const int TONE_LOW = 110;
const int TONE_MEDIUM = 246;
const int TONE_HIGH = 516;
const int SHORT = 125;
const int LONG = 250;

void Tone::Beep() {
    tone_wait(TONE_LOW, SHORT);
}

void Tone::GameStart() {
    tone_wait(TONE_MEDIUM, LONG);
    tone_wait(TONE_HIGH, SHORT);
    delay(LONG);
    tone_wait(TONE_HIGH, SHORT);
    delay(SHORT);
    tone_wait(TONE_LOW, LONG);
}

void Tone::Victory() {
    tone_wait(TONE_HIGH, SHORT);
    delay(SHORT);
    tone_wait(TONE_HIGH, SHORT);
    delay(SHORT);
    tone_wait(TONE_HIGH, SHORT);
}

void Tone::Correct() {
    tone_wait(TONE_MEDIUM, SHORT);
    tone_wait(TONE_HIGH, LONG);
}

void Tone::Wrong() {
    tone_wait(TONE_MEDIUM, SHORT);
    tone_wait(TONE_LOW, LONG);
}

void tone_wait(uint32_t frequency, uint32_t duration) {
    tone(PIEZO_PIN, frequency, duration);
    delay(duration);
}