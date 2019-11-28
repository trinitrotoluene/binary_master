#include <Arduino.h>
#include "src/display.hpp"
#include "src/game.hpp"

const int DISPLAY_SIZE = 4;
const int DISPLAY_START_PIN = 9;

Led _displayLeds[DISPLAY_SIZE];
Display* _display;

void setup() {
    Serial.begin(9600);
    // Set up LEDs for the display
    for (int i = 0; i < DISPLAY_SIZE; i++)
        _displayLeds[i].Bind(DISPLAY_START_PIN + i);
    // Initialise the display wrapper
    _display = new Display(_displayLeds, DISPLAY_SIZE);
}

void loop() {
    // TODO: Run a function that reads in selected input in decimal via 3 buttons

    // TODO: Initialise a numchain from the supplied input
    auto chain = NumChain(5, 0, 16);
    // Initialise the round
    auto game = BinaryMasterRound(&chain, _display);

    // Placeholder completion condition
    bool isComplete = false;
    while (!isComplete) {
        game.ShowNextNumber();

        // Substitute this with reading from serial, checking for sent data, returning status object.
        delay(2000);

        // Optionally break out of the loop here.
    }
}