/* This preprocessor variable is used to select the correct platform-specific header in io.h
 * It's usually defined for you by the Arduino IDE, but if you aren't using it to compile then you have to do it yourself.
 * 
 * REFERENCE #1:
 * For a reference implementation of Pin-Change Interrupts, I used information from this article: https://arduino-projekte.webnode.at/registerprogrammierung/pinchangeinterrupt/
 */
#define __AVR_ATmega168__

#include <Arduino.h>
#include <math.h>
#include "src/display.hpp"
#include "src/game.hpp"
#include "src/debug.hpp"
#include "src/button.hpp"

enum State { Ingest, Run };

const int SREG_DATA = 12;
const int SREG_LATCH = 11;
const int SREG_CLOCK = 10;

const int PIEZO_PIN = 7;

const int BTN_COUNT = 3;
const int BTN_START_PIN = 2;

State _state = State::Ingest;

SReg* _sreg;
Display* _display;

Button BUTTONS[BTN_COUNT];

byte _currentTarget;

void setup() {
    Serial.begin(9600);

    // Initialise the display wrapper
    _sreg = new SReg(SREG_DATA, SREG_LATCH, SREG_CLOCK);
    _display = new Display(_sreg);

    // Set up buttons
    for (int i = 0; i < BTN_COUNT; i++)
        BUTTONS[i].Bind(i + BTN_START_PIN);
}

void loop() {
    // Update the state of the input buttons
    for (int i = 0; i < BTN_COUNT; i++)
        BUTTONS[i].UpdateState();

    if (_state == State::Ingest) {
        ingest_loop();
    }
    else if (_state == State::Run) {
        game_loop();
    }
}

void ingest_loop() {
    // Check if two buttons are pressed at the same time
    int raiseBy = 0;
    bool previouslyPressed = false;
    for (int i = 0; i < BTN_COUNT; i++)
    {
        if (BUTTONS[i].GetState() == ButtonState::Pressed) {
            if (previouslyPressed) {
                _state = State::Run;
                tone(PIEZO_PIN, 1500, 250);
                tone(PIEZO_PIN, 1000, 500);
                tone(PIEZO_PIN, 1500, 250);
                return;
            }
            else {
                previouslyPressed = true;
                raiseBy = i;
            }
        }
    }
    
    if (previouslyPressed) {
        _currentTarget += pow(10, raiseBy);
        tone(PIEZO_PIN, 600, 100);
        Debug::printLn("Current Target: %i", _currentTarget);
    }

    _display->PrintBinary(_currentTarget);
}

void game_loop() {
    // Initialise a numchain targeting the provided target
    auto chain = NumChain(_currentTarget, 0, 255);
    // Initialise the round
    auto game = BinaryMasterRound(&chain, _display);

    bool isComplete = false;
    while (!isComplete) {
        game.ShowNextNumber();

        // Substitute this with reading from serial, checking for sent data, returning status object.
        delay(1000);

        // Optionally break out of the loop here.
    }
}
