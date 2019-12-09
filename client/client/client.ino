#include <Arduino.h>
#include "src/button.hpp"
#include "src/frame.hpp"
#include "src/array.hpp"

const int BTN_PIN_START = 2;
const int BTN_COUNT = 2;
const int BUF_SIZE = 2;
byte target = 0;
byte currentNum = 1;
byte buffer[BUF_SIZE];

Button BUTTONS[BTN_COUNT];
bool roundOpen = false;

void setup() {
    Serial.begin(9600);

    for (int i = 0; i < BTN_COUNT; i++)
        BUTTONS[i].Bind(i + BTN_PIN_START);
}

void loop() {
    // Update button state
    for (int i = 0; i < BTN_COUNT; i++)
        BUTTONS[i].UpdateState();

    int pid = -1;   
    for (int i = 0; i < BTN_COUNT; i++)
    {
        if (BUTTONS[i].GetState() == ButtonState::Pressed) {
            pid = i;
            break;
        }
    }

    if (pid == -1 || !roundOpen)
        return;

    // If the player got it right, send an answer frame (true).
    if (target == currentNum) {
        auto playerData = PlayerFrame(pid, PlayerCommand::Answer);
        Frame::WriteToSerial(playerData, true);
        roundOpen = false;
    }
    // If the player got it wrong, send an answer frame (false).
    else {
        auto playerData = PlayerFrame(pid, PlayerCommand::Answer);
        Frame::WriteToSerial(playerData, false);
    }
}

void serialEvent() {
    if (Serial.available() < 2)
        return;

    const int BUF_SIZE = 2;
    byte buffer[BUF_SIZE];
    // Read the next 2 bytes available over serial into the buffer.
    buffer[0] = Serial.read();
    buffer[1] = Serial.read();
    // Parse out a new frame from the buffer
    auto frame = Frame::Parse(buffer);

    switch(frame.Type) {
            case FrameType::Control:
                handle_control_frame(frame);
    }
}

void handle_control_frame(Frame frame) {
    switch (frame.Control)
    {
        case ControlCommand::Start:
            target = frame.Value;
        case ControlCommand::NextNumber:
            currentNum = frame.Value;
            roundOpen = true;
    }
}
