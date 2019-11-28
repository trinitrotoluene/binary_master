#include "game.hpp"

BinaryMasterRound::BinaryMasterRound(NumChain* chain, Display* display) {
    this->Chain = chain;
    this->DisplayOutput = display;
}

void BinaryMasterRound::ShowNextNumber() {
    auto nextNum = this->Chain->Next();

    this->DisplayOutput->PrintBinary(nextNum);

    // TODO: Save when the game was last updated?
}