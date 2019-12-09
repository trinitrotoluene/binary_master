#ifndef _GAME_H
#define _GAME_H
#include "numchain.hpp"
#include "display.hpp"

class BinaryMasterRound {
    public:
    BinaryMasterRound();
    BinaryMasterRound(NumChain*, Display*);
    // Chain from which numbers will be pulled during this game.
    NumChain* Chain;
    // Ptr to the display that this game is using.
    Display* DisplayOutput;
    // Pull the next number from the chain, and display it.
    int ShowNextNumber();
};

#endif