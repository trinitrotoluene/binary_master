#include "game.hpp"

BinaryMasterRound::BinaryMasterRound() {
}

BinaryMasterRound::BinaryMasterRound(NumChain* chain, Display* display) {
    this->Chain = chain;
    this->DisplayOutput = display;
}

int BinaryMasterRound::ShowNextNumber() {
    auto nextNum = this->Chain->Next();

    this->DisplayOutput->PrintBinary(nextNum);

    return nextNum;
}