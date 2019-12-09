#include "frame.hpp"

Frame Frame::Parse(byte buffer[]) {
    bool isControl = buffer[0] & FrameType::Control;

    if (isControl) {
        switch (buffer[0] & 0x0F) {
            case ControlCommand::Start:
                return Frame(ControlCommand::Start, buffer[1]);

            case ControlCommand::Stop:
                return Frame(ControlCommand::Stop, 0);

            case ControlCommand::NextNumber:
                return Frame(ControlCommand::NextNumber, buffer[1]);

            default:
                break;
        }
    }
    else {
        byte playerId = (buffer[0] & 0x70) >> 4;
        PlayerFrame frame;
        switch (buffer[0] & 0x0F) {
            case PlayerCommand::Answer:
                frame = PlayerFrame(playerId, PlayerCommand::Answer);
                return Frame(frame, buffer[1]);

            default:
                break;
        }
    }

    return;
}

void Frame::WriteToSerial(ControlCommand command, byte value) {
    byte first = 0;
    first |= FrameType::Control;
    first |= command;
    Serial.write(first);
    Serial.write(value);
}

void Frame::WriteToSerial(PlayerFrame player, byte value) {
    byte first = 0;
    first |= (player.PlayerId << 4);
    first |= player.Command;
    Serial.write(first);
    Serial.write(value);
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

Frame::Frame() {
}

PlayerFrame::PlayerFrame() {
}

PlayerFrame::PlayerFrame(byte pid, PlayerCommand command) {
    this->Command = command;
    this->PlayerId = pid;
}