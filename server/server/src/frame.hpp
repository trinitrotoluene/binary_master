#pragma once
#include <Arduino.h>

enum FrameType {
    Control = 0x80, 
    PID = 0
};

enum ControlCommand {
    Start = 0x40,
    Stop = 0x20,
};

enum PlayerCommand {
    Answer = 0x40
};

struct PlayerFrame {
    public:
    PlayerFrame(byte, PlayerCommand);
    byte PlayerId;
    PlayerCommand Command;
};

struct Frame {
    public:
    Frame(PlayerFrame, byte);
    Frame(ControlCommand, byte);
    static Frame Parse(byte buffer[], int length);
    static void WriteToSerial(ControlCommand, byte);
    static void WriteToSerial(PlayerFrame, byte);
    FrameType Type;
    byte Value;
    union {
        ControlCommand Control;
        PlayerFrame Player;
    };
};
