#pragma once
#include <Arduino.h>

// Leading bit is set = Control frame
enum FrameType {
    Control = 0x80, 
    PID = 0x0
};

enum ControlCommand {
    Start = 0x01,
    Stop = 0x02,
    NextNumber = 0x04
};

enum PlayerCommand {
    Answer = 0x01
};

struct PlayerFrame {
    public:
    PlayerFrame();
    PlayerFrame(byte, PlayerCommand);
    byte PlayerId;
    PlayerCommand Command;
};

struct Frame {
    public:
    Frame();
    Frame(PlayerFrame, byte);
    Frame(ControlCommand, byte);
    static Frame Parse(byte buffer[]);
    static void WriteToSerial(ControlCommand, byte);
    static void WriteToSerial(PlayerFrame, byte);
    FrameType Type;
    byte Value;
    union {
        ControlCommand Control;
        PlayerFrame Player;
    };
};
