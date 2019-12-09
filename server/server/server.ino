#include <Arduino.h>
#include "src/BinaryMaster.h"

// Used to track the current state of the server.
enum State { Ingest, Run, Running };

// Pin and other const definitions
const int SREG_DATA = 13;
const int SREG_LATCH = 12;
const int SREG_CLOCK = 11;

const int VICTORY_PIN = 6;

const int BTN_COUNT = 3;
const int BTN_START_PIN = 2;
const int DURATION_OFFSET = 500;

// When starting out we're going to be ingesting user input.
State _state = State::Ingest;

// Sreg and display wrappers.
SReg _sreg = SReg(SREG_DATA, SREG_LATCH, SREG_CLOCK);
Display _display = Display(&_sreg);
NumChain _currentChain;
BinaryMasterRound _currentRound;

Led _victoryLed;
// Array of buttons we'll be using to accept input.
Button BUTTONS[BTN_COUNT];

// Our current byte target, starts at 0.
byte _currentTarget = 0;

uint64_t endTime;

void setup() {
    Serial.begin(9600);

    _victoryLed.Bind(VICTORY_PIN);

    // Set up button pins
    for (int i = 0; i < BTN_COUNT; i++)
        BUTTONS[i].Bind(i + BTN_START_PIN);

    ScoreManager::Configure();
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
        // Initialise a numchain targeting the provided target
        _currentChain = NumChain(_currentTarget, 0, 255);
        _currentRound  = BinaryMasterRound(&_currentChain, &_display);

        // Send a Start frame to the client with the current target.
        Frame::WriteToSerial(ControlCommand::Start, _currentTarget);

        _state = State::Running;
    }
    else if (_state == State::Running) {
        if (millis() > endTime) {
            send_next_number();
            endTime = millis() + analogRead(5) + DURATION_OFFSET;
        }
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
    int totalPressed = Array::Count(BUTTONS, BTN_COUNT, filter_pressed_or_held);
    int index = Array::IndexOfFirst(BUTTONS, BTN_COUNT, filter_pressed);

    // If more than one button is pressed or held
    if (totalPressed > 1) {
        // Change the server state to Run, play a tone and exit the loop.
        _state = State::Run;
        Tone::GameStart();
        return;
    }
    // If a button was found in a pressed state
    else if (index > -1) {
        // Raise 10 to the power of the button's index to get the multipliers 1x, 10x, 100x and add it to the target.
        _currentTarget += pow(10, index);
        Tone::Beep();
    }
    // Display the current or updated target number.
    _display.PrintBinary(_currentTarget);
}

void send_next_number() {
    // Move to the next number in the chain, display it.
    int current = _currentRound.ShowNextNumber();
    // Write the current in the chain to the serial connection
    Frame::WriteToSerial(ControlCommand::NextNumber, current);
}

void serialEvent() {
    if (Serial.available() < 2)
        return;

    const int BUF_SIZE = 2;
    byte buffer[BUF_SIZE];
    // Read the next 2 bytes available over serial into the buffer. Waits for setTimeout(ms) milliseconds
    size_t count = Serial.readBytes(buffer, BUF_SIZE);
    // Parse out a new frame from the buffer
    auto frame = Frame::Parse(buffer);
    // Pick the right path based on the frame type.
    switch(frame.Type) {
        case FrameType::Control:
            // Not implemented, but extension point for reset functionality from the client.
            break;
        case FrameType::PID:
            handle_player_frame(frame);
            break;
        default:
            break;
    }
}

// This method is called every time a player frame was sent over serial.
void handle_player_frame(Frame frame) {
    switch (frame.Player.Command) {
        // If this was a submitted answer
        case PlayerCommand::Answer:
            // The second byte should be interpreted as a bool for Answer commands
            if (frame.Value) {
                // Check whether this was the last LED
                bool playerWon = ScoreManager::Increment(frame.Player.PlayerId);
                if (playerWon) {
                    full_reset();
                }
                else {
                    // Already incremented score, so just play the tone and move to the next round.
                    Tone::Correct();
                    next_round();
                }
            }
            else {
                // Wrong answer, decrement and play the appropriate tone.
                ScoreManager::Decrement(frame.Player.PlayerId);
                Tone::Wrong();
            }
            break;
        default:
            break;
    }
}

void next_round() {
    _currentTarget = 0;
    _state = State::Ingest;
}

void full_reset() {
    digitalWrite(VICTORY_PIN, HIGH);
    Tone::Victory();
    Tone::Victory();
    digitalWrite(VICTORY_PIN, LOW);
    ScoreManager::Reset();
    _currentTarget = 0;
    _state = State::Ingest;
}
