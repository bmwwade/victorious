#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Board stdBoard;
    Side mySide;
    Side otherSide;
};

int improveHeuristic(int base, int x, int y);
int miniMax(Board *board, Side mySide, Side otherSide);
int calcBase(Board *board, Side side);
#endif
