#include "frame.hpp"

Frame Frame::Parse(byte buffer[], int length = 2 /*TODO this parameter is not needed.*/) {
    if (length > 2 || length < 1) return;

    bool isControl = buffer[0] & FrameType::Control;

    if (isControl) {
        // Mask over the remaining 7 bits
        switch (buffer[0] & 0x7F) {
            case ControlCommand::Start:
                return Frame(ControlCommand::Start, buffer[1]);
            case ControlCommand::Stop:
                return Frame(ControlCommand::Stop, 0);
            default:
                return;
        }
    }
    else {
        byte playerId = buffer[0] & 0x70;
        PlayerCommand command;
        switch (buffer[0] & 0x0F) {
            case PlayerCommand::Answer:
                PlayerFrame frame = PlayerFrame(playerId, PlayerCommand::Answer);
                return Frame(frame, buffer[1]);
        }
    }
}

void Frame::WriteToSerial(ControlCommand command, byte value) {
    byte first = 0x80;
    first |= command;
    Serial.print(first);
    Serial.print(value);
}

void Frame::WriteToSerial(PlayerFrame player, byte value) {
    byte first = 0;
    first |= (player.PlayerId << 4);
    first |= player.Command;
    Serial.print(first);
    Serial.print(value);
}

Frame::Frame(ControlCommand command, byte value) {
    this->Type = FrameType::Control;
    this->Control = command;
    this->Value = value;
}

Frame::Frame(PlayerFrame frame, byte value) {
    this->Type = FrameType::PID;
    this->Player = frame;
    this->Value = value;
}