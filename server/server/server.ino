// Just to make sure the correct headers are included by io.h (included by Arduino.h)
#define __AVR_ATmega168__

#include <Arduino.h>
#include "BinaryMaster.h"

// Used to track the current state of the server.
enum State { Ingest, Run };

// Pin and other const definitions
const int SREG_DATA = 12;
const int SREG_LATCH = 11;
const int SREG_CLOCK = 10;

const int PIEZO_PIN = 7;

const int BTN_COUNT = 3;
const int BTN_START_PIN = 2;

const int TONE_LOW = 110;
const int TONE_HIGH = 516;
const int TONE_DURATION_SHORT = 250;
const int TONE_DURATION_HIGH = 1000;

// When starting out we're going to be ingesting user input.
State _state = State::Ingest;

// Pointers to hold the shift register and display wrappers.
SReg* _sreg;
Display* _display;

// Array of buttons we'll be using to accept input.
Button BUTTONS[BTN_COUNT];

// Our current byte target, starts at 0.
byte _currentTarget;

void setup() {
    Serial.begin(9600);

    // Initialise the display wrapper and give it a shift register to work with.
    _sreg = new SReg(SREG_DATA, SREG_LATCH, SREG_CLOCK);
    _display = new Display(_sreg);
    
    // Set up button pins
    for (int i = 0; i < BTN_COUNT; i++)
        BUTTONS[i].Bind(i + BTN_START_PIN);
}

void loop() {
    // Update the state of the input buttons
    for (int i = 0; i < BTN_COUNT; i++)
        BUTTONS[i].UpdateState();

    // Branch into the correct loop for the current state of the program.
    if (_state == State::Ingest) {
        ingest_loop();
    }
    else if (_state == State::Run) {
        run_game();
    }
}

void ingest_loop() {
    // Check if two buttons are pressed at the same time
    int raiseBy = 0;
    bool previouslyPressed = false;

    // Lambdas to use when applying filters to the button array
    auto filter_pressed_or_held = [] (Button btn) -> bool { return btn.GetState() == ButtonState::Pressed || btn.GetState() == ButtonState::Held; };
    auto filter_pressed = [] (Button btn) -> bool { return btn.GetState() == ButtonState::Pressed; };
    // Filter the button array for the number of pressed or held buttons, and get the index (if any) of the first pressed button.
    int totalPressed = Array<Button>::Count(BUTTONS, BTN_COUNT, filter_pressed_or_held);
    int index = Array<Button>::IndexOfFirst(BUTTONS, BTN_COUNT, filter_pressed);

    // If more than one button is pressed or held
    if (totalPressed > 1) {
        // Change the server state to Run, play a tone and exit the loop.
        Debug::printLn("Selected Target: %i! Beginning game.", _currentTarget);
        _state = State::Run;
        tone(PIEZO_PIN, TONE_LOW, TONE_DURATION_SHORT);
        delay(TONE_DURATION_SHORT);
        tone(PIEZO_PIN, TONE_HIGH, TONE_DURATION_HIGH);
        delay(TONE_DURATION_HIGH);
        tone(PIEZO_PIN, TONE_LOW, TONE_DURATION_SHORT);
        delay(TONE_DURATION_SHORT);
        tone(PIEZO_PIN, TONE_HIGH, TONE_DURATION_HIGH);
        delay(TONE_DURATION_HIGH);
        return;
    }
    // If a button was found in a pressed state
    else if (index > -1) {
        // Raise 10 to the power of the button's index to get the multipliers 1x, 10x, 100x and add it to the target.
        _currentTarget += pow(10, index);
        tone(PIEZO_PIN, TONE_LOW, TONE_DURATION_SHORT);
        Debug::printLn("Target Updated: %i", _currentTarget);
    }
    // Display the current or updated target number.
    _display->PrintBinary(_currentTarget);
}

void run_game() {
    // Initialise a numchain targeting the provided target
    auto chain = NumChain(_currentTarget, 0, 255);
    // Initialise the round
    auto game = BinaryMasterRound(&chain, _display);

    // Send a Start frame to the client with the current target.
    Frame::WriteToSerial(ControlCommand::Start, _currentTarget);

    const int BUF_SIZE = 2;
    byte buffer[BUF_SIZE];
    while(true) {
        Serial.readBytes(buffer, BUF_SIZE);
        auto frame = Frame::Parse(buffer, 2);

        switch(frame.Type) {
            case FrameType::Control:
                // TODO: Control
            case FrameType::PID:
                handle_player_frame(frame);
        }
    }
}

void handle_player_frame(Frame frame) {
    switch (frame.Player.Command) {
        case PlayerCommand::Answer:
            if (frame.Value) {
                // Player got the right answer
                _currentTarget = 0;
                _state = State::Ingest;
                // TODO: Celebrate
            }
            else {
                // Player got the wrong answer
            }
    }
}
